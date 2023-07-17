/*******************************************************************************
* Assignment: Project 2                                                        *
* Author: Matthew Berlin                                                       *
* Date: 22 Nov. 2022                                                           *
* File: SyntacticalAnalyzer.cpp                                                *
*                                                                              *
* Description: This file contains all the function definitions of the		   *
* functions within the SyntacticalAnalyzer.h								   *
*******************************************************************************/

#include "SyntacticalAnalyzer.h"

using namespace std;

/*******************************************************************************
* Function: SyntacticalAnalyzer                                                *
*                                                                              *
* Parameters: filename                                                         *
* Return value:                                                                *
* Description: This function will create the SyntacticalAnalyzer               *
*******************************************************************************/

SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
	lex = new LexicalAnalyzer (filename);
	token_type t;
	string p2Name = filename;
	p2Name = p2Name.substr(0, p2Name.length() - 3);
	p2Name += ".p2";
	ruleFile.open(p2Name);
	token = lex->GetToken();

	program ();
}

/*******************************************************************************
* Function: deconstructor                                                      *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will delete the LexicalAnalyzer lex               *
*******************************************************************************/
SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	ruleFile.close();
	delete lex;
}

/*******************************************************************************
* Function: program                                                            *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will call the rules defined in program            *
*******************************************************************************/
void SyntacticalAnalyzer::program (){
	static set<token_type> firsts;
	static set<token_type> follows;

	firsts.insert(LPAREN_T);
	firsts.insert(EOF_T);

	follows.insert(EOF_T);

	while(firsts.find(token) == firsts.end()){
		token = lex->GetToken();
	}

	switch(token){
		case LPAREN_T:
			ReportRule(1);
			if(token == LPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), "(");
			}

			define();

			if(token == LPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), "(");
			}

			moreDefines();

			if(token != EOF_T){
				lex->ReportError(lex->GetLexeme(), "EndOfFile");
			}
			break;
		default:
			while(follows.find(token) == follows.end()){
				lex->ReportError(lex->GetLexeme());
				token = lex->GetToken();
			}
			break;
	}

	
}

/*******************************************************************************
* Function: moreDefines                                                        *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will call the rules defined in moreDefines based  *
* on the current token.														   *
*******************************************************************************/
void SyntacticalAnalyzer::moreDefines(){
	static set<token_type> firsts;
	static set<token_type> follows;
	
	firsts.insert(IDENT_T);
	firsts.insert(DEFINE_T);
	firsts.insert(EOF_T);

	follows.insert(EOF_T);
	
	while(firsts.find(token) == firsts.end()){
		lex->ReportError(lex->GetLexeme());
		token = lex->GetToken();
	}

	switch(token){
		case IDENT_T:
			ReportRule(3);
			token = lex->GetToken();
			stmtList();
			if(token == RPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), ")");
			}
			break;

		case DEFINE_T:
			ReportRule(2);
			define();
			if(token == LPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), "(");
			}
			moreDefines();
			break;
		default:
			while(follows.find(token) == follows.end()){
				lex->ReportError(lex->GetLexeme());
				token = lex->GetToken();
			}
			break;
	}
}

/*******************************************************************************
* Function: define                                                             *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will call the rules defined in eefine based on    *
* the current token.														   *
*******************************************************************************/
void SyntacticalAnalyzer::define(){
	static set<token_type> firsts;
	static set<token_type> follows;

	firsts.insert(DEFINE_T);
	firsts.insert(EOF_T);
	
	follows.insert(LPAREN_T);
	follows.insert(EOF_T);

	while(firsts.find(token) == firsts.end()){
		lex->ReportError(lex->GetLexeme());
		token = lex->GetToken();
	}

	switch(token){
		case DEFINE_T:
			ReportRule(4);
			if(token == DEFINE_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), "define");
			}

			if(token == LPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), "(");
			}

			if(token == IDENT_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), "ident");
			}

			paramList();

			if(token == RPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), ")");
			}

			stmt();

			stmtList();

			if(token == RPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), ")");
			}
			break;
		default:
			while(follows.find(token) == follows.end()){
				lex->ReportError(lex->GetLexeme());
				token = lex->GetToken();
			}
			break;
	}
}

