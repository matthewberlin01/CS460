/*****************************************************************************/
/*                                                                           */
/* Assignment: CS 460 Project 1                                              */
/* Author: Dr. Watts                                                         */
/* Date: September 2022                                                      */
/* Modified by:                                                              */
/* Date:                                                                     */
/* Description: This file contains the description of a class called         */
/*      LexicalAnalyzer.                                                     */
/*                                                                           */
/*****************************************************************************/

#ifndef LEXICALANLYZER_H
#define LEXICALANLYZER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

/*****************************************************************************/
/*                                                                           */
/* Class name: LexicalAnalyzer                                               */
/* Description: This class is designed to define methods and attributes      */
/*      needed to perform Lexical Analysis on a Scheme input file.           */
/*                                                                           */
/*****************************************************************************/

enum token_type {NONE = 1, IDENT_T = 2, NUMLIT_T = 3, LISTOP_T = 4, PLUS_T = 5, MINUS_T = 6,
                GT_T = 7, LT_T = 8, CONS_T = 9, IF_T = 10, COND_T = 11, ELSE_T = 12, DISPLAY_T = 13,
                NEWLINE_T = 14, AND_T = 15, OR_T = 16, NOT_T = 17, DEFINE_T = 18, LET_T = 19,
                MODULO_T = 20, ROUND_T = 21, STRLIT_T = 22, NUMBERP_T = 23, LISTP_T = 24, ZEROP_T = 25,
                NULLP_T = 26, STRINGP_T = 27, GTE_T = 28, LTE_T = 29, DIV_T = 30, MULT_T = 31,
                EQUALTO_T = 32,LPAREN_T = 33, RPAREN_T = 34, SQUOTE_T = 35, ERROR_T = 36, EOF_T = 37};

class LexicalAnalyzer 
{
    public:
	LexicalAnalyzer (char * filename);
	~LexicalAnalyzer ();
	token_type GetToken ();
	string GetTokenName (token_type t) const;
	string GetLexeme () const;
    int GetErrors();
	void ReportError (const string & msg);
	void WriteListingFile(const string & msg);
	void WriteTokenFile(const string & msg);
	void WriteDebugFile(const string & msg);
	ofstream debugFile;	// .dbg
	
    private:
	int ColumnPosition(char);

	ifstream input; 	// .ss 
	ofstream listingFile;	// .lst
	ofstream tokenFile;	// .p1
	token_type token;
	string line;
	int linenum;
	int pos;
	string lexeme;
	string messageText;
	int errors;

	std::vector<token_type> tokenState = {NONE, IDENT_T, NUMLIT_T, LISTOP_T, PLUS_T, MINUS_T, GT_T,
                                          LT_T, CONS_T, IF_T, COND_T, ELSE_T, DISPLAY_T, NEWLINE_T, AND_T,
                                          OR_T, NOT_T, DEFINE_T, LET_T, MODULO_T, ROUND_T, STRLIT_T, NUMBERP_T,
                                          LISTP_T, ZEROP_T, NULLP_T, STRINGP_T, GTE_T, LTE_T, DIV_T, MULT_T,
                                          EQUALTO_T,LPAREN_T, RPAREN_T, SQUOTE_T, ERROR_T, EOF_T};

	std::vector<std::string> tokenNames = {"NONE", "IDENT_T", "NUMLIT_T", "LISTOP_T", "PLUS_T",
                                           "MINUS_T", "GT_T", "LT_T","CONS_T", "IF_T", "COND_T", "ELSE_T",
                                           "DISPLAY_T", "NEWLINE_T", "AND_T", "OR_T", "NOT_T", "DEFINE_T",
                                           "LET_T", "MODULO_T", "ROUND_T", "STRLIT_T", "NUMBERP_T", "LISTP_T", "ZEROP_T",
                                           "NULLP_T", "STRINGP_T", "GTE_T", "LTE_T","DIV_T", "MULT_T", "EQUALTO_T",
                                           "LPAREN_T", "RPAREN_T", "SQUOTE_T", "ERROR_T", "EOF_T"};

