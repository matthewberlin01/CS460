// Project: CS 460 Fall 2022 Project 3
// File: Object.cpp
// Author: Dr. Watts
// Modified by: 
// Desciption: Object class for Scheme to C++ translation

#include "Object.h"
#include <sstream>
#include <cstdlib>

#define DEBUG 0
#define debug if (DEBUG) cout

string nameof [] = {"unknown", "integer", "real", "string", "list", "rational", "boolean"};


/*******************************************************************************
* Function: Empty Constructor                                                  *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will create an empty Object                       *
*******************************************************************************/
Object::Object()
{
	type = NONE;
	intval = realval = 0;
	rationalVal = 0;
	boolVal = false;
}

/*******************************************************************************
* Function: Int Constructor	                                                   *
*                                                                              *
* Parameters: const int& value                                                 *
* Return value: None                                                           *
* Description: This function will create an int Object                         *
*******************************************************************************/
Object::Object (const int & value)
{
	type = INT;
	intval = value;
	realval = 0;
	rationalVal = 0;
	boolVal = false;
	MakeName ();
}

/*******************************************************************************
* Function: Real Constructor	                                               *
*                                                                              *
* Parameters: const double& value                                              *
* Return value: None                                                           *
* Description: This function will create a real Object                         *
*******************************************************************************/
Object::Object (const double & value)
{
	type = REAL;
	intval = 0;
	realval = value;
	rationalVal = 0;
	boolVal = false;
	MakeName ();
}

/*******************************************************************************
* Function: String Constructor	                                               *
*                                                                              *
* Parameters: const string& value                                              *
* Return value: None                                                           *
* Description: This function will create either a string, bool, or list		   *
*			   object based on the string given.							   *
*******************************************************************************/
Object::Object (const string & value)
{
	type = NONE;
	int sgn = 0, num = 0, dp = 0;
	if (value.length() > 1 && (value[0] == '+' || value[0] == '-'))
		sgn++;
	for (int i = sgn; i < value.size(); i++)
		if (isdigit (value[i]))
			num++;
		else if (value[i] == '.')
			dp++; 
	if (sgn + num + dp == value.size())
		if (dp == 0)
			*this = Object (atoi (value.c_str()));
		else if (dp == 1)
			*this = Object (atof (value.c_str()));
	if (type != NONE)
		return;
	int i = 0;
	while (isspace(value[i]))
		i++;
	if(value[i] == '#'){
		type = BOOLEAN;
		if(value[i+1] == 'f'){
			boolType = false;
			boolVal = "#f";
		}
		else{
			boolType = true;
			boolVal = "#t";
		}
			
		intval = realval = 0;
		rationalVal = 0;
		strval = "";
		MakeName();
		return;
	}
	if (value[i] != '(')
	{
		type = STRING;
		strval = value;
		intval = realval = 0;
		MakeName ();
		return;
	}
	debug << "value is " << value << endl;
	string temp;
	for (int i = 0; i < value.length(); i++)
	{
		temp += value[i];
		if (value[i] == '(' || value[i] == ')')
			temp += ' ';
	}
	debug << "temp is " << temp << endl;
	stringstream ss (temp.c_str(), ios_base::in);
	*this = Object (ss);
}

/*******************************************************************************
* Function: Rational Constructor	                                           *
*                                                                              *
* Parameters: const rational& value                                            *
* Return value: None                                                           *
* Description: This function will create a rational Object                     *
*******************************************************************************/
Object::Object (const rational & value){
	type = RATIONAL;
	intval = 0;
	realval = 0;
	rationalVal = value;
	MakeName();
}

