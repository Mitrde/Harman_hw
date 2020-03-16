#pragma once

class String
{
public:
	String(const char* _str = "");
	String(const String&);
	String(String &&other) noexcept;
	String & operator= (String && other) noexcept;
	String & operator=(const String & rhs);
	const char* Get_c() noexcept;

	~String();

private:
	char* str;
	int size;
};

