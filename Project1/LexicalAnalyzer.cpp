#include <iomanip>
#include <cstdlib>
#include "LexicalAnalyzer.h"

using namespace std;

//enum token_type {NONE = 1};
static string tokennames[] = {"NONE"}; 

LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
	// This function will initialize the lexical analyzer class
	input.open(filename);
    std::string theFile = filename;
    theFile = theFile.substr(0, theFile.length() - 3) + ".lst";
    listingFile.open(theFile);
    theFile = theFile.substr(0, theFile.length() - 4) + ".p1";
    tokenFile.open(theFile);
    theFile = theFile.substr(0, theFile.length() - 3) + ".dbg";
    debugFile.open(theFile);

	string fileName = string(filename);
	messageText = "Input File: " + fileName;
    WriteListingFile(messageText);

	linenum = 0;
	pos = 0;
	errors = 0;


    if(input.is_open()){
        WriteDebugFile("file opened");
    }
    else{
        WriteDebugFile("file didn't open properly");
    }
}

LexicalAnalyzer::~LexicalAnalyzer ()
{
	// This function will complete the execution of the lexical analyzer class
    input.close();
}

token_type LexicalAnalyzer::GetToken ()
{
    //Get rid of any leading whitespaces
    while(line[pos] == ' '){
        pos++;
    }

	// This function will find the next lexeme int the input file and return
	// the token_type value associated with that lexeme
	if(line[pos] == '\0'){
		getline(input, line);
		pos = 0;
		linenum++;
		//If we encounter another end oof line after getting the next line, we
		//have an end of file character and must return end of file.
		if(input.eof()){
			token = EOF_T;
			messageText = to_string(linenum) + " : " + line;
			WriteListingFile(messageText);
			messageText = GetTokenName(token) + "\t";
            WriteTokenFile(messageText);
            lexeme = "";
			return token;	//position of the end of file token
		}
	}
	else{
		//Since we are not at the end of the line, we will move through input until
		//currentState reaches a terminating state from the tokenFlowState, set token
		//equal to that terminating token, and write to the tokenFile what that
		//token type is as well as its associated lexeme.
		int currentState = 0;
		int column;
		while(currentState >= 0){
			column = ColumnPosition(line[pos]);
            if(!(currentState == 0 && column == 0)){
                lexeme += line[pos];
            }
			if(column == -1 || tokenFlowState.at(currentState).at(column) == -ERROR_T){
				errors++;
                //If we are currently reading in an error and we have multiple characters in our
                //lexeme, put the current character back on the input as it could potentially be
                //a part of another lexeme, otherwise move to the next position as we have read in
                //a single character and doesn't affect any future lexemes.
                if(lexeme.length() > 1){
                    lexeme.pop_back();
                }
                else{
                    pos++;
                }
                token = ERROR_T;
				messageText = "Error at " + to_string(linenum) + "," + to_string(pos) + ": Invalid character found: " + lexeme;
				ReportError(messageText);
				messageText = GetTokenName(token) + "\t" + GetLexeme();
				WriteTokenFile(messageText);
                lexeme = "";
				return token;
			}
			else{
				currentState = tokenFlowState.at(currentState).at(column);
			}
			pos++;
		}
        //Set the current state back to a positive value to compare it with the proper token_type
		currentState *= -1;
		if(currentState == IDENT_T){
            //If the currentState is IDENT_T, check to see if the lexeme is actually a keyword.
			if(keywordMap.find(lexeme) != keywordMap.end()){
				currentState = keywordMap.find(lexeme)->second;
			}
            else{
                //If the lexeme is not a keyword, check to see if we got one more character than we needed,
                //such as a space.
                if(keywordMap.find(lexeme.substr(0, lexeme.length() - 1)) != keywordMap.end()){
                    currentState = keywordMap.find(lexeme.substr(0, lexeme.length() - 1))->second;
                }
                //We need to decrement pos to read in the current character on the next GetToken call
                //and remove the last character from the lexeme since it belongs to the next token.
                pos--;
                lexeme.pop_back();
            }
		}
        //If we have a terminal state that requires that the character be put back on the line,
        //between the positions of NONE and ROUND_T inclusive, then we decrement pos so that the
        //next character can be read on the next GetToken call and remove the last character from
        //the lexeme since it belongs to the next token.
        else if(currentState <= ROUND_T){
            pos--;
            lexeme.pop_back();
        }

		//return the token_type value at currentState;
		token = tokenState.at(currentState - 1);
		messageText = GetTokenName(token) + "\t" + GetLexeme();
		WriteTokenFile(messageText);
        lexeme = "";
		return token;
	}
	//Since we reached the end of the line and are now at a new line, we must
	//write to the listFile what line we are on as well as what is in that line.
	messageText = to_string(linenum) + " : " + line;
	WriteListingFile(messageText);
    lexeme = "";
	return token;
}

string LexicalAnalyzer::GetTokenName (token_type t) const
{
	// This function returns a string containing the name of the token
	// passed to it.
	return tokenNames.at(token - 1);
}

string LexicalAnalyzer::GetLexeme () const
{
	// This function will return the lexeme found by the most recent call to 
	// the GetToken function
	return lexeme;
}

int LexicalAnalyzer::GetErrors(){
    return errors;
}


void LexicalAnalyzer::ReportError (const string & msg)
{
	// This function will be called to write an error message to a file
	listingFile << msg << endl;
}

void LexicalAnalyzer::WriteListingFile(const string & msg){
	// This function will be called to write a message to the listingFile
	listingFile << msg << endl;
}

void LexicalAnalyzer::WriteTokenFile(const string & msg){
	// This function will be called to write a message to the tokenFile
	tokenFile << msg << endl;
}

void LexicalAnalyzer::WriteDebugFile(const string & msg){
	debugFile << msg << endl;
}

int LexicalAnalyzer::ColumnPosition(char theCharacter){
	// This function takes an input character and returns the corresponding
	// column position for the input character.
	if(isspace(theCharacter)){
		return 0;
	}
	else if(isalpha(theCharacter)){
		switch(theCharacter){
			case 'c':
				return 2;
			case 'a':
				return 3;
			case 'd':
				return 4;
			case 'r':
				return 5;
            default:
			    return 1;
		}
	}
	else if(isdigit(theCharacter)){
		return 7;
	}
	else{
		switch(theCharacter){
			case '?':
				return 6;
			case '+':
				return 8;
			case '-':
				return 9;
			case '/':
				return 10;
			case '*':
				return 11;
			case '.':
				return 12;
			case '=':
				return 13;
			case '>':
				return 14;
			case '<':
				return 15;
			case '(':
				return 16;
			case ')':
				return 17;
			case '\'':
				return 18;
			case '"':
				return 19;
            case '_':
                return 20;
            case '\0':
                return 21;
		}
        if(theCharacter < 0){
            return 21;
        }
        else{
            return -1;
        }
	}
}
