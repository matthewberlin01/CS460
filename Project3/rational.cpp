/*******************************************************************************
* Assignment: Exercise 4 - rational class                                      *
* Author: Dr. Watts                                                            *
* Date: Fall 2022                                                              *
* File: rational.cpp                                                           *
*                                                                              *
* Description: This file contains the implementations of the functions and     *
*              operators prototyped in the rational class definition in        *
*              rational.h                                                      *
*              Note: rational values will be stored in reduced (simplified)    *    
*              terms. A 0 denominator will result in an error message and      *
*              termination of program execution.                               *
*******************************************************************************/

#include "rational.h"
#include <sstream>
#include <iomanip>
#include <cmath>
#include <numeric>

#define DEBUG false
#define debug if (DEBUG) cerr

/*******************************************************************************
* Number: 1                                                                    *
* Function: Default Constructor                                                *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will initialze the value of the newly constructed *
*              rational to 0 (zero).                                           *
*******************************************************************************/

rational::rational ()
{
	debug << "/* 1 */ Executing rational default constructor for "
              << this << endl;
	num = 0;
	denom = 1;
}

/*******************************************************************************
* Number: 2                                                                    *
* Function: Copy Constructor                                                   *
*                                                                              *
* Parameters: R is an existing rational object.                                *
* Return value: None                                                           *
* Description: This function will copy the contents of the rational passed to  *
*              it to *this, a newly constructed rational.                      *
*******************************************************************************/

rational::rational (const rational & R)
{
	debug << "/* 2 */ Executing rational copy constructor for "
	      << this << endl;
	num = R.num;
	denom = R.denom;
}

/*******************************************************************************
* Number: 3                                                                    *
* Function: Destructor                                                         *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will be called when a rational object goes        *
*              out of scope.                                                   *
*******************************************************************************/

rational::~rational ()
{
	debug << "/* 3 */ Executing rational destructor for " << this << endl;
}
 
/*******************************************************************************
* Number: 4                                                                    *
* Function: Assignment Operator                                                *
*                                                                              *
* Parameters: R is an existing rational object.                                *
* Return value: An implicit pointer to this rational.                          *
* Description: This function will copy the contents of the rational passed to  *
*              it to this existing rational.                                   *
*******************************************************************************/

rational & rational::operator = (const rational & R)
{
	debug << "/* 4 */ Executing rational assignment operator for "
	      << this << " and " << &R << endl;
	num = R.num;
	denom = R.denom;
	return * this;
}

/*******************************************************************************
* Number: 5                                                                    *
* Function: Extraction Operator                                                *
*                                                                              *
* Parameters: input is an open istream object.                                 *
*             R is an existing rational object.                                *
* Return value: An implicit pointer to the passed istream object.              *
* Description: This function will extract (read) appropriate values from       *
*              input and store them in R.                                      *
*******************************************************************************/

istream & operator >> (istream & input, rational & R)
{
	debug << "/* 5 */ Executing rational extraction operator for "
	      << &R << endl;
	int n = 0, d = 1;
	char c, x = ' ';
	bool good = false;
	while (isspace (input.peek()))
		input.get();
	c = input.peek ();
	if ((c == '+') || (c == '-') || isdigit (c))
	{
		input >> n; 
		good = true;
		c = input.peek ();
	}
	if (c == '/' || c == '.')
	{
		x = input.get();
		good = true;
	}
	if (x == '.')
		d = 0;
	c = input.peek ();
	if (isdigit (c))
	{
		input >> d; 
		good = true;
	}
	if (good && !input.fail())
	{
		if (x == '.')
			R = rational (stod (to_string (n) + x + to_string (d)));
		else
			R = rational (n, d);
	}
	else
		input.setstate (ios::failbit);
	return input;
}

/*******************************************************************************
* Number: 6                                                                    *
* Function: Insertion Operator                                                 *
*                                                                              *
* Parameters: output is an open ostream object.                                *
*             R is an existing rational object.                                *
* Return value: An implicit pointer to the passed ostream object.              *
* Description: This function will insert (write) appropriate values from R     *
*              into output.                                                    *
*******************************************************************************/

ostream & operator << (ostream & output, const rational & R)
{
	debug << "/* 6 */ Executing rational insertion operator for "
	      << &R << endl;
	output << R.num;
	if (R.denom != 1 && R.num != 0)
		output << '/' << R.denom;
	return output;
}