/*******************************************************************************
* Function: stmtList                                                           *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will call the rules defined in stmtList based on  *
* the current token.														   *
*******************************************************************************/
void SyntacticalAnalyzer::stmtList(){
	static set<token_type> firsts;
	static set<token_type> follows;

	firsts.insert(IDENT_T);
	firsts.insert(LPAREN_T);
	firsts.insert(NUMLIT_T);
	firsts.insert(STRLIT_T);
	firsts.insert(SQUOTE_T);
	firsts.insert(TRUE_T);
	firsts.insert(FALSE_T);
	firsts.insert(RPAREN_T);
	firsts.insert(EOF_T);

	follows.insert(RPAREN_T);
	follows.insert(EOF_T);
	
	while(firsts.find(token) == firsts.end()){
		lex->ReportError(lex->GetLexeme());
		token = lex->GetToken();
	}

	switch(token){
		case IDENT_T:
			ReportRule(5);
			stmt();
			stmtList();
			break;
		case LPAREN_T:
			ReportRule(5);
			stmt();
			stmtList();
			break;
		case NUMLIT_T:
			ReportRule(5);
			stmt();
			stmtList();
			break;
		case STRLIT_T:
			ReportRule(5);
			stmt();
			stmtList();
			break;
		case SQUOTE_T:
			ReportRule(5);
			stmt();
			stmtList();
			break;
		case TRUE_T:
			ReportRule(5);
			stmt();
			stmtList();
			break;
		case FALSE_T:
			ReportRule(5);
			stmt();
			stmtList();
			break;
		case RPAREN_T:
			ReportRule(6);
			break;
		default:
			while(follows.find(token) == follows.end()){
				lex->ReportError(lex->GetLexeme());
				token = lex->GetToken();
			}
			break;
	}
}

/*******************************************************************************
* Function: stmt                                                               *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will call the rules defined in stmt based on the  *
* current token.							    							   *
*******************************************************************************/
void SyntacticalAnalyzer::stmt(){
	static set<token_type> firsts;
	static set<token_type> follows;

	firsts.insert(IDENT_T);
	firsts.insert(LPAREN_T);
	firsts.insert(NUMLIT_T);
	firsts.insert(STRLIT_T);
	firsts.insert(SQUOTE_T);
	firsts.insert(TRUE_T);
	firsts.insert(FALSE_T);
	firsts.insert(EOF_T);
	
	follows.insert(RPAREN_T);
	follows.insert(IDENT_T);
	follows.insert(LPAREN_T);
	follows.insert(NUMLIT_T);
	follows.insert(STRLIT_T);
	follows.insert(SQUOTE_T);
	follows.insert(TRUE_T);
	follows.insert(FALSE_T);
	follows.insert(EOF_T);

	while(firsts.find(token) == firsts.end()){
		lex->ReportError(lex->GetLexeme());
		token = lex->GetToken();
	}

	switch(token){
		case IDENT_T:
			ReportRule(8);
			token = lex->GetToken();
			break;
		case LPAREN_T:
			ReportRule(9);
			token = lex->GetToken();

			action();

			if(token == RPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), ")");
			}
			break;
		case NUMLIT_T:
			ReportRule(7);
			literal();
			break;
		case STRLIT_T:
			ReportRule(7);
			literal();
			break;
		case SQUOTE_T:
			ReportRule(7);
			literal();
			break;
		case TRUE_T:
			ReportRule(7);
			literal();
			break;
		case FALSE_T:
			ReportRule(7);
			literal();
			break;
		default:
			while(follows.find(token) == follows.end()){
				lex->ReportError(lex->GetLexeme());
				token = lex->GetToken();
			}
			break;
	}
}

/*******************************************************************************
* Function: literal                                                            *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will call the rules defined in literal based on   *
* the current token.														   *
*******************************************************************************/
void SyntacticalAnalyzer::literal(){
	static set<token_type> firsts;
	static set<token_type> follows;

	firsts.insert(NUMLIT_T);
	firsts.insert(STRLIT_T);
	firsts.insert(SQUOTE_T);
	firsts.insert(TRUE_T);
	firsts.insert(FALSE_T);
	firsts.insert(EOF_T);

	follows.insert(RPAREN_T);
	follows.insert(IDENT_T);
	follows.insert(LPAREN_T);
	follows.insert(NUMLIT_T);
	follows.insert(STRLIT_T);
	follows.insert(SQUOTE_T);
	follows.insert(TRUE_T);
	follows.insert(FALSE_T);
	follows.insert(EOF_T);

	while(firsts.find(token) == firsts.end()){
		lex->ReportError(lex->GetLexeme());
		token = lex->GetToken();
	}

	switch(token){
		case NUMLIT_T:
			ReportRule(10);
			token = lex->GetToken();
			break;
		case STRLIT_T:
			ReportRule(11);
			token = lex->GetToken();
			break;
		case SQUOTE_T:
			ReportRule(12);
			token = lex->GetToken();
			quotedLit();
			break;
		case TRUE_T:
			ReportRule(13);
			logicalLit();
			break;
		case FALSE_T:
			ReportRule(13);
			logicalLit();
			break;
		default:
			while(follows.find(token) == follows.end()){
				lex->ReportError(lex->GetLexeme());
				token = lex->GetToken();
			}
			break;
	}
}

