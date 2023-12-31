// Autogenerated Scheme to C++ Code
// File: Example2.cpp
#include <iostream>
#include "Object.h"
using namespace std;


Object sum (Object L)
{
	Object __RetVal;
	if (nullp (L))
	{
		__RetVal = Object(0);
	}
	else
	{
		__RetVal = (listop ("car", L) + sum(listop ("cdr", L)));
	}
;
	return __RetVal;
}

int main ()
{
	Object __RetVal;
	cout << Object("The sum of '(1 5 6) is ");
;
	cout << sum(Object("(1 5 6 )"));
;
	cout << endl;
;
	cout << Object("The sum of '() is ");
;
	cout << sum(Object("()"));
;
	cout << endl;
;
	cout << Object("The sum of '(5 -1 3 7 10) is ");
;
	cout << sum(Object("(5 -1 3 7 10 )"));
;
	cout << endl;
;
	return 0;
}
