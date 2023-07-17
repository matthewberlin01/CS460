#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "SyntacticalAnalyzer.h"

using namespace std;

SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
	lex = new LexicalAnalyzer (filename);
	token_type t;
	while ((t = lex->GetToken()) != EOF_T){
	}
    lex->ReportError(to_string(lex->GetErrors()) + " errors found in input file");
}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	delete lex;
}