/*******************************************************************************
* Function: quotedLit                                                          *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will call the rules defined in quotedLit based on *
* the current token.														   *
*******************************************************************************/
void SyntacticalAnalyzer::quotedLit(){
	static set<token_type> firsts;
	static set<token_type> follows;

	firsts.insert(LPAREN_T);
	firsts.insert(IDENT_T);
	firsts.insert(NUMLIT_T);
	firsts.insert(STRLIT_T);
	firsts.insert(IF_T);
	firsts.insert(DISPLAY_T);
	firsts.insert(NEWLINE_T);
	firsts.insert(LISTOP1_T);
	firsts.insert(LISTOP2_T);
	firsts.insert(AND_T);
	firsts.insert(OR_T);
	firsts.insert(NOT_T);
	firsts.insert(DEFINE_T);
	firsts.insert(LET_T);
	firsts.insert(NUMBERP_T);
	firsts.insert(LISTP_T);
	firsts.insert(ZEROP_T);
	firsts.insert(NULLP_T);
	firsts.insert(STRINGP_T);
	firsts.insert(PLUS_T);
	firsts.insert(MINUS_T);
	firsts.insert(DIV_T);
	firsts.insert(MULT_T);
	firsts.insert(MODULO_T);
	firsts.insert(ROUND_T);
	firsts.insert(EQUALTO_T);
	firsts.insert(GT_T);
	firsts.insert(LT_T);
	firsts.insert(GTE_T);
	firsts.insert(LTE_T);
	firsts.insert(SQUOTE_T);
	firsts.insert(COND_T);
	firsts.insert(ELSE_T);
	firsts.insert(TRUE_T);
	firsts.insert(FALSE_T);
	firsts.insert(EOF_T);

	follows.insert(RPAREN_T);
	follows.insert(IDENT_T);
	follows.insert(LPAREN_T);
	follows.insert(NUMLIT_T);
	follows.insert(STRLIT_T);
	follows.insert(SQUOTE_T);
	follows.insert(TRUE_T);
	follows.insert(FALSE_T);
	follows.insert(EOF_T);

	while(firsts.find(token) == firsts.end()){
		lex->ReportError(lex->GetLexeme());
		token = lex->GetToken();
	}

	if(firsts.find(token) != firsts.end()){
		ReportRule(14);
		anyOtherToken();
	}
	else{
		while(follows.find(token) == follows.end()){
				lex->ReportError(lex->GetLexeme());
				token = lex->GetToken();
		}
	}
}

/*******************************************************************************
* Function: logicalLit                                                         *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will call the rules defined in logicalLit based   *
* on the current token.														   *
*******************************************************************************/
void SyntacticalAnalyzer::logicalLit(){
	static set<token_type> firsts;
	static set<token_type> follows;

	firsts.insert(TRUE_T);
	firsts.insert(FALSE_T);
	firsts.insert(EOF_T);

	follows.insert(RPAREN_T);
	follows.insert(IDENT_T);
	follows.insert(LPAREN_T);
	follows.insert(NUMLIT_T);
	follows.insert(STRLIT_T);
	follows.insert(SQUOTE_T);
	follows.insert(TRUE_T);
	follows.insert(FALSE_T);
	follows.insert(EOF_T);

	while(firsts.find(token) == firsts.end()){
		lex->ReportError(lex->GetLexeme());
		token = lex->GetToken();
	}

	switch(token){
		case TRUE_T:
			ReportRule(15);
			token = lex->GetToken();
			break;
		case FALSE_T:
			ReportRule(16);
			token = lex->GetToken();
			break;
		default:
			while(follows.find(token) == follows.end()){
				lex->ReportError(lex->GetLexeme());
				token = lex->GetToken();
			}
			break;
	}
}

