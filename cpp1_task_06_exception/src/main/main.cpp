#include <iostream>
#include "circular_buffer.h"

using namespace std;


//class MyClass
//{
//public:
//	int a;
//	MyClass() = default;
//	MyClass(int a)
//	{
//		
//		this->a = a;
//		cout << "Constructor #" << a << endl;
//	}
//
//	~MyClass()
//	{
//		cout << "Destructor #" << a << endl;
//	}
//};
int main()
{
	Circular_buffer<int> m(9);
	for (int i = 0; i < 7; i++)
	{
		m.push(i);		
	}
	cout << m.get_size() << endl;
	m.erase(m.begin()+4);
	cout <<endl << "M_______M" << endl;
	m.print();
	
	Circular_buffer<int> p(10);
	for (int i = 0; i < 5; i++)
	{
		p.push(move(i));
	}
	cout << "iterator output" << endl;
	for (int i = 0; i < p.get_size(); i++)
	{
		cout << *(p.begin() + i) << " ";
	}
	cout << endl << "P_______P" << endl;
	p.print();
	p = move(m);
	cout << endl << "M_______M" << endl;
	m.print();
	system("pause");
	return 0;
}