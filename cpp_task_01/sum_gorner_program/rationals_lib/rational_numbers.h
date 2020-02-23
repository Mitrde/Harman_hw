#pragma once

class Rationals
{
private:
	int numerator;
	size_t denominator = 1;
	
public:
	Rationals(int numerator_, size_t denominator_ = 1) : numerator(numerator_), denominator(denominator_)
	{}

	void reduce();
	std::ostream & print(std::ostream & out) const;

	Rationals const operator+(const Rationals & other);
	Rationals const operator-(const Rationals & other);
	Rationals const operator*(const Rationals & other);
	Rationals const operator/(const Rationals & other);
	Rationals& operator=(const Rationals & other);
	bool const operator==(const Rationals & other);
	bool const operator>(const Rationals & other);
	bool const operator<(const Rationals & other);	
};