/*******************************************************************************
* Function: moreTokens                                                         *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will call the rules defined in moreTokens based   *
* on the current token.														   *
*******************************************************************************/
void SyntacticalAnalyzer::moreTokens(){
	static set<token_type> firsts;
	static set<token_type> follows;

	firsts.insert(LPAREN_T);
	firsts.insert(IDENT_T);
	firsts.insert(NUMLIT_T);
	firsts.insert(STRLIT_T);
	firsts.insert(IF_T);
	firsts.insert(DISPLAY_T);
	firsts.insert(NEWLINE_T);
	firsts.insert(LISTOP1_T);
	firsts.insert(LISTOP2_T);
	firsts.insert(AND_T);
	firsts.insert(OR_T);
	firsts.insert(NOT_T);
	firsts.insert(DEFINE_T);
	firsts.insert(LET_T);
	firsts.insert(NUMBERP_T);
	firsts.insert(LISTP_T);
	firsts.insert(ZEROP_T);
	firsts.insert(NULLP_T);
	firsts.insert(STRINGP_T);
	firsts.insert(PLUS_T);
	firsts.insert(MINUS_T);
	firsts.insert(DIV_T);
	firsts.insert(MULT_T);
	firsts.insert(MODULO_T);
	firsts.insert(ROUND_T);
	firsts.insert(EQUALTO_T);
	firsts.insert(GT_T);
	firsts.insert(LT_T);
	firsts.insert(GTE_T);
	firsts.insert(LTE_T);
	firsts.insert(SQUOTE_T);
	firsts.insert(COND_T);
	firsts.insert(ELSE_T);
	firsts.insert(TRUE_T);
	firsts.insert(FALSE_T);
	firsts.insert(RPAREN_T);
	firsts.insert(EOF_T);

	follows.insert(RPAREN_T);
	follows.insert(EOF_T);

	while(firsts.find(token) == firsts.end()){
		lex->ReportError(lex->GetLexeme());
		token = lex->GetToken();
	}

	if(token == RPAREN_T){
		ReportRule(18);
		return;
	}
	else if(firsts.find(token) != firsts.end()){
		ReportRule(17);
		anyOtherToken();
		moreTokens();
	}
	else{
		while(follows.find(token) == follows.end()){
				lex->ReportError(lex->GetLexeme());
				token = lex->GetToken();
		}
	}
}

/*******************************************************************************
* Function: paramList                                                          *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will call the rules defined in paramList based on *
* the current token.														   *
*******************************************************************************/
void SyntacticalAnalyzer::paramList(){
	static set<token_type> firsts;
	static set<token_type> follows;

	firsts.insert(IDENT_T);
	firsts.insert(RPAREN_T);
	firsts.insert(EOF_T);

	follows.insert(RPAREN_T);
	follows.insert(EOF_T);

	while(firsts.find(token) == firsts.end()){
		lex->ReportError(lex->GetLexeme());
		token = lex->GetToken();
	}

	switch(token){
		case IDENT_T:
			ReportRule(19);
			token = lex->GetToken();
			paramList();
			break;
		case RPAREN_T:
			ReportRule(20);
			break;
		default:
			while(follows.find(token) == follows.end()){
				lex->ReportError(lex->GetLexeme());
				token = lex->GetToken();
			}
			break;
	}
}

/*******************************************************************************
* Function: elsePart                                                           *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will call the rules defined in elsePart based on  *
* the current token.														   *
*******************************************************************************/
void SyntacticalAnalyzer::elsePart(){
	static set<token_type> firsts;
	static set<token_type> follows;

	firsts.insert(IDENT_T);
	firsts.insert(LPAREN_T);
	firsts.insert(NUMLIT_T);
	firsts.insert(STRLIT_T);
	firsts.insert(SQUOTE_T);
	firsts.insert(TRUE_T);
	firsts.insert(FALSE_T);
	firsts.insert(RPAREN_T);
	firsts.insert(EOF_T);
	
	follows.insert(RPAREN_T);
	follows.insert(EOF_T);

	while(firsts.find(token) == firsts.end()){
		lex->ReportError(lex->GetLexeme());
		token = lex->GetToken();
	}

	switch(token){
		case IDENT_T:
			ReportRule(21);
			stmt();
			break;
		case LPAREN_T:
			ReportRule(21);
			stmt();
			break;
		case NUMLIT_T:
			ReportRule(21);
			stmt();
			break;
		case STRLIT_T:
			ReportRule(21);
			stmt();
			break;
		case SQUOTE_T:
			ReportRule(21);
			stmt();
			break;
		case TRUE_T:
			ReportRule(21);
			stmt();
			break;
		case FALSE_T:
			ReportRule(21);
			stmt();
			break;
		case RPAREN_T:
			ReportRule(22);
			break;
		default:
			while(follows.find(token) == follows.end()){
				lex->ReportError(lex->GetLexeme());
				token = lex->GetToken();
			}
			break;
	}
}