/*******************************************************************************
* Function: == Operator		                                                   *
*                                                                              *
* Parameters: const Object& O                                                  *
* Return value: bool                                                           *
* Description: This function will try to return a bool based on the objects    *
*			   given, otherwise it will throw and catch the error.			   *
*******************************************************************************/
bool Object::operator == (const Object & O) const
{
    try
    {
	if (type == INT)
	{
		if (O.type == INT)
			return intval == O.intval;
		if (O.type == REAL)
			return intval == O.realval;
		if (O.type == RATIONAL)
			return intval == (int)O.rationalVal;
		throw "";
	}
	if (type == REAL)
	{
		if (O.type == INT)
			return realval == O.intval;
		if (O.type == REAL)
			return realval == O.realval;
		if (O.type == RATIONAL)
			return realval == (float)O.rationalVal;
		throw "";
	}
	if (type == RATIONAL){
		if(O.type == INT)
			return rationalVal == (rational)O.intval;
		if(O.type == REAL)
			return rationalVal == (rational)O.realval;
		if(O.type == RATIONAL)
			return rationalVal == O.rationalVal;
		throw "";
	}
	if (type == STRING)
	{
		if (O.type == STRING)
			return strval == O.strval;
		throw "";
	}
	if (type == LIST)
	{
		if (O.type == LIST)
		{
			if (listval.size() != O.listval.size())
				return false;
			for (int i = 0; i < listval.size(); i++)
				if (listval[i] != O.listval[i])
					return false;
			return true;
		}
		throw "";
	}
	throw "";
    }
    catch (const char * message)
    {
	cerr << "Wrong types for == operator: " << name << " and " << O.name
	     << " (" << nameof[type] << " and " << nameof[O.type] << ")\n"; 
	exit (1);
    }
}

/*******************************************************************************
* Function: != Operator		                                                   *
*                                                                              *
* Parameters: const Object& O                                                  *
* Return value: bool                                                           *
* Description: This function will try to return a bool based on the objects    *
*			   given, otherwise it will throw and catch the error.			   *
*******************************************************************************/
bool Object::operator != (const Object & O) const
{
    try
    {
	if (type == INT)
	{
		if (O.type == INT)
			return intval != O.intval;
		if (O.type == REAL)
			return intval != O.realval;
		if(O.type == RATIONAL)
			return intval != (int)O.rationalVal;
		throw "";
	}
	if (type == REAL)
	{
		if (O.type == INT)
			return realval != O.intval;
		if (O.type == REAL)
			return realval != O.realval;
		if(O.type == RATIONAL)
			return realval != (float)O.rationalVal;
		throw "";
	}
	if(type == RATIONAL){
		if(O.type == INT)
			return rationalVal != (rational)O.intval;
		if(O.type == REAL)
			return rationalVal != (rational)O.realval;
		if(O.type == RATIONAL)
			return rationalVal != O.rationalVal;
		throw "";
	}
	if (type == STRING)
	{
		if (O.type == STRING)
			return strval != O.strval;
		throw "";
	}
	if (type == LIST)
	{
		if (O.type == LIST)
		{
			if (listval.size() != O.listval.size())
				return true;
			for (int i = 0; i < listval.size(); i++)
				if (listval[i] != O.listval[i])
					return true;
			return false;
		}
		throw "";
	}
	throw "";
    }
    catch (const char * message)
    {
	cerr << "Wrong types for != operator: " << name << " and " << O.name
	     << " (" << nameof[type] << " and " << nameof[O.type] << ")\n"; 
	exit (1);
    }
}

/*******************************************************************************
* Function: < Operator		                                                   *
*                                                                              *
* Parameters: const Object& O                                                  *
* Return value: bool                                                           *
* Description: This function will try to return a bool based on the objects    *
*			   given, otherwise it will throw and catch the error.			   *
*******************************************************************************/
bool Object::operator < (const Object & O) const
{
    try
    {
	if (type == INT)
	{
		if (O.type == INT)
			return intval < O.intval;
		if (O.type == REAL)
			return intval < O.realval;
		if(O.type == RATIONAL)
			return intval < (int)O.rationalVal;
		throw "";
	}
	if (type == REAL)
	{
		if (O.type == INT)
			return realval < O.intval;
		if (O.type == REAL)
			return realval < O.realval;
		if(O.type == RATIONAL)
			return realval < (float)O.rationalVal;
		throw "";
	}
	if(type == RATIONAL){
		if(O.type == INT)
			return rationalVal < (rational)O.intval;
		if(O.type == REAL)
			return rationalVal < (rational)O.realval;
		if(O.type == RATIONAL)
			return rationalVal < O.rationalVal;
		throw "";
	}
	if (type == STRING)
	{
		if (O.type == STRING)
			return strval < O.strval;
		throw "";
	}
	throw "";
    }
    catch (const char * message)
    {
	cerr << "Wrong types for < operator: " << name << " and " << O.name
	     << " (" << nameof[type] << " and " << nameof[O.type] << ")\n"; 
	exit (1);
    }
}