/*******************************************************************************
* Number: 7                                                                    *
* Function: Alternate Constructor                                              *
*                                                                              *
* Parameters: numerator is the value to be stored in the attribute "num".      *
*             denominator is the value to be stored in the attribute "denom".  *
* Return value: None                                                           *
* Description: This function will initialze the value of the newly constructed *
*              rational to numerator / denominator.                            *
*******************************************************************************/

rational::rational (const int numerator, const int denominator)
{
	debug << "/* 7 */ Executing rational (int,int) constructor for "
	      << this << endl;
	debug << numerator << "/" << denominator << endl;
	num = numerator;
	denom = denominator;
	reduce ();
}

/*******************************************************************************
* Number: 8                                                                    *
* Function: Alternate Constructor                                              *
*                                                                              *
* Parameters: I is an integer value to be stored in the attribute "num".       *
* Return value: None                                                           *
* Description: This function will initialze the value of the newly constructed *
*              rational to I / 1.                                              *
*******************************************************************************/

rational::rational (const int I)
{
	debug << "/* 8 */ Executing rational (int) constructor for "
	      << this << endl;
	num = I;
	denom = 1;
}

/*******************************************************************************
* Number: 9                                                                    *
* Function: Alternate Constructor                                              *
*                                                                              *
* Parameters: D is a double value to be converted to a rational number.        *
* Return value: None                                                           *
* Description: This function will initialze the value of the newly constructed *
*              rational by rounding the fractional part of D to 5 digit        *
*              precision and converting it to a rational with denom set to     *
*              100000.                                                         *
*******************************************************************************/

rational::rational (const double D)
{
	debug << "/* 9 */ Executing rational (double) constructor for "
	      << this << endl;
	stringstream ss;
	bool neg = D < 0 ? true : false;
	ss << showpoint << fixed << setprecision(5) << abs(D);
	int whole, fraction;
	char dot;
	ss >> whole >> dot >> fraction;
	debug << "D = " << D << endl;
	debug << "pieces = " << whole << "." << fraction << endl;
	rational w (whole, 1);
	debug << "w = " << w << endl;
	rational f (fraction, 100000);
	debug << "f = " << f << endl;
	*this = w + f;
	num = neg ? -num : num;
}

/*******************************************************************************
* Number: 12                                                                   *
* Function: Operator !=                                                        *
*                                                                              *
* Parameters: R is an existing rational object.                                *
* Return value: a boolean value.                                               *
* Description: This function will return true if *this != R.                   *
*******************************************************************************/

bool rational::operator != (const rational & R) const
{
	debug << "/* 12 */ Executing rational != operator for " << this
	      << " and " << &R << endl;
	return (num * R.denom) != (R.num * denom);
}

/*******************************************************************************
* Number: 13                                                                   *
* Function: Operator >                                                         *
*                                                                              *
* Parameters: R is an existing rational object.                                *
* Return value: a boolean value.                                               *
* Description: This function will return true if *this > R.                    *
*******************************************************************************/

bool rational::operator > (const rational & R) const
{
	debug << "/* 13 */ Executing rational > operator for " << this
	      << " and " << &R << endl;
	return (num * R.denom) > (R.num * denom);
}

/*******************************************************************************
* Number: 14                                                                   *
* Function: Operator >=                                                        *
*                                                                              *
* Parameters: R is an existing rational object.                                *
* Return value: a boolean value.                                               *
* Description: This function will return true if *this >= R.                   *
*******************************************************************************/

bool rational::operator >= (const rational & R) const
{
	debug << "/* 14 */ Executing rational >= operator for " << this
	      << " and " << &R << endl;
	return (num * R.denom) >= (R.num * denom);
}

/*******************************************************************************
* Number: 15                                                                   *
* Function: Operator ==                                                        *
*                                                                              *
* Parameters: R is an existing rational object.                                *
* Return value: a boolean value.                                               *
* Description: This function will return true if *this == R.                   *
*******************************************************************************/

bool rational::operator == (const rational & R) const
{
	debug << "/* 15 */ Executing rational == operator for " << this
	      << " and " << &R << endl;
	return (num * R.denom) == (R.num * denom);
}