/*******************************************************************************
* Function: stmtPair                                                           *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will call the rules defined in stmtPair based on  *
* the current token.														   *
*******************************************************************************/
void SyntacticalAnalyzer::stmtPair(){
	static set<token_type> firsts;
	static set<token_type> follows;

	firsts.insert(LPAREN_T);
	firsts.insert(RPAREN_T);
	firsts.insert(EOF_T);

	follows.insert(RPAREN_T);
	follows.insert(EOF_T);

	while(firsts.find(token) == firsts.end()){
		lex->ReportError(lex->GetLexeme());
		token = lex->GetToken();
	}

	switch(token){
		case LPAREN_T:
			ReportRule(23);
			token = lex->GetToken();
			stmtPairBody();
			break;
		case RPAREN_T:
			ReportRule(24);
			break;
		default:
			while(follows.find(token) == follows.end()){
				lex->ReportError(lex->GetLexeme());
				token = lex->GetToken();
			}
			break;
	}
}

/*******************************************************************************
* Function: stmtPairBody                                                       *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will call the rules defined in stmtPairBody based *
* on the current token.														   *
*******************************************************************************/
void SyntacticalAnalyzer::stmtPairBody(){
	static set<token_type> firsts;
	static set<token_type> follows;

	firsts.insert(ELSE_T);
	firsts.insert(IDENT_T);
	firsts.insert(LPAREN_T);
	firsts.insert(NUMLIT_T);
	firsts.insert(STRLIT_T);
	firsts.insert(SQUOTE_T);
	firsts.insert(TRUE_T);
	firsts.insert(FALSE_T);
	firsts.insert(EOF_T);

	follows.insert(RPAREN_T);
	follows.insert(EOF_T);

	while(firsts.find(token) == firsts.end()){
		lex->ReportError(lex->GetLexeme());
		token = lex->GetToken();
	}

	switch(token){
		case ELSE_T:
			ReportRule(26);
			token = lex->GetToken();
			stmt();

			if(token == RPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), ")");
			}
			break;
		case IDENT_T:
			ReportRule(25);
			stmt();
			stmt();

			if(token == RPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), ")");
			}

			stmtPair();
			break;
		case LPAREN_T:
			ReportRule(25);
			stmt();
			stmt();

			if(token == RPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), ")");
			}

			stmtPair();
			break;
		case NUMLIT_T:
			ReportRule(25);
			stmt();
			stmt();

			if(token == RPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), ")");
			}

			stmtPair();
			break;
		case STRLIT_T:
			ReportRule(25);
			stmt();
			stmt();

			if(token == RPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), ")");
			}

			stmtPair();
			break;
		case SQUOTE_T:
			ReportRule(25);
			stmt();
			stmt();

			if(token == RPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), ")");
			}

			stmtPair();
			break;
		case TRUE_T:
			ReportRule(25);
			stmt();
			stmt();

			if(token == RPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), ")");
			}

			stmtPair();
			break;
		case FALSE_T:
			ReportRule(25);
			stmt();
			stmt();

			if(token == RPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), ")");
			}

			stmtPair();
			break;
		default:
			while(follows.find(token) == follows.end()){
				lex->ReportError(lex->GetLexeme());
				token = lex->GetToken();
			}
			break;
	}
}

/*******************************************************************************
* Function: assignPair                                                         *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will call the rules defined in assignPair based   *
* on the current token.														   *
*******************************************************************************/
void SyntacticalAnalyzer::assignPair(){
	static set<token_type> firsts;
	static set<token_type> follows;

	firsts.insert(LPAREN_T);
	firsts.insert(EOF_T);

	follows.insert(LPAREN_T);
	follows.insert(RPAREN_T);
	follows.insert(EOF_T);

	while(firsts.find(token) == firsts.end()){
		lex->ReportError(lex->GetLexeme());
		token = lex->GetToken();
	}

	switch(token){
		case LPAREN_T:
			ReportRule(27);
			token = lex->GetToken();

			if(token == IDENT_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), "ident");
			}

			stmt();

			if(token == RPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), ")");
			}
		default:
			while(follows.find(token) == follows.end()){
				lex->ReportError(lex->GetLexeme());
				token = lex->GetToken();
			}
			break;
	}
}

