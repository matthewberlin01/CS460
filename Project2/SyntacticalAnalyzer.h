/*****************************************************************************/
/*                                                                           */
/* Assignment: CS 460 Project 2                                              */
/* Author: Matthew Berlin                                                    */
/* Date: November 27 2022                                                    */
/* Description: This file contains the description of a class called         */
/*      Syntactical Analyzer.                                                */
/*                                                                           */
/*****************************************************************************/

#ifndef SYNTACTICALANLYZER_H
#define SYNTACTICALANLYZER_H

#include <iostream>
#include <fstream>
#include <set>
#include "LexicalAnalyzer.h"

using namespace std;

/*****************************************************************************/
/*                                                                           */
/* Class name: Syntactical Analyzer                                          */
/* Description: This class is designed to define methods and attributes      */
/*      needed to perform Syntactical Analysis on a Scheme input file.       */
/*                                                                           */
/*****************************************************************************/

class SyntacticalAnalyzer 
{
    public:
	SyntacticalAnalyzer (char * filename);
	~SyntacticalAnalyzer ();
    private:
	void program();			//first pass complete
	void moreDefines();
	void define();
	void stmtList();
	void stmt();
	void literal();
	void quotedLit();
	void logicalLit();
	void moreTokens();
	void paramList();
	void elsePart();
	void stmtPair();
	void stmtPairBody();
	void assignPair();
	void moreAssigns();
	void action();
	void anyOtherToken();

	void ReportRule(int);

	LexicalAnalyzer * lex;
	token_type token;
	ofstream ruleFile;	//p2
	
};

#endif