/*******************************************************************************
* Number: 16                                                                   *
* Function: Operator <                                                         *
*                                                                              *
* Parameters: R is an existing rational object.                                *
* Return value: a boolean value.                                               *
* Description: This function will return true if *this < R.                    *
*******************************************************************************/

bool rational::operator < (const rational & R) const
{
	debug << "/* 16 */ Executing rational < operator for " << this
	      << " and " << &R << endl;
	return (num * R.denom) < (R.num * denom);
}

/*******************************************************************************
* Number: 17                                                                   *
* Function: Operator <=                                                        *
*                                                                              *
* Parameters: R is an existing rational object.                                *
* Return value: a boolean value.                                               *
* Description: This function will return true if *this <= R.                   *
*******************************************************************************/

bool rational::operator <= (const rational & R) const
{
	debug << "/* 17 */ Executing rational <= operator for " << this
	      << " and " << &R << endl;
	return (num * R.denom) <= (R.num * denom);
}

/*******************************************************************************
* Number: 18                                                                   *
* Function: Operator +                                                         *
*                                                                              *
* Parameters: R is an existing rational object.                                *
* Return value: a newly instantiated rational object.                          *
* Description: This function will return the sum of *this and R.               *
*******************************************************************************/

rational rational::operator + (const rational & R) const
{
	debug << "/* 18 */ Executing rational + operator for " << this
	      << " and " << &R << endl;
	rational sum;
	sum.num = (num * R.denom) + (R.num * denom);
	sum.denom = denom * R.denom;
	sum.reduce ();
	return sum;
}

/*******************************************************************************
* Number: 19                                                                   *
* Function: Operator /                                                         *
*                                                                              *
* Parameters: R is an existing rational object.                                *
* Return value: a newly instantiated rational object.                          *
* Description: This function will return the result of *this / R.              *
*******************************************************************************/

rational rational::operator / (const rational & R) const
{
	rational quotient;
	debug << "/* 19 */ Executing rational / operator for " << this
	      << " and " << &R << endl;
	quotient.num = num * R.denom;
	quotient.denom = denom * R.num;
	quotient.reduce ();
	return quotient;
}

/*******************************************************************************
* Number: 20                                                                   *
* Function: Operator -                                                         *
*                                                                              *
* Parameters: R is an existing rational object.                                *
* Return value: a newly instantiated rational object.                          *
* Description: This function will return the result of *this - R.              *
*******************************************************************************/

rational rational::operator - (const rational & R) const
{
	debug << "/* 20 */ Executing rational - operator for " << this
	      << " and " << &R << endl;
	rational diff;
	diff.num = (num * R.denom) - (R.num * denom);
	diff.denom = denom * R.denom;
	diff.reduce ();
	return diff;
}

/*******************************************************************************
* Number: 21                                                                   *
* Function: Operator *                                                         *
*                                                                              *
* Parameters: R is an existing rational object.                                *
* Return value: a newly instantiated rational object.                          *
* Description: This function will return the product of *this and R.           *
*******************************************************************************/

rational rational::operator * (const rational & R) const
{
	debug << "/* 21 */ Executing rational * operator for " << this
	      << " and " << &R << endl;
	rational product;
	product.num = num * R.num;
	product.denom = denom * R.denom;
	product.reduce ();
	return product;
}

/*******************************************************************************
* Number: 22                                                                   *
* Function: Operator *=                                                        *
*                                                                              *
* Parameters: R is an existing rational object.                                *
* Return value: the rational object *this (left side operand).                 *
* Description: This function will store the product of *this and R in *this    *
*              and return *this.                                               *
*******************************************************************************/

rational rational::operator *= (const rational & R)
{
	debug << "/* 22 */ Executing rational *= operator for " << this
	      << " and " << &R << endl;
	*this = *this * R;
	return * this;
}

/*******************************************************************************
* Number: 23                                                                   *
* Function: Operator +=                                                        *
*                                                                              *
* Parameters: R is an existing rational object.                                *
* Return value: the rational object *this (left side operand).                 *
* Description: This function will store the sum of *this and R in *this and    *
*              return *this.                                                   *
*******************************************************************************/

rational rational::operator += (const rational & R)
{
	debug << "/* 23 */ Executing rational += operator for " << this
	      << " and " << &R << endl;
	*this = *this + R;
	return * this;
}

