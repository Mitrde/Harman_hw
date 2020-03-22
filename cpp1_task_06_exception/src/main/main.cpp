#include <iostream>
#include "circular_buffer.h"
#include <utility>     // swap()
#include <functional>
#include <type_traits>
#include <iostream>
#include <iomanip>
#include <iterator>    // ostream_iterator <>
#include <string>      // to_string()
#include <list>

using namespace std;



struct Test
{
	int m_n;
	int m_nCheck;
	bool m_bThrowInMove, m_bThrowLater;
	static bool ms_bThrowDeferred;
	std::list <double> m_List;
	//
	Test(int n, bool bThrowInMove = false, bool bThrowLater = false)
		: m_n(n),
		m_nCheck(1),
		m_bThrowInMove(bThrowInMove),
		m_bThrowLater(bThrowLater),
		m_List(100, 1.)
	{
		std::cout << "Test(" << setw(3) << n << ")" << endl;
	}
	//
	Test(const Test &rcTest)
		: m_n(rcTest.m_n),
		m_nCheck(rcTest.m_nCheck),
		m_bThrowInMove(rcTest.m_bThrowInMove),
		m_bThrowLater(rcTest.m_bThrowLater),
		m_List(rcTest.m_List)
	{
		cout << "Test(const Test &rcTest), rcTest == " << rcTest << endl;
		if (m_bThrowInMove)
		{
			cout << "Throwing..." << endl;
			throw std::logic_error(string("Test(") + to_string(m_n) + ")");
		}
		if (m_bThrowLater && ms_bThrowDeferred)
		{
			cout << "Throwing..." << endl;
			throw std::logic_error("Test(Test &&)");
		}
	}
	//
	friend std::ostream &operator << (std::ostream &rStream, const Test &rcTest)
	{
		if (rcTest.m_nCheck == 1)
			rStream << setw(3) << rcTest.m_n;
		else
			rStream << "invalid";
		//
		return rStream;
	}
	//
	Test(Test &&) = delete;
	Test &operator = (const Test &) = delete;
	Test &operator = (Test &&) = delete;
};

bool Test::ms_bThrowDeferred = false;
void output(Test* begin, Test* end)
{
	copy(begin, end, ostream_iterator <Test>(cout, " "));
	cout << endl;
}

void output(Circular_buffer <Test> &rCircular_buffer)
{
	cout <<
		"Size: " << rCircular_buffer.get_size() <<
		", capacity: " << rCircular_buffer.get_capacity() <<
		", contents:\n";
	output(rCircular_buffer.begin(), rCircular_buffer.end());
}

void output(const exception &rcException)
{
	cout << "Exception: " << rcException.what() << endl;
}
//using Stack = Circular_buffer <Test>;
	//
	// 1. push()
	//
int main()
{
	using Circular_buffer = Circular_buffer<Test>;
	cout << "1. push()" << endl;
	Circular_buffer s1(5);
	int i = 0;
	for (; i < 10; ++i)
		s1.push(Test(i));
	//
	for (; s1.get_size() < s1.get_capacity(); ++i)
		s1.push(Test(i));
	//
	auto begin = s1.begin();
	auto end = s1.end();
	//
	output(s1);
	//
	try
	{
		s1.push(Test(999, true));
	}
	catch (const exception &rcException)
	{
		output(rcException);
	}
	//
	output(begin, end);
	//
	s1.push(Test(i++));
	//
	begin = s1.begin();
	end = s1.end();
	//
	output(s1);
	//
	try
	{
		s1.push(Test(9999, true));
	}
	catch (const exception &rcException)
	{
		output(rcException);
	}
	//
	output(s1);
	output(begin, end);
	//
	s1.push(Test(i++, false, true));
	s1.push(Test(i++));
	//
	output(s1);
	//
	// 2. Copy construction
	//
	cout << "2. Copy construction" << endl;
	Test::ms_bThrowDeferred = true;
	try
	{
		Circular_buffer s2 = s1;
		//Stack s2 = std::move(s1); - compilation error
	}
	catch (const exception &rcException)
	{
		output(rcException);
	}
	catch (...)
	{
		cout << "catch (...)" << endl;
	}
	//
	// 3. Copy assignment
	//
	cout << "3. Copy assignment" << endl;
	Circular_buffer s3(5);
	s3.push(Test(111));
	begin = s3.begin();
	end = s3.end();
	try
	{
		s3 = s1;
		//s3 = std::move(s1); - compilation error
	}
	catch (const exception &rcException)
	{
		output(rcException);
	}
	//
	output(s3);
	output(begin, end);
	system("pause");
	return 0;
}