/*****************************************************************
* Assignment: Exercise 4 - rational class                        *
* Author: CS 460 Students                                        *
* Date: Fall 2022                                                *
* File: rational.h                                               *
*                                                                *
* Description: This file contains the definition of a class      *
*              called rational. Objects of the rational class    *
*              will contain a fraction's numerator (signed)      *
*              and denominator (unsigned > 0).                   *
*****************************************************************/

#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
using namespace std;

class rational
{
    public:

	// Constructors
	
/* X */     rational ();
/* 2 */     rational (const rational & R);
	
	// Destructor 
	
/* 3 */     ~rational (); 
	
	//Assignment operator
	
/* 4 */     rational & operator = (const rational & R);
	
	// Input and Output Operators
	
/* 5 */     friend istream & operator >>
				(istream & input, rational & R);
/* 6 */     friend ostream & operator <<
				(ostream & output, const rational & R);

//-----------------------------------------------------------------//
	
	// Additional constructors constructors
	
/* 7 */     rational (const int numerator, const int denominator);
/* 8 */     rational (const int I);
/* 9 */     rational (const double D);
	
	// Logical Operators
       
/* 12 */     bool operator != (const rational & R) const;
/* 13 */     bool operator > (const rational & R) const;
/* 14 */     bool operator >= (const rational & R) const;
/* 15 */     bool operator == (const rational & R) const;
/* 16 */     bool operator < (const rational & R) const;
/* 17 */     bool operator <= (const rational & R) const;
	
	// Arithmetic Operators

/* 18 */     rational operator + (const rational & R) const;
/* 19 */     rational operator / (const rational & R) const;
/* 20 */     rational operator - (const rational & R) const;
/* 21 */     rational operator * (const rational & R) const;
/* 22 */     rational operator *= (const rational & R);
/* 23 */     rational operator += (const rational & R);
/* 24 */     rational operator -= (const rational & R);
/* 25 */     rational operator /= (const rational & R);
/* 26 */     rational operator ++ (); // Pre
/* 27 */     rational operator ++ (int); // Post
/* 28 */     rational operator -- (); // Pre
/* 29 */     rational operator -- (int); // Post
	
	// Conversion Operators
	
/* 30 */     operator int () const;
/* 31 */     operator float () const;
/* 32 */     operator double () const;
/* 33 */     friend string to_string (const rational & R);

/* 34 */     rational round ();				
/* 35 */     rational round (unsigned D);	
/* 36 */     friend int round (const rational & R);
/* 37 */     friend rational round (const rational & R, unsigned D);
	
	// Other Methods
	
/* 38 */     rational reduce ();			
/* 39 */     rational reciprocal () const;	

    private:
	int num;
	int denom;
};

#endif
