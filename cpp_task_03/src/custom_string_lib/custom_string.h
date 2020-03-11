#pragma once

class String
{
public:
	String(const char* _str = "");
	String(const String&);
	String(String &&other) noexcept;
	String & operator= (String && other);
	String & operator=(const String & rhs);

	~String();

private:
	char* str;
	int size;
};