/*******************************************************************************
* Function: moreAssigns                                                        *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will call the rules defined in moreAssigns based  *
* on the current token.														   *
*******************************************************************************/
void SyntacticalAnalyzer::moreAssigns(){
	static set<token_type> firsts;
	static set<token_type> follows;

	firsts.insert(LPAREN_T);
	firsts.insert(RPAREN_T);
	firsts.insert(EOF_T);

	follows.insert(RPAREN_T);
	follows.insert(EOF_T);

	while(firsts.find(token) == firsts.end()){
		lex->ReportError(lex->GetLexeme());
		token = lex->GetToken();
	}

	switch(token){
		case LPAREN_T:
			ReportRule(28);
			assignPair();
			moreAssigns();
			break;
		case RPAREN_T:
			ReportRule(29);
			break;
		default:
			while(follows.find(token) == follows.end()){
				lex->ReportError(lex->GetLexeme());
				token = lex->GetToken();
			}
			break;
	}
}

/*******************************************************************************
* Function: action                                                             *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will call the rules defined in action based on    *
* the current token.														   *
*******************************************************************************/
void SyntacticalAnalyzer::action(){
	static set<token_type> firsts;
	static set<token_type> follows;

	firsts.insert(IF_T);
	firsts.insert(COND_T);
	firsts.insert(LET_T);
	firsts.insert(LISTOP1_T);
	firsts.insert(LISTOP2_T);
	firsts.insert(AND_T);
	firsts.insert(OR_T);
	firsts.insert(NOT_T);
	firsts.insert(NUMBERP_T);
	firsts.insert(LISTP_T);
	firsts.insert(ZEROP_T);
	firsts.insert(NULLP_T);
	firsts.insert(STRINGP_T);
	firsts.insert(PLUS_T);
	firsts.insert(MINUS_T);
	firsts.insert(DIV_T);
	firsts.insert(MULT_T);
	firsts.insert(MODULO_T);
	firsts.insert(ROUND_T);
	firsts.insert(EQUALTO_T);
	firsts.insert(GT_T);
	firsts.insert(LT_T);
	firsts.insert(GTE_T);
	firsts.insert(LTE_T);
	firsts.insert(IDENT_T);
	firsts.insert(DISPLAY_T);
	firsts.insert(NEWLINE_T);
	firsts.insert(EOF_T);
	
	follows.insert(RPAREN_T);
	follows.insert(EOF_T);

	while(firsts.find(token) == firsts.end()){
		lex->ReportError(lex->GetLexeme());
		token = lex->GetToken();
	}

	switch(token){
		case IF_T:
			ReportRule(30);
			token = lex->GetToken();
			stmt();
			stmt();
			elsePart();
			break;
		case COND_T:
			ReportRule(31);
			token = lex->GetToken();

			if(token == LPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), "(");
			}

			stmtPairBody();
			break;
		case LET_T:
			ReportRule(32);
			token = lex->GetToken();

			if(token == LPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), "(");
			}

			moreAssigns();

			if(token == RPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), ")");
			}

			stmt();
			stmtList();
			break;
		case LISTOP1_T:
			ReportRule(33);
			token = lex->GetToken();
			stmt();
			break;
		case LISTOP2_T:
			ReportRule(34);
			token = lex->GetToken();
			stmt();
			stmt();
			break;
		case AND_T:
			ReportRule(35);
			token = lex->GetToken();
			stmtList();
			break;
		case OR_T:
			ReportRule(36);
			token = lex->GetToken();
			stmtList();
			break;
		case NOT_T:
			ReportRule(37);
			token = lex->GetToken();
			stmt();
			break;
		case NUMBERP_T:
			ReportRule(38);
			token = lex->GetToken();
			stmt();
			break;
		case LISTP_T:
			ReportRule(39);
			token = lex->GetToken();
			stmt();
			break;
		case ZEROP_T:
			ReportRule(40);
			token = lex->GetToken();
			stmt();
			break;
		case NULLP_T:
			ReportRule(41);
			token = lex->GetToken();
			stmt();
			break;
		case STRINGP_T:
			ReportRule(42);
			token = lex->GetToken();
			stmt();
			break;
		case PLUS_T:
			ReportRule(43);
			token = lex->GetToken();
			stmtList();
			break;
		case MINUS_T:
			ReportRule(44);
			token = lex->GetToken();
			stmt();
			stmtList();
			break;
		case DIV_T:
			ReportRule(45);
			token = lex->GetToken();
			stmt();
			stmtList();
			break;
		case MULT_T:
			ReportRule(46);
			token = lex->GetToken();
			stmtList();
			break;
		case MODULO_T:
			ReportRule(47);
			token = lex->GetToken();
			stmt();
			stmt();
			break;
		case ROUND_T:
			ReportRule(48);
			token = lex->GetToken();
			stmt();
			break;
		case EQUALTO_T:
			ReportRule(49);
			token = lex->GetToken();
			stmtList();
			break;
		case GT_T:
			ReportRule(50);
			token = lex->GetToken();
			stmtList();
			break;
		case LT_T:
			ReportRule(51);
			token = lex->GetToken();
			stmtList();
			break;
		case GTE_T:
			ReportRule(52);
			token = lex->GetToken();
			stmtList();
			break;
		case LTE_T:
			ReportRule(53);
			token = lex->GetToken();
			stmtList();
			break;
		case IDENT_T:
			ReportRule(54);
			token = lex->GetToken();
			stmtList();
			break;
		case DISPLAY_T:
			ReportRule(55);
			token = lex->GetToken();
			stmt();
			break;
		case NEWLINE_T:
			ReportRule(56);
			token = lex->GetToken();
			break;
		default:
			while(follows.find(token) == follows.end()){
				lex->ReportError(lex->GetLexeme());
				token = lex->GetToken();
			}
			break;
	}
}

