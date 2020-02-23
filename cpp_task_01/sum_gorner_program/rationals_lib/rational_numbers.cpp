#include <vector>
#include <string>
#include <iostream>
#include "rational_numbers.h"

using namespace std;

void Rationals::reduce()
{
	int a = this->numerator;
	int b = this->denominator;
	while (a != b) {
		if (a > b) {
			long tmp = a;
			a = b;
			b = tmp;
		}
		b = b - a;
	}
	this->numerator /= a;
	this->denominator /= a;
}

Rationals const Rationals::operator+(const Rationals & other)
{
	int a = this->numerator * other.denominator + this->denominator*other.numerator;
	int b = this->denominator * other.denominator;
	Rationals tmp(a, b);
	tmp.reduce();
	return tmp;
}

Rationals const Rationals::operator-(const Rationals & other)
{
	int a = this->numerator * other.denominator - this->denominator*other.numerator;
	int b = this->denominator * other.denominator;
	Rationals tmp(a, b);
	tmp.reduce();
	return tmp;
}

Rationals const Rationals::operator*(const Rationals & other)
{
	int a = this->numerator * other.numerator;
	int b = this->denominator * other.denominator;
	Rationals tmp(a, b);
	tmp.reduce();
	return tmp;
}

Rationals & Rationals::operator=(const Rationals & other)
{
	this->denominator = other.denominator;
	this->numerator = other.numerator;
	return *this;
}

Rationals const Rationals::operator/(const Rationals & other)
{
	int a = this->numerator * other.denominator;
	int b = this->denominator * other.numerator;

	//if (b == 0)
	//	throw std::runtime_error("zero division error");

	Rationals tmp(a, b);
	tmp.reduce();
	return tmp;
}

bool const Rationals::operator==(const Rationals & other)
{
	int this_n = this->numerator;
	size_t this_d = this->denominator;
	int other_n = other.numerator;
	size_t other_d = other.denominator;

	return(this_n * other_d == other_n * this_d);
}

bool const Rationals::operator>(const Rationals & other)
{
	int this_n = this->numerator;
	size_t this_d = this->denominator;
	int other_n = other.numerator;
	size_t other_d = other.denominator;

	return(this_n * other_d > other_n * this_d);
}

bool const Rationals::operator<(const Rationals & other)
{
	int this_n = this->numerator;
	size_t this_d = this->denominator;
	int other_n = other.numerator;
	size_t other_d = other.denominator;

	return(this_n * other_d < other_n * this_d);
}

std::ostream & Rationals::print(std::ostream & out) const
{
	string c = to_string(this->numerator) +"/" + to_string(this->denominator);
	out << c.c_str();	
	return out;
}