/*******************************************************************************
* Number: 24                                                                   *
* Function: Operator -=                                                        *
*                                                                              *
* Parameters: R is an existing rational object.                                *
* Return value: the rational object *this (left side operand).                 *
* Description: This function will store the result of *this - R in *this       *
*              and return *this.                                               *
*******************************************************************************/

rational rational::operator -= (const rational & R)
{
	debug << "/* 24 */ Executing rational -= operator for " << this
	      << " and " << &R << endl;
	*this = *this - R;
	return * this;
}

/*******************************************************************************
* Number: 25                                                                   *
* Function: Operator /=                                                        *
*                                                                              *
* Parameters: R is an existing rational object.                                *
* Return value: the rational object *this (left side operand).                 *
* Description: This function will store the result of *this / R in *this       *
*              and return *this.                                               *
*******************************************************************************/

rational rational::operator /= (const rational & R)
{
	debug << "/* 25 */ Executing rational /= operator for " << this
	      << " and " << &R << endl;
	*this = *this / R;
	return * this;
}

/*******************************************************************************
* Number: 26                                                                   *
* Function: Pre increment operator                                             *
*                                                                              *
* Parameters: None.                                                            *
* Return value: the rational object *this                                      *
* Description: This function will add 1 to *this and return *this.             *
*******************************************************************************/

rational rational::operator ++ ()
{
	debug << "/* 26 */ Executing rational pre ++ operator for "
	      << this << endl;
	num += denom;
	reduce ();
	return * this;
}

/*******************************************************************************
* Number: 27                                                                   *
* Function: Post increment operator                                            *
*                                                                              *
* Parameters: int flag indicating that this is the post increment operation.   *
* Return value: a newly instantiated rational object.                          *
* Description: This function will make a copy of *this. It will then add       *
*              1 to *this and return the copy.                                 *
*******************************************************************************/

rational rational::operator ++ (int)
{
	debug << "/* 27 */ Executing rational post ++ operator for "
	      << this << endl;
	rational copy = *this;
	num += denom;
	reduce ();
	return copy;
}

/*******************************************************************************
* Number: 28                                                                   *
* Function: Pre decrement operator                                             *
*                                                                              *
* Parameters: None.                                                            *
* Return value: the rational object *this                                      *
* Description: This function will subtract 1 from *this and return *this.      *
*******************************************************************************/

rational rational::operator -- ()
{
	debug << "/* 28 */ Executing rational pre -- operator for "
	      << this << endl;
	num -= denom;
	reduce ();
	return * this;
}

/*******************************************************************************
* Number: 29                                                                   *
* Function: Post decrement operator                                            *
*                                                                              *
* Parameters: int flag indicating that this is the post decrement operation.   *
* Return value: a newly instantiated rational object.                          *
* Description: This function will make a copy of *this. It will then subtract  *
*              1 from *this and return the copy.                               *
*******************************************************************************/

rational rational::operator -- (int)
{
	debug << "/* 29 */ Executing rational post -- operator for "
	      << this << endl;
	rational copy = *this;
	num -= denom;
	reduce ();
	return copy;
}
	
/*******************************************************************************
* Number: 30                                                                   *
* Function: operator int                                                       *
*                                                                              *
* Parameters: None.                                                            *
* Return value: an integer value.                                              *
* Description: This function will be used to cast a rational to an int.        *
*******************************************************************************/

rational::operator int () const
{
	debug << "/* 30 */ Executing rational int() operator for "
	      << this << endl;
	return num / denom;
}

/*******************************************************************************
* Number: 31                                                                   *
* Function: operator float                                                     *
*                                                                              *
* Parameters: None.                                                            *
* Return value: a single precision floating point value.                       *
* Description: This function will be used to cast a rational to a float.       *
*******************************************************************************/

rational::operator float () const
{
	debug << "/* 31 */ Executing rational float() operator for "
	      << this << endl;
	return float(num) / denom;
}

/*******************************************************************************
* Number: 32                                                                   *
* Function: operator float                                                     *
*                                                                              *
* Parameters: None.                                                            *
* Return value: a double precision floating point value.                       *
* Description: This function will be used to cast a rational to a double.      *
*******************************************************************************/

