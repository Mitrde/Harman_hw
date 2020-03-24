#include <iostream>
#include "custom_string.h"

using namespace std;

int main()
{
	String A("str");
	String B = A;
	A = move(B);
    cout << A.Get_c() << endl;
	return 0;
}
