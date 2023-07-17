/*****************************************************************************/
/*                                                                           */
/* Assignment: CS 460 Project 1                                              */
/* Author: Dr. Watts                                                         */
/* Date: September 2022                                                      */
/* Modified by:                                                              */
/* Date:                                                                     */
/* Description: This file contains the description of a class called         */
/*      Syntactical Analyzer.                                                */
/*                                                                           */
/*****************************************************************************/

#ifndef SYNTACTICALANLYZER_H
#define SYNTACTICALANLYZER_H

#include <iostream>
#include <fstream>
#include "LexicalAnalyzer.h"

using namespace std;

/*****************************************************************************/
/*                                                                           */
/* Class name: Syntactical Analyzer                                          */
/* Description: This class is designed to define methods and attributes      */
/*      needed to perform Syntactical  Analysis on a Scheme input file.      */
/*                                                                           */
/*****************************************************************************/

class SyntacticalAnalyzer 
{
    public:
	SyntacticalAnalyzer (char * filename);
	~SyntacticalAnalyzer ();
    private:
	LexicalAnalyzer * lex;
	token_type token;
};

#endif