/*******************************************************************************
* Function: anyOtherToken                                                      *
*                                                                              *
* Parameters: None                                                             *
* Return value: None                                                           *
* Description: This function will call the rules defined in anyOtherToken      *
* based on the current token.												   *
*******************************************************************************/
void SyntacticalAnalyzer::anyOtherToken(){
	static set<token_type> firsts;
	static set<token_type> follows;

	firsts.insert(LPAREN_T);
	firsts.insert(IDENT_T);
	firsts.insert(NUMLIT_T);
	firsts.insert(STRLIT_T);
	firsts.insert(IF_T);
	firsts.insert(DISPLAY_T);
	firsts.insert(NEWLINE_T);
	firsts.insert(LISTOP1_T);
	firsts.insert(LISTOP2_T);
	firsts.insert(AND_T);
	firsts.insert(OR_T);
	firsts.insert(NOT_T);
	firsts.insert(DEFINE_T);
	firsts.insert(LET_T);
	firsts.insert(NUMBERP_T);
	firsts.insert(LISTP_T);
	firsts.insert(ZEROP_T);
	firsts.insert(NULLP_T);
	firsts.insert(STRINGP_T);
	firsts.insert(PLUS_T);
	firsts.insert(MINUS_T);
	firsts.insert(DIV_T);
	firsts.insert(MULT_T);
	firsts.insert(MODULO_T);
	firsts.insert(ROUND_T);
	firsts.insert(EQUALTO_T);
	firsts.insert(GT_T);
	firsts.insert(LT_T);
	firsts.insert(GTE_T);
	firsts.insert(LTE_T);
	firsts.insert(SQUOTE_T);
	firsts.insert(COND_T);
	firsts.insert(ELSE_T);
	firsts.insert(TRUE_T);
	firsts.insert(FALSE_T);
	firsts.insert(EOF_T);

	follows.insert(LPAREN_T);
	follows.insert(IDENT_T);
	follows.insert(NUMLIT_T);
	follows.insert(STRLIT_T);
	follows.insert(IF_T);
	follows.insert(DISPLAY_T);
	follows.insert(NEWLINE_T);
	follows.insert(LISTOP1_T);
	follows.insert(LISTOP2_T);
	follows.insert(AND_T);
	follows.insert(OR_T);
	follows.insert(NOT_T);
	follows.insert(DEFINE_T);
	follows.insert(LET_T);
	follows.insert(NUMBERP_T);
	follows.insert(LISTP_T);
	follows.insert(ZEROP_T);
	follows.insert(NULLP_T);
	follows.insert(STRINGP_T);
	follows.insert(PLUS_T);
	follows.insert(MINUS_T);
	follows.insert(DIV_T);
	follows.insert(MULT_T);
	follows.insert(MODULO_T);
	follows.insert(ROUND_T);
	follows.insert(EQUALTO_T);
	follows.insert(GT_T);
	follows.insert(LT_T);
	follows.insert(GTE_T);
	follows.insert(LTE_T);
	follows.insert(SQUOTE_T);
	follows.insert(COND_T);
	follows.insert(ELSE_T);
	follows.insert(TRUE_T);
	follows.insert(FALSE_T);
	follows.insert(EOF_T);

	while(firsts.find(token) == firsts.end()){
		lex->ReportError(lex->GetLexeme());
		token = lex->GetToken();
	}

	switch(token){
		case LPAREN_T:
			ReportRule(57);
			token = lex->GetToken();
			moreTokens();

			if(token == RPAREN_T){
				token = lex->GetToken();
			}
			else{
				lex->ReportError(lex->GetLexeme(), ")");
			}
			break;
		case IDENT_T:
			ReportRule(58);
			token = lex->GetToken();
			break;

		case NUMLIT_T:
			ReportRule(59);
			token = lex->GetToken();
			break;
		case STRLIT_T:
			ReportRule(60);
			token = lex->GetToken();
			break;
		case IF_T:
			ReportRule(61);
			token = lex->GetToken();
			break;
		case DISPLAY_T:
			ReportRule(62);
			token = lex->GetToken();
			break;
		case NEWLINE_T:
			ReportRule(63);
			token = lex->GetToken();
			break;
		case LISTOP1_T:
			ReportRule(64);
			token = lex->GetToken();
			break;
		case LISTOP2_T:
			ReportRule(65);
			token = lex->GetToken();
			break;
		case AND_T:
			ReportRule(66);
			token = lex->GetToken();
			break;
		case OR_T:
			ReportRule(67);
			token = lex->GetToken();
			break;
		case NOT_T:
			ReportRule(68);
			token = lex->GetToken();
			break;
		case DEFINE_T:
			ReportRule(69);
			token = lex->GetToken();
			break;
		case LET_T:
			ReportRule(70);
			token = lex->GetToken();
			break;
		case NUMBERP_T:
			ReportRule(71);
			token = lex->GetToken();
			break;
		case LISTP_T:
			ReportRule(72);
			token = lex->GetToken();
			break;
		case ZEROP_T:
			ReportRule(73);
			token = lex->GetToken();
			break;
		case NULLP_T:
			ReportRule(74);
			token = lex->GetToken();
			break;
		case STRINGP_T:
			ReportRule(75);
			token = lex->GetToken();
			break;
		case PLUS_T:
			ReportRule(76);
			token = lex->GetToken();
			break;
		case MINUS_T:
			ReportRule(77);
			token = lex->GetToken();
			break;
		case DIV_T:
			ReportRule(78);
			token = lex->GetToken();
			break;
		case MULT_T:
			ReportRule(79);
			token = lex->GetToken();
			break;
		case MODULO_T:
			ReportRule(80);
			token = lex->GetToken();
			break;
		case ROUND_T:
			ReportRule(81);
			token = lex->GetToken();
			break;
		case EQUALTO_T:
			ReportRule(82);
			token = lex->GetToken();
			break;
		case GT_T:
			ReportRule(83);
			token = lex->GetToken();
			break;
		case LT_T:
			ReportRule(84);
			token = lex->GetToken();
			break;
		case GTE_T:
			ReportRule(85);
			token = lex->GetToken();
			break;
		case LTE_T:
			ReportRule(86);
			token = lex->GetToken();
			break;
		case SQUOTE_T:
			ReportRule(87);
			token = lex->GetToken();
			anyOtherToken();
		case COND_T:
			ReportRule(88);
			token = lex->GetToken();
			break;
		case ELSE_T:
			ReportRule(89);
			token = lex->GetToken();
			break;
		case TRUE_T:
			ReportRule(90);
			token = lex->GetToken();
			break;
		case FALSE_T:
			ReportRule(91);
			token = lex->GetToken();
			break;
		default:
			while(follows.find(token) == follows.end()){
				lex->ReportError(lex->GetLexeme());
				token = lex->GetToken();
			}
			break;
	}
}

/*******************************************************************************
* Function: ReportRule                                                         *
*                                                                              *
* Parameters: ruleNumber                                                       *
* Return value: None                                                           *
* Description: This function will write to ruleFile what rule is currently	   *
* beingt used based on the given ruleNumber.								   *
*******************************************************************************/
void SyntacticalAnalyzer::ReportRule(int ruleNumber){
	ruleFile << "Using Rule " << ruleNumber << endl;
}