/*******************************************************************************
* Function: <= Operator		                                                   *
*                                                                              *
* Parameters: const Object& O                                                  *
* Return value: bool                                                           *
* Description: This function will try to return a bool based on the objects    *
*			   given, otherwise it will throw and catch the error.			   *
*******************************************************************************/
bool Object::operator <= (const Object & O) const
{
    try
    {
	if (type == INT)
	{
		if (O.type == INT)
			return intval <= O.intval;
		if (O.type == REAL)
			return intval <= O.realval;
		if(O.type == RATIONAL)
			return intval <= (int)O.rationalVal;
		throw "";
	}
	if (type == REAL)
	{
		if (O.type == INT)
			return realval <= O.intval;
		if (O.type == REAL)
			return realval <= O.realval;
		if(O.type == RATIONAL)
			return realval <= (float)O.rationalVal;
		throw "";
	}
	if(type == RATIONAL){
		if (O.type == INT)
			return rationalVal <= (rational)O.intval;
		if (O.type == REAL)
			return rationalVal <= (rational)O.realval;
		if(O.type == RATIONAL)
			return rationalVal <= O.rationalVal;
		throw "";
	}
	if (type == STRING)
	{
		if (O.type == STRING)
			return strval <= O.strval;
		throw "";
	}
	throw "";
    }
    catch (const char * message)
    {
	cerr << "Wrong types for <= operator: " << name << " and " << O.name
	     << " (" << nameof[type] << " and " << nameof[O.type] << ")\n"; 
	exit (1);
    }
}

/*******************************************************************************
* Function: > Operator		                                                   *
*                                                                              *
* Parameters: const Object& O                                                  *
* Return value: bool                                                           *
* Description: This function will try to return a bool based on the objects    *
*			   given, otherwise it will throw and catch the error.			   *
*******************************************************************************/
bool Object::operator > (const Object & O) const
{
    try
    {
	if (type == INT)
	{
		if (O.type == INT)
			return intval > O.intval;
		if (O.type == REAL)
			return intval > O.realval;
		if(O.type == RATIONAL)
			return intval > (int)O.rationalVal;
		throw "";
	}
	if (type == REAL)
	{
		if (O.type == INT)
			return realval > O.intval;
		if (O.type == REAL)
			return realval > O.realval;
		if(O.type == RATIONAL)
			return realval > (float)O.rationalVal;
		throw "";
	}
	if(type == RATIONAL){
		if (O.type == INT)
			return rationalVal > (rational)O.intval;
		if (O.type == REAL)
			return rationalVal > (rational)O.realval;
		if(O.type == RATIONAL)
			return rationalVal > O.rationalVal;
		throw "";
	}
	if (type == STRING)
	{
		if (O.type == STRING)
			return strval > O.strval;
		throw "";
	}
	throw "";
    }
    catch (const char * message)
    {
	cerr << "Wrong types for > operator: " << name << " and " << O.name
	     << " (" << nameof[type] << " and " << nameof[O.type] << ")\n"; 
	exit (1);
    }
}

