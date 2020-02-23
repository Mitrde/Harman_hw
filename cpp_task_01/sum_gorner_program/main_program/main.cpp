#include <iostream>
#include <vector>
#include "rational_numbers.h"

using namespace std;

ostream & operator<<(ostream & out, const Rationals & other)
{	
	return other.print(out);;
}

Rationals gorner_sum(Rationals &q, vector<Rationals> &koefs)
{
	Rationals sum = koefs[0];

	for (auto koef : koefs)
	{
		sum = sum * q;
		sum = sum + koef;
	}
	return sum;
}


int main()
{
	vector<Rationals> a = { Rationals(2,3), Rationals(5,7), Rationals(8,6) }; //polynomial coefficients
	int q1_a, q1_b, q2_a, q2_b;
	cout << "Input q1 = a/b like 'a b': ";
	cin >> q1_a >> q1_b;
	cout << "Input q2 = a/b like 'a b': ";
	cin >> q2_a >> q2_b;
	Rationals q1(q1_a, q1_b);
	Rationals q2(q2_a, q2_b);

	Rationals sum1 = gorner_sum(q1,a);

	Rationals sum2 = gorner_sum(q2, a);

	

	cout << "sum(q1): " << sum1 << " sum(q2): " << sum2 << ((sum1 < sum2) ? "\nsum1 < sum2" : "\nsum1 > sum2") << endl;

	system("pause");
	return 0;
}