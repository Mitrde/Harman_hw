#include <iostream>
#include "custom_string.h"

int StrLen(const char*);	
void StrCpy(char*,const char*);

String::String(const char* _str)
{
	this->size = StrLen(_str);
	str = new char[StrLen(_str) + 1];
	StrCpy(str, _str);
}

String::String(const String& other)
{
	str = new char[other.size + 1];
	StrCpy(str, other.str);
}

String::String(String &&other) noexcept
{
	this->str = other.str;
	this->size = other.size;
	other.size = 0;
	other.str = nullptr;
}

String& String::operator= (String && other) noexcept
{
	if (this != &other)
	{
		delete[] str;
		str = other.str;
		size = other.size;
		other.size = 0;
		other.str = nullptr;
	}
	return *this;
}

String::~String()
{
	delete str;
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		delete[] this->str;
		this->str = new char[other.size + 1];
		StrCpy(this->str, other.str);
	}
	return *this;
}

const char * String::Get_c() noexcept
{
	return this->str;
}
	
	// ---

int StrLen(const char* _str)
{
	int size = 0;
	for (; _str[size] != 0; size++);
	return size;
}

void StrCpy(char* destptr,const char* srcptr)
{
	for (int i = 0; i < StrLen(destptr); i++)
		destptr[i] = srcptr[i];
}