/*******************************************************************************
* Function: >= Operator		                                                   *
*                                                                              *
* Parameters: const Object& O                                                  *
* Return value: bool                                                           *
* Description: This function will try to return a bool based on the objects    *
*			   given, otherwise it will throw and catch the error.			   *
*******************************************************************************/
bool Object::operator >= (const Object & O) const
{
    try
    {
	if (type == INT)
	{
		if (O.type == INT)
			return intval >= O.intval;
		if (O.type == REAL)
			return intval >= O.realval;
		if(O.type == RATIONAL)
			return intval >= (int)O.rationalVal;
		throw "";
	}
	if (type == REAL)
	{
		if (O.type == INT)
			return realval >= O.intval;
		if (O.type == REAL)
			return realval >= O.realval;
		if(O.type == RATIONAL)
			return realval >= (float)O.rationalVal;
		throw "";
	}
	if(type == RATIONAL){
		if(O.type == INT)
			return rationalVal >= (rational)O.intval;
		if(O.type == REAL)
			return rationalVal >= (rational)O.realval;
		if(O.type == RATIONAL)
			return rationalVal >= O.rationalVal;
		throw "";
	}
	if (type == STRING)
	{
		if (O.type == STRING)
			return strval >= O.strval;
		throw "";
	}
	throw "";
    }
    catch (const char * message)
    {
	cerr << "Wrong types for >= operator: " << name << " and " << O.name
	     << " (" << nameof[type] << " and " << nameof[O.type] << ")\n"; 
	exit (1);
    }
}

/*******************************************************************************
* Function: + Operator		                                                   *
*                                                                              *
* Parameters: const Object& O                                                  *
* Return value: Object                                                         *
* Description: This function will try to create an object that has performed   *
*			   the + operation on elligible Object types, otherwise it will	   *
*			   throw and catch the error.									   *
*******************************************************************************/
Object Object::operator + (const Object & O) const
{
    try
    {
	if (type == INT)
	{
		if (O.type == INT)
			return Object (intval + O.intval);
		if (O.type == REAL)
			return Object (intval + O.realval);
		if(O.type == RATIONAL)
			return Object(intval + (int)O.rationalVal);
		throw "";
	}
	if (type == REAL)
	{
		if (O.type == INT)
			return Object (realval + O.intval);
		if (O.type == REAL)
			return Object (realval + O.realval);
		if(O.type == RATIONAL)
			return Object(realval + (int)O.rationalVal);
		throw "";
	}
	if(type == RATIONAL){
		if(O.type == INT)
			return Object(rationalVal + (rational)O.intval);
		if(O.type == REAL)
			return Object(rationalVal + (rational)O.realval);
		if(O.type == RATIONAL)
			return Object(rationalVal + O.rationalVal);
		throw "";
	}
	if (type == STRING)
	{
		if (O.type == STRING)
			return Object (strval + O.strval);
		throw "";
	}
	if (type == LIST)
	{
		if (O.type == LIST)
		{
			string n1 = name;
			n1[n1.size() - 1] = ' ';
			string n2 = O.name;
			n2[0] = ' ';
			return Object (n1 + n2);
		}
		throw "";
	}
	throw "";
    }
    catch (const char * message)
    {
	cerr << "Wrong types for + operator: " << name << " and " << O.name
	     << " (" << nameof[type] << " and " << nameof[O.type] << ")\n"; 
	exit (1);
    }
}

/*******************************************************************************
* Function: - Operator		                                                   *
*                                                                              *
* Parameters: const Object& O                                                  *
* Return value: Object                                                         *
* Description: This function will try to create an object that has performed   *
*			   the - operation on elligible Object types, otherwise it will	   *
*			   throw and catch the error.									   *
*******************************************************************************/
Object Object::operator - (const Object & O) const
{
    try
    {
	if (type == INT)
	{
		if (O.type == INT)
			return Object (intval - O.intval);
		if (O.type == REAL)
			return Object (intval - O.realval);
		if(O.type == RATIONAL)
			return Object (intval - (int)O.rationalVal);
		throw "";
	}
	if (type == REAL)
	{
		if (O.type == INT)
			return Object (realval - O.intval);
		if (O.type == REAL)
			return Object (realval - O.realval);
		if(O.type == RATIONAL)
			return Object(realval - (float)O.rationalVal);
		throw "";
	}
	if(type == RATIONAL){
		if(O.type == INT)
			return Object(rationalVal - (rational)O.intval);
		if(O.type == REAL)
			return Object(rationalVal - (rational)O.realval);
		if(O.type == RATIONAL)
			return Object(rationalVal - O.rationalVal);
		throw "";
	}
	throw "";
    }
    catch (const char * message)
    {
	cerr << "Wrong types for - operator: " << name << " and " << O.name
	     << " (" << nameof[type] << " and " << nameof[O.type] << ")\n"; 
	exit (1);
    }
}