	std::vector<std::vector<int>> tokenFlowState = {
	{0,	1,	8,	1,	1,	1,	-ERROR_T,	2,	13,	14,	-DIV_T,	-MULT_T,	3,	-EQUALTO_T,	15,	16,	-LPAREN_T,	-RPAREN_T,	-SQUOTE_T,	7,	-ERROR_T,	0},
	{-IDENT_T,	1,	1,	1,	1,	1,	-IDENT_T,	1,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T, 1,	-IDENT_T},
	{-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	2,	-NUMLIT_T,	-NUMLIT_T,	4,	-NUMLIT_T,	3,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T},
	{-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	3,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T},
	{-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	3,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T},
	{-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	6,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-ERROR_T,	-NUMLIT_T,	-ERROR_T},
	{-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	6,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T,	-NUMLIT_T},
	{7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	-STRLIT_T,	7,	7},
	{-IDENT_T,	1,	1,	9,	10,	1,	-IDENT_T,	1,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	1,	-IDENT_T},
	{-IDENT_T,	1,	1,	1,	9,	12,	-IDENT_T,	1,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	1,	-IDENT_T},
	{-IDENT_T,	1,	1,	11,	10,	12,	-IDENT_T,	1,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	1,	-IDENT_T},
	{-IDENT_T,	1,	1,	1,	1,	12,	-IDENT_T,	1,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	-IDENT_T,	1,	-IDENT_T},
	{-LISTOP_T,	1,	1,	1,	1,	1,	-LISTOP_T,	1,	-LISTOP_T,	-LISTOP_T,	-LISTOP_T,	-LISTOP_T,	-LISTOP_T,	-LISTOP_T,	-LISTOP_T,	-LISTOP_T,	-LISTOP_T,	-LISTOP_T,	-LISTOP_T,	-LISTOP_T,	1,	-LISTOP_T},
	{-PLUS_T,	-PLUS_T,	-PLUS_T,	-PLUS_T,	-PLUS_T,	-PLUS_T,	-PLUS_T,	2,	-PLUS_T,	-PLUS_T,	-PLUS_T,	-PLUS_T,	2,	-PLUS_T,	-PLUS_T,	-PLUS_T,	-PLUS_T,	-PLUS_T,	-PLUS_T,	-PLUS_T,	-PLUS_T,	-PLUS_T},
	{-MINUS_T,	-MINUS_T,	-MINUS_T,	-MINUS_T,	-MINUS_T,	-MINUS_T,	-MINUS_T,	2,	-MINUS_T,	-MINUS_T,	-MINUS_T,	-MINUS_T,	2,	-MINUS_T,	-MINUS_T,	-MINUS_T,	-MINUS_T,	-MINUS_T,	-MINUS_T,	-MINUS_T,	-MINUS_T,	-MINUS_T},
	{-GT_T,	-GT_T,	-GT_T,	-GT_T,	-GT_T,	-GT_T,	-GT_T,	-GT_T,	-GT_T,	-GT_T,	-GT_T,	-GT_T,	-GT_T,	-GTE_T,	-GT_T,	-GT_T,	-GT_T,	-GT_T,	-GT_T,	-GT_T,	-GT_T,	-GT_T},
	{-LT_T,	-LT_T,	-LT_T,	-LT_T,	-LT_T,	-LT_T,	-LT_T,	-LT_T,	-LT_T,	-LT_T,	-LT_T,	-LT_T,	-LT_T,	-LTE_T,	-LT_T,	-LT_T,	-LT_T,	-LT_T,	-LT_T,	-LT_T,	-LT_T,	-LT_T}
};

	std::map<std::string, token_type> keywordMap = {{"cons", CONS_T}, {"if", IF_T}, {"cond", COND_T}, {"else", ELSE_T},
	{"display", DISPLAY_T}, {"newline", NEWLINE_T}, {"and", AND_T}, {"or", OR_T}, {"not", NOT_T}, {"define", DEFINE_T},
	{"let", LET_T}, {"number?", NUMBERP_T}, {"list?", LISTP_T}, {"zero?", ZEROP_T}, {"null?", NULLP_T}, {"string?", STRINGP_T},
	{"modulo", MODULO_T}, {"round", ROUND_T}};
};

#endif