rational::operator double () const
{
	debug << "/* 32 */ Executing rational double() operator for "
	      << this << endl;
	return double(num) / denom;
}

/*******************************************************************************
* Number: 33                                                                   *
* Function: to_string friend function                                          *
*                                                                              *
* Parameters: R is an existing rational object.                                *
* Return value: a string object.                                               *
* Description: This function will create and return a string containing        *
*              "num/denom".                                                    *
*******************************************************************************/

string to_string (const rational & R)
{
	debug << "/* 33 */ Executing rational to_string method for "
	      << &R << endl;
	stringstream ss;
	ss << R;
	return ss.str();
}


/*******************************************************************************
* Number: 34                                                                   *
* Function: round member function                                              *
*                                                                              *
* Parameters: None                                                             *
* Return value: the rational object *this.                                     *
* Description: This function will round *this to the closest integer value.    *
*******************************************************************************/

rational rational::round ()
{
	debug << "/* 34 */ Executing rational round() method for "
	      << this << endl;
	num = int (std::round (double(num) / denom));
	denom = 1;
	return *this;
}
				
/*******************************************************************************
* Number: 35                                                                   *
* Function: round member function                                              *
*                                                                              *
* Parameters: D is the new value for the denominator.                          *
* Return value: the rational object *this.                                     *
* Description: This function will modify *this by setting denom to D and       *
*              setting num to the integer value that makes the modified value  *
*              as close to the original as possible.                           *
*******************************************************************************/

rational rational::round (unsigned D)
{
	debug << "/* 35 */ Executing rational round(unsigned) method for "
	      << this << endl;
	num = int (std::round (double(num) * D /denom));
	denom = D;
	reduce ();
	return *this;
}
	
/*******************************************************************************
* Number: 36                                                                   *
* Function: round friend function                                              *
*                                                                              *
* Parameters: R is an existing rational object.                                *
* Return value: a newly instantiated rational object.                          *
* Description: This function will calculate and return the closest integer     *
*              value to the rational stored in R.                              *
*******************************************************************************/

int round (const rational & R)
{
	debug << "/* 36 */ Executing round(rational) friend function for "
	      << &R << endl;
	return int (std::round (double(R.num) / R.denom));
}

/*******************************************************************************
* Number: 37                                                                   *
* Function: round friend function                                              *
*                                                                              *
* Parameters: R is an existing rational object.                                *
*             D is the new value for the denominator.                          *
* Return value: a newly instantiated rational object.                          *
* Description: This function will create and return a new rational with denom  *
*              set to D and num set to the integer value that makes the new    *
*              rational as close to R as possible.                             *
*******************************************************************************/

rational round (const rational & R, unsigned D)
{
	debug << "/* 37 */ Executing round(rational,unsigned) friend function"
	      << "  for " << &R << endl;
	rational rounded;
	rounded.num = int (std::round (double(R.num) * D / R.denom));
	rounded.denom = D;
	rounded.reduce ();
	return rounded;
}

/*******************************************************************************
* Number: 38                                                                   *
* Function: reduce                                                             *
*                                                                              *
* Parameters: None.                                                            *
* Return value: the rational object *this.                                     *
* Description: This function will reduce *this to simplest terms by dividing   *
*              num and denom by their greatest common divisor (GCD).           *
*******************************************************************************/

rational rational::reduce ()
{
	debug << "/* 38 */ Executing rational reduce() method for "
	      << this << endl;
	if (denom == 0)
	{
		cerr << "Denominator cannot be 0; exiting program.\n";
		exit (1);
	}
	if (num == 0)
	{
		denom = 1;
		return * this;
	}
	if (denom < 0)
	{
		num = -num;
		denom = -denom;
	}
	int gcd = std::gcd (abs(num), abs(denom));
	num /= gcd;
	denom /= gcd;
	return * this;
}
			
/*******************************************************************************
* Number: 39                                                                   *
* Function: reciprocal                                                         *
*                                                                              *
* Parameters: None.                                                            *
* Return value: a newly instantiated rational object.                          *
* Description: This function will return the reciprocal of *this by creating   *
*              a new rational with num and denom reversed.                     *
*******************************************************************************/

rational rational::reciprocal () const
{
	debug << "/* 39 */ Executing rational reciprocal() method for "
	      << this << endl;
	return rational (denom, num);
}