/*******************************************************************************
* Function: * Operator		                                                   *
*                                                                              *
* Parameters: const Object& O                                                  *
* Return value: Object                                                         *
* Description: This function will try to create an object that has performed   *
*			   the * operation on elligible Object types, otherwise it will	   *
*			   throw and catch the error.									   *
*******************************************************************************/
Object Object::operator * (const Object & O) const
{
    try
    {
	if (type == INT)
	{
		if (O.type == INT)
			return Object (intval * O.intval);
		if (O.type == REAL)
			return Object (intval * O.realval);
		if(O.type == RATIONAL)
			return Object (intval * (int)O.rationalVal);
		throw "";
	}
	if (type == REAL)
	{
		if (O.type == INT)
			return Object (realval * O.intval);
		if (O.type == REAL)
			return Object (realval * O.realval);
		if(O.type == RATIONAL)
			return Object(realval * (float)O.rationalVal);
		throw "";
	}
	if(type == RATIONAL){
		if(O.type == INT)
			return Object(rationalVal * (rational)O.intval);
		if(O.type == REAL)
			return Object(rationalVal * (rational)O.realval);
		if(O.type == RATIONAL)
			return Object(rationalVal * O.rationalVal);
			throw "";
	}
	throw "";
    }
    catch (const char * message)
    {
	cerr << "Wrong types for * operator: " << name << " and " << O.name
	     << " (" << nameof[type] << " and " << nameof[O.type] << ")\n"; 
	exit (1);
    }
}

/*******************************************************************************
* Function: / Operator		                                                   *
*                                                                              *
* Parameters: const Object& O                                                  *
* Return value: Object                                                         *
* Description: This function will try to create an object that has performed   *
*			   the / operation on elligible Object types, otherwise it will	   *
*			   throw and catch the error.									   *
*******************************************************************************/
Object Object::operator / (const Object & O) const
{
    try
    {
	if (type == INT)
	{
		if (O.type == INT)
		{
			if (O.intval == 0)
				throw "division by 0";
			return Object ((rational)intval / (rational)O.intval);
		}
		if (O.type == REAL)
		{
			if (O.realval == 0)
				throw "division by 0";
			return Object (intval / O.realval);
		}
		if(O.type == RATIONAL){
			if((float)O.rationalVal == 0)
				throw "division by 0";
			return Object(intval / (int)O.rationalVal);
		}
		throw "";
	}
	if (type == REAL)
	{
		if (O.type == INT)
		{
			if (O.intval == 0)
				throw "division by 0";
			return Object (realval / O.intval);
		}
		if (O.type == REAL)
		{
			if (O.realval == 0)
				throw "division by 0";
			return Object (realval / O.realval);
		}
		if(O.type == RATIONAL){
			if((float)O.rationalVal == 0)
				throw "division by 0";
			return Object(realval / (float)O.rationalVal);
		}
		throw "";
	}
	if(type == RATIONAL){
		if(O.type == INT){
			if(O.intval == 0)
				throw "division by 0";
			return Object(rationalVal / (rational)O.intval);
		}
		if(O.type == REAL){
			if(O.realval == 0)
				throw "division by 0";
			return Object(rationalVal / (rational)O.realval);
		}
		if(O.type == RATIONAL){
			if((float)O.rationalVal == 0)
				throw "division by 0";
			return Object(rationalVal / O.rationalVal);
		}
		throw "";
	}
	throw "";
    }
    catch (const char * message)
    {
	cerr << "Wrong types for / operator: " << name << " and " << O.name
	     << " (" << nameof[type] << " and " << nameof[O.type] << ")\n"; 
	exit (1);
    }
}

