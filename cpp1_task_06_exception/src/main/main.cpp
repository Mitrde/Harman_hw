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
	~Test()
	{}
};

bool Test::ms_bThrowDeferred = false;
void output(ConstCircularIterator<Test> begin, ConstCircularIterator<Test> end)
{
	copy(begin, end+1, ostream_iterator <Test>(cout, " "));
	cout << endl;
}

void output(Circular_buffer <Test> &rCircular_buffer)
	{
		cout <<
			"Size: " << rCircular_buffer.get_size() <<
			", capacity: " << rCircular_buffer.get_capacity() <<
			", contents:\n";
		output(rCircular_buffer.cbegin(), rCircular_buffer.cend());
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
	output(s1);
	
	auto begin = s1.cbegin();
	auto end = s1.cend();
	//
	output(s1);
	//
	try
	{
		s1.push(move(Test(999, true)));
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
	begin = s1.cbegin();
	end = s1.cend();
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
	Test::ms_bThrowDeferred = true; //////////////////////////
	
	
	try
	{
		auto it_b = s1.begin();
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
	begin = s3.cbegin();
	end = s3.cend();
	try
	{
		s3 = s1;
		cout << " number of refs after copy " << s3.refs() << endl;
		//s3 = std::move(s1); - compilation error
	}
	catch (const exception &rcException)
	{
		output(rcException);
	}
	//
	output(s3);
	output(begin, end);

	//////////////// Copy on write TESTS
	Test::ms_bThrowDeferred = false;

	Circular_buffer c1(5);
	for (int i = 0; i < 5; ++i)
	{
		c1.push(Test(i));
	}
	Circular_buffer c2(c1);

	Circular_buffer c3(c2);
	cout << "c1 amount of refs: " << c1.refs() << endl;
	cout << "1)" << endl;
	output(c1);
	output(c2);
	output(c3);

	c1.push(Test(777));
	cout << "c1 amount of refs: " << c1.refs() << endl;
	cout << "c2 amount of refs: " << c2.refs() << endl;
	Circular_buffer c4(c1);
	output(c4);
	cout << "c1 amount of refs: " << c1.refs() << endl;

	cout << "2)" << endl;
	output(c1);
	output(c2);
	output(c3);
	output(c4);

	c1.push(1337);
	Circular_buffer c5(c1);

	cout << "3)" << endl;
	output(c1);
	output(c2);
	output(c3);
	output(c4);
	output(c5);

	c5.push(Test(69));

	cout << "4)" << endl;
	output(c1);
	output(c2);
	output(c3);
	output(c4);
	output(c5);

	c5.push(Test(420));

	cout << "5)" << endl;
	output(c1);
	output(c2);
	output(c3);
	output(c4);
	output(c5);


	system("pause");
	return 0;
}