/*******************************************************************************
* Function: % Operator		                                                   *
*                                                                              *
* Parameters: const Object& O                                                  *
* Return value: Object                                                         *
* Description: This function will try to create an object that has performed   *
*			   the % operation on elligible Object types, otherwise it will	   *
*			   throw and catch the error.									   *
*******************************************************************************/
Object Object::operator % (const Object & O) const
{
    try
    {
	if (type == INT && O.type == INT)
	{
		if (O.intval == 0)
			throw "modulo by 0";
		return Object (intval % O.intval);
	}
	throw "";
    }
    catch (const char * message)
    {
	cerr << "Wrong types for % operator: " << name << " and " << O.name
	     << " (" << nameof[type] << " and " << nameof[O.type] << ")\n"; 
	exit (1);
    }
}

/*******************************************************************************
* Function: ! Operator		                                                   *
*                                                                              *
* Parameters: None                            			                       *
* Return value: Object                                                         *
* Description: This function will try to create an object that has performed   *
*			   the ! operation on elligible Object types, otherwise it will	   *
*			   throw and catch the error.									   *
*******************************************************************************/
Object Object::operator !()const{
	try{
		if(type == BOOLEAN){
			if(!boolType){
				return Object("#t");
			}
			else{
				return Object("#f");
			}
		}
		throw "";
	}
	catch(const char* message){
		cerr << "Wrong type for ! operator: " << name
	     << " (" << nameof[type] << ")\n"; 
		exit (1);
	}
}

/*******************************************************************************
* Function: && Operator		                                                   *
*                                                                              *
* Parameters: const Object& O                                                  *
* Return value: bool                                                           *
* Description: This function will try to return a bool based on the objects    *
*			   given, otherwise it will throw and catch the error.			   *
*******************************************************************************/
bool Object::operator &&(const Object& O)const{
	try{
		if(type == BOOLEAN){
			if(O.type == BOOLEAN){
				return boolType && O.boolType;
			}
		}
		throw "";
	}
	catch(const char* message){
		cerr << "Wrong types for && operator: " << name << " and " << O.name
	     << " (" << nameof[type] << " and " << nameof[O.type] << ")\n"; 
		exit (1);
	}
}


/*******************************************************************************
* Function: numberp		    		                                           *
*                                                                              *
* Parameters: const Object& O                                                  *
* Return value: bool                                                           *
* Description: This function will try to return a bool based on the objects    *
*			   given, otherwise it will throw and catch the error.			   *
*******************************************************************************/
bool numberp (const Object & O) 
{
	if (O.type == INT || O.type == REAL || O.type == RATIONAL)
		return true;
	return false;
}

/*******************************************************************************
* Function: symbolp		                                                       *
*                                                                              *
* Parameters: const Object& O                                                  *
* Return value: bool                                                           *
* Description: This function will try to return a bool based on the objects    *
*			   given, otherwise it will throw and catch the error.			   *
*******************************************************************************/
bool symbolp (const Object & O) 
{
	if (O.type == STRING)
		return true;
	return false;
}

/*******************************************************************************
* Function: listp		                                                       *
*                                                                              *
* Parameters: const Object& O                                                  *
* Return value: bool                                                           *
* Description: This function will try to return a bool based on the objects    *
*			   given, otherwise it will throw and catch the error.			   *
*******************************************************************************/
bool listp (const Object & O) 
{
	if (O.type == LIST)
		return true;
	return false;
}

/*******************************************************************************
* Function: zerop		                                                       *
*                                                                              *
* Parameters: const Object& O                                                  *
* Return value: bool                                                           *
* Description: This function will try to return a bool based on the objects    *
*			   given, otherwise it will throw and catch the error.			   *
*******************************************************************************/
bool zerop (const Object & O) 
{
    try
    {
	if (O.type != INT || O.type != REAL || O.type != RATIONAL)
		throw "type";
	if (O.type == INT && O.intval == 0)
		return true;
	if (O.type == REAL && O.realval == 0)
		return true;
	if (O.type == RATIONAL && (float)O.rationalVal == 0)
		return true;
	return false;
    }
    catch (const char * message)
    {
	cerr << "Wrong " << message << " for zero? predicate\n";
	exit (1);
    }
}

/*******************************************************************************
* Function: nullp		                                                       *
*                                                                              *
* Parameters: const Object& O                                                  *
* Return value: bool                                                           *
* Description: This function will try to return a bool based on the objects    *
*			   given, otherwise it will throw and catch the error.			   *
*******************************************************************************/
bool nullp (const Object & O) 
{
	if (O.type == LIST && O.listval.size() == 0)
		return true;
	return false;
}

/*******************************************************************************
* Function: stringp		                                                       *
*                                                                              *
* Parameters: const Object& O                                                  *
* Return value: bool                                                           *
* Description: This function will try to return a bool based on the objects    *
*			   given, otherwise it will throw and catch the error.			   *
*******************************************************************************/
bool stringp (const Object & O) 
{
	if (O.type == STRING)
		return true;
	return false;
}

/*******************************************************************************
* Function: listop		                                                       *
*                                                                              *
* Parameters: const string& s, const Object& O                                 *
* Return value: Object                                                         *
* Description: This function will try to create an Object of type list based   *
*			   on the string and Object provided, otherwise it will throw and  *
*			   catch the error.												   *
*******************************************************************************/
Object listop (const string & S, const Object & O)
{// will handle list operator as well as car, cdr, etc.
    try
    {
	debug << "listop name : " << S << endl;
	if (S == "list")
	{
		Object T;
		T.type = LIST;
		T.listval.push_back (O);
		T.MakeName ();
		return T;
	}
	if (O.type != LIST)
		throw "type";
	if (O.listval.size() < 1)
		throw "size";
	if (S.length() < 3 || S[0] != 'c' || S[S.length()-1] != 'r')
		throw "name";
	Object T = O;
	int i = S.length()-2;
	while (S[i] == 'd' || S[i] == 'a')
	{
		if (S[i] == 'd')
			T.listval.erase (T.listval.begin());
		else if (S[i] == 'a')
			T = Object (T.listval[0]);
		i--;
	}
	if (S[i] == 'c')
	{
		T.MakeName ();
		return T;
	}
	debug << S << " : " << S[i] << endl;
	throw "name";	
    }
    catch (const char * message)
    {
	cerr << "Wrong " << message << " for list operation function: " << S;
	if (message[0] == 't')
		cerr << " (" << nameof[O.type]<< ")"; 
	else if (message[0] == 's')
		cerr << " (" << O.listval.size() << ")"; 
	else if (message[0] == 'n')
		cerr << " (list operator may need 2 parameters)"; 
	cerr << endl;
	exit (1);
    }
}

/*******************************************************************************
* Function: listop		                                                       *
*                                                                              *
* Parameters: const string& s, const Object& O1, const Object& O2              *
* Return value: Object                                                         *
* Description: This function will try to create an Object of type list based   *
*			   on the string and Objects provided, otherwise it will throw and *
*			   catch the error.												   *
*******************************************************************************/
Object listop (const string & S, const Object & O1, const Object O2)
{// will handle cons and append operators
    try
    {
	if (S == "cons")
	{
		if (O2.type != LIST)
			throw "type";
		Object T = O2;
		T.listval.insert (T.listval.begin(), O1);
		T.MakeName();
		return T;
	}
	if (S == "append")
	{
		if (O1.type != LIST || O2.type != LIST)
			throw "type";
		Object T = O1;
		for (int i = 0; i < O2.listval.size(); i++)
			T.listval.push_back(O2.listval[i]);
		T.MakeName();
		return T;
	}
	debug << S << endl;
	throw "name";	
    }
    catch (const char * message)
    {
	cerr << "Wrong " << message << " for list operation function: " << S;
	if (message[0] == 't')
		cerr << " (" << nameof[O1.type]<< " or " << nameof[O2.type]<< ")"; 
	else if (message[0] == 's')
		cerr << " (" << O1.listval.size() << " or " << O2.listval.size() << ")"; 
	else if (message[0] == 'n')
		cerr << " (list operator may accept only 1 parameter)"; 
	cerr << endl;
	exit (1);
    }
}

/*******************************************************************************
* Function: round		                                                       *
*                                                                              *
* Parameters: const Object& O                                                  *
* Return value: Object                                                         *
* Description: This function will try to create an Object whose value has been *
*			   rounded as long as the round operation is elligible on that 	   *
*			   Object type, otherwise it will throw and catch the error.	   *
*******************************************************************************/
Object round (const Object & O)
{
    try
    {
	int r = 0;
	if (O.type == INT)
		r = O.intval;
	else if (O.type == REAL)
		r = O.realval + 0.5;
	else if(O.type == RATIONAL)
		r = round(O.rationalVal);
	else 
		throw "type";
	return Object(r);
    }
    catch (const char * message)
    {
	cerr << "Wrong " << message << " for round function parameter: " << O.name;
	if (message[0] == 't')
		cerr << " (" << nameof[O.type]<< ")"; 
	cerr << endl;
	exit (1);
    }
}
/*******************************************************************************
* Function: << operator		                                                   *
*                                                                              *
* Parameters: ostream& outs, const Object& O                                   *
* Return value: ostream&                                                       *
* Description: This function will write the Object's name to the output stream *
*			   and return the updated output stream.						   *
*******************************************************************************/
ostream & operator << (ostream & outs, const Object & O)
{
	outs << O.name;
	return outs;
}

/*******************************************************************************
* Function: StringStream Constructor                                           *
*                                                                              *
* Parameters: stringstream& ss                                                 *
* Return value: None                                                           *
* Description: This function will create multiple objects based on the list	   *
*			   provided from the stringstream. If the list is not formatted	   *
*			   properly, it will throw and catch the error.					   *
*******************************************************************************/
Object::Object (stringstream & ss)
{
    try
    {
	type = LIST;
	intval = realval = 0;
	char achar;
	ss >> achar;
	if (achar != '(')
		throw "(";
	bool endfound = false;
	while (!endfound)
	{
		Object temp;
		while (isspace (achar = ss.peek()))
			ss.get (achar);
		if (achar == '(')
			temp = Object (ss);
		else if (achar == ')')
		{
			endfound = true;
			ss.get (achar);
		}
		else
		{
			string astring;
			ss >> astring;
			debug << "astring is " << astring << endl;
			if (astring[astring.size()-1] == ')')
			{
				endfound = true;
				astring = astring.substr (0, astring.size()-1);
			}
			if (astring.size() > 0)
				temp = Object (astring);
		}
		if (temp.type != NONE)
		{
			debug << "Adding " << temp << " to LIST Object\n";
			listval.push_back (temp);
		}
	}
	MakeName ();
	debug << "name is " << name << endl;
    }
    catch (const char * message)
    {
	cerr << "message" << endl;
	exit (1);
    }
}

/*******************************************************************************
* Function: MakeName                                                           *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will create the name for the Object.			   *
*******************************************************************************/
void Object::MakeName ()
{
	stringstream ss;
	switch (type)
	{
		case INT:
			ss << intval;
			break;
		case REAL:
			ss << realval;
			break;
		case RATIONAL:
			ss << rationalVal;
			break;
		case BOOLEAN:
			ss << boolVal;
			break;
		case STRING:
			ss << strval;
			break;
		case LIST:
			ss << '(';
			if (listval.size() > 0)
				ss << listval[0].name;
			for (int i = 1; i < listval.size(); i++)
				ss << ' ' << listval[i].name;
			ss << ')';
			break;
		default:
			ss << "";
	}
	name = ss.str();
}
