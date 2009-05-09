/*
 *  ParsingGrammar.cpp
 *  parser
 *
 * Grammar G
 * 
 */

#include "ParsingGrammar.h"

ParsingGrammar::ParsingGrammar()
{
	// manually enter all productions as strings
	constructProductions();
	
	// make a data table large enough to hold all symbols up to end
	precedenceMatrix = new DataTable(end, end);
	computePrecedenceMatrix();
}


/*
 * CONSTRUCT_PRODUCTIONS
 *
 * return void
 * fill up the production list with lists of strings
 */
void ParsingGrammar::constructProductions()
{
	// Set up the static prodctions table
	/*
*/

// attempting to order by length of right aprt
	productions[0] = new Production(Prod		, "rnum a => R"	); // 12
	productions[1] = new Production(Prod		, "P | R"		); // 11
	productions[2] = new Production(Line		, "L D sc"		); // 2
	productions[3] = new Production(Rule		, "R a"			); // 13
	productions[4] = new Production(Line		, "D sc"		); // 3
	productions[5] = new Production(NTList		, "X a"			); // 8
	productions[6] = new Production(NTList		, "t a"			); // 6
	productions[7] = new Production(NTList		, "nt a"		); // 7
	productions[8] = new Production(Deriv		, "X"			); // 5
	productions[9] = new Production(Start		, "L"			); // 1
	productions[10] = new Production(Deriv		, "n"			); // 4
	productions[11] = new Production(Deriv		, "s"			); // 9
	productions[12] = new Production(Deriv		, "P"			); // 10
	productions[13] = new Production(Rule		, "lambda"		); // 14
}


/*
 * VOCAB_SYMBOL_AS_STRING
 *
 * return string with rule identifier
 * for the given vocabulary type
 */
std::string ParsingGrammar::vocabSymbolAsString(vocab_t type)
{
	std::string r;
	switch (type)
	{
		case Start:
			r = "S";
			break;
			
		case Line:
			r = "L";
			break;
			
		case Deriv:
			r = "D";
			break;
			
		case NTList:
			r = "X";
			break;
			
		case Prod:
			r = "P";
			break;
			
		case Rule:
			r = "R";
			break;
			
		case name:
			r = "n";
			break;
			
		case terminal:
			r = "t";
			break;
			
		case nonterminal:
			r = "nt";
			break;
			
		case vocabsymbol:
			r = "a";
			break;
			
		case semicolon:
			r = "sc";
			break;
			
		case choice:
			r = "|";
			break;
			
		case becomes:
			r = "=>";
			break;
			
		case rulenumber:
			r = "rnum";
			break;
			
		case startdec:
			r = "s";
			break;
			
		case lambda:
			r = "lambda";
			break;
			
		case end:
			r = "$";
			break;
			
		default:
			break;
	}
	return r;
}


/*
 * GET_SYMBOL_TYPE_FROM_INPUT_STRING
 *
 * return ParsingGrammar::vocab_t
 *
 * returns a vocab_t (ParserGrammar vocab type)
 * representing the type of the string supplied
 * via the type rules for the parsing grammar G
 */
vocab_t ParsingGrammar::getSymbolTypeFromInputString(std::string str)
{
	// make string into character array
	const char * symbolName = str.c_str();
	
	// return type, if not overwritten, wil be error
	vocab_t type = error;
	
	// State 1: A declaration
	if(symbolName[0] == '!')
	{
		// copy the symbol name declaration into temp with out the '!'
		char temp[ 50 ];//(int) str.length() - 1 ];
		strcpy(temp, &symbolName[1]);
		
		if( strcmp("name:", temp) == 0)
		{
			type = name;
		}
		else if( strcmp("non-terminals:", temp) == 0 )
		{
			type = nonterminal;
		}
		else if( strcmp("terminals:", temp) == 0 )
		{
			type = terminal;
		}
		else if( strcmp("start:", temp) == 0 )
		{
			type = startdec;
		}
	}
	
	// State 2: a number
	else if( isdigit(symbolName[0]) )
	{
		if(symbolName[1] == ':')
		{
			type = rulenumber;
		}
	}
	
	// State 3: a symbol or lambda
	else if( isalpha(symbolName[0]) )
	{
		if( strcmp("lambda", symbolName) == 0 )
		{
			type = lambda;
		}
		else
		{
			// Assume that any other input that
			// is alphanumeric is a vocab symbol
			type = vocabsymbol;
		}
	}
	
	// Other states, misc symbols
	else if( str == "=>" )
	{
		type = becomes;
	}
	
	else if( str == ";" )
	{
		type = semicolon;
	}
	
	else if( str == "|" )
	{
		type = choice;
	}
	
	return type;
}



/*
 * COMPUTE_PRECEDENCE_MATRIX
 *
 * fill PrecedenceMatrix <pointer>
 * with all relations already set
 *
 */
void ParsingGrammar::computePrecedenceMatrix()
{
	// S Production
	setRel(Start, Start,              0	);
	setRel(Start, Line,               0	);
	setRel(Start, Deriv,              0	);
	setRel(Start, NTList,             0	);
	setRel(Start, Prod,               0	);
	setRel(Start, Rule,               0	);
	setRel(Start, name,               0	);
	setRel(Start, terminal,           0	);
	setRel(Start, nonterminal,        0	);
	setRel(Start, vocabsymbol,        0	);
	setRel(Start, semicolon,          0	);
	setRel(Start, choice,             0	);
	setRel(Start, becomes,            0	);
	setRel(Start, rulenumber,         0	);
	setRel(Start, startdec,           0	);
	setRel(Start, lambda,             0	);
	setRel(Start, end,                0	);
	
	// L Prod,      
	setRel(Line, Start,               0	);
	setRel(Line, Line,                0	);
	setRel(Line, Deriv,               EQL	);
	setRel(Line, NTList,              LES	);
	setRel(Line, Prod,                LES	);
	setRel(Line, Rule,                0	);
	setRel(Line, name,                LES	);                                 
	setRel(Line, terminal,            LES	);                                 
	setRel(Line, nonterminal,         LES	);                                 
	setRel(Line, vocabsymbol,         0	);
	setRel(Line, semicolon,           0	);
	setRel(Line, choice,              0	);
	setRel(Line, becomes,             0	);
	setRel(Line, rulenumber,          LES	);                                 
	setRel(Line, startdec,            LES	);                                 
	setRel(Line, lambda,              0	);
	setRel(Line, end,                 GTR	);                                 
	
	// D Prod,      
	setRel(Deriv, Start,              0	);
	setRel(Deriv, Line,               0	);
	setRel(Deriv, Deriv,              0	);
	setRel(Deriv, NTList,             0	);
	setRel(Deriv, Prod,               0	);
	setRel(Deriv, Rule,               0	);
	setRel(Deriv, name,               0	);
	setRel(Deriv, terminal,           0	);
	setRel(Deriv, nonterminal,        0	);
	setRel(Deriv, vocabsymbol,        0	);
	setRel(Deriv, semicolon,          EQL	);                                 
	setRel(Deriv, choice,             0	);
	setRel(Deriv, becomes,            0	);
	setRel(Deriv, rulenumber,         0	);
	setRel(Deriv, startdec,           0	);
	setRel(Deriv, lambda,             0	);
	setRel(Deriv, end,                0	);
	
	// X Prod,       (allows a list of symbols t or nt)
	setRel(NTList, Start,             0	);
	setRel(NTList, Line,              0	);
	setRel(NTList, Deriv,             0	);
	setRel(NTList, NTList,            0	);
	setRel(NTList, Prod,              0	);
	setRel(NTList, Rule,              0	);
	setRel(NTList, name,              0	);
	setRel(NTList, terminal,          0	);
	setRel(NTList, nonterminal,       0	);
	setRel(NTList, vocabsymbol,       EQL	);                                 
	setRel(NTList, semicolon,         GTR	);                                 
	setRel(NTList, choice,            0	);
	setRel(NTList, becomes,           0	);
	setRel(NTList, rulenumber,        0	);
	setRel(NTList, startdec,          0	);
	setRel(NTList, lambda,            0	);
	setRel(NTList, end,               0	);
	
	// P Produciton
	setRel(Prod,       Start,         0	);
	setRel(Prod,       Line,          0	);
	setRel(Prod,       Deriv,         0	);
	setRel(Prod,       NTList,        0	);
	setRel(Prod,       Prod,          0	);
	setRel(Prod,       Rule,          0	);
	setRel(Prod,       name,          0	);
	setRel(Prod,       terminal,      0	);
	setRel(Prod,       nonterminal,   0	);
	setRel(Prod,       vocabsymbol,   0	);
	setRel(Prod,       semicolon,     GTR	);                                 
	setRel(Prod,       choice,        EQL	);
	setRel(Prod,       becomes,       0	);
	setRel(Prod,       rulenumber,    0	);
	setRel(Prod,       startdec,      0	);
	setRel(Prod,       lambda,        0	);
	setRel(Prod,       end,           0	);
	
	// R Prod,      
	setRel(Rule, Start,               0	);
	setRel(Rule, Line,                0	);
	setRel(Rule, Deriv,               0	);
	setRel(Rule, NTList,              0	);
	setRel(Rule, Prod,                0	);
	setRel(Rule, Rule,                0	);
	setRel(Rule, name,                0	);
	setRel(Rule, terminal,            0	);
	setRel(Rule, nonterminal,         0	);
	setRel(Rule, vocabsymbol,         EQL	);                                 
	setRel(Rule, semicolon,           GTR	);                                 
	setRel(Rule, choice,              GTR	);                                 
	setRel(Rule, becomes,             0	);
	setRel(Rule, rulenumber,          0	);
	setRel(Rule, startdec,            0	);
	setRel(Rule, lambda,              0	);
	setRel(Rule, end,                 0	);
	
	// n terminal
	setRel(name, Start,               0	);
	setRel(name, Line,                0	);
	setRel(name, Deriv,               0	);
	setRel(name, NTList,              0	);
	setRel(name, Prod,                0	);
	setRel(name, Rule,                0	);
	setRel(name, name,                0	);
	setRel(name, terminal,            0	);
	setRel(name, nonterminal,         0	);
	setRel(name, vocabsymbol,         0	);
	setRel(name, semicolon,           GTR	);
	setRel(name, choice,              0	);
	setRel(name, becomes,             0	);
	setRel(name, rulenumber,          0	);
	setRel(name, startdec,            0	);
	setRel(name, lambda,              0	);
	setRel(name, end,                 0	);
	
	// t terminal (terminal listing declaration)
	setRel(terminal, Start,           0	);
	setRel(terminal, Line,            0	);
	setRel(terminal, Deriv,           0	);
	setRel(terminal, NTList,          0	);
	setRel(terminal, Prod,            0	);
	setRel(terminal, Rule,            0	);
	setRel(terminal, name,            0	);
	setRel(terminal, terminal,        0	);
	setRel(terminal, nonterminal,     0	);
	setRel(terminal, vocabsymbol,     EQL	);                                 
	setRel(terminal, semicolon,       0	);
	setRel(terminal, choice,          0	);
	setRel(terminal, becomes,         0	);
	setRel(terminal, rulenumber,      0	);
	setRel(terminal, startdec,        0	);
	setRel(terminal, lambda,          0	);
	setRel(terminal, end,             0	);
	
	// nt terminal (nonterminal listing declaration)
	setRel(nonterminal, Start,        0	);
	setRel(nonterminal, Line,         0	);
	setRel(nonterminal, Deriv,        0	);
	setRel(nonterminal, NTList,       0	);
	setRel(nonterminal, Prod,         0	);
	setRel(nonterminal, Rule,         0	);
	setRel(nonterminal, name,         0	);
	setRel(nonterminal, terminal,     0	);
	setRel(nonterminal, nonterminal,  0	);
	setRel(nonterminal, vocabsymbol,  EQL	);                                 
	setRel(nonterminal, semicolon,    0	);
	setRel(nonterminal, choice,       0	);
	setRel(nonterminal, becomes,      0	);
	setRel(nonterminal, rulenumber,   0	);
	setRel(nonterminal, startdec,     0	);
	setRel(nonterminal, lambda,       0	);
	setRel(nonterminal, end,          0	);
	
	// a terminal (any symbol in the input alphabet)
	setRel(vocabsymbol, Start,        0	);
	setRel(vocabsymbol, Line,         0	);
	setRel(vocabsymbol, Deriv,        0	);
	setRel(vocabsymbol, NTList,       0	);
	setRel(vocabsymbol, Prod,         0	);
	setRel(vocabsymbol, Rule,         0	);
	setRel(vocabsymbol, name,         0	);
	setRel(vocabsymbol, terminal,     0	);
	setRel(vocabsymbol, nonterminal,  0	);
	setRel(vocabsymbol, vocabsymbol,  GTR	);                                 
	setRel(vocabsymbol, semicolon,    GTR	);                                 
	setRel(vocabsymbol, choice,       GTR	);                                 
	setRel(vocabsymbol, becomes,      EQL	);                                 
	setRel(vocabsymbol, rulenumber,   0	);
	setRel(vocabsymbol, startdec,     0	);
	setRel(vocabsymbol, lambda,       GTR	);                                 
	setRel(vocabsymbol, end,          0	);
	
	setRel(semicolon, Start,          0	);
	setRel(semicolon, Line,           0	);
	setRel(semicolon, Deriv,          0	);
	setRel(semicolon, NTList,         0	);
	setRel(semicolon, Prod,           0	);
	setRel(semicolon, Rule,           0	);
	setRel(semicolon, name,           GTR	);                                 
	setRel(semicolon, terminal,       GTR	);                                 
	setRel(semicolon, nonterminal,    GTR	);                                 
	setRel(semicolon, vocabsymbol,    0	);
	setRel(semicolon, semicolon,      0	);
	setRel(semicolon, choice,         0	);
	setRel(semicolon, becomes,        0	);
	setRel(semicolon, rulenumber,     GTR	);                                 
	setRel(semicolon, startdec,       GTR	);                                 
	setRel(semicolon, lambda,         0	);
	setRel(semicolon, end,            GTR	);
	
	// or terminal
	setRel(choice, Start,             0	);
	setRel(choice, Line,              0	);
	setRel(choice, Deriv,             0	);
	setRel(choice, NTList,            0	);
	setRel(choice, Prod,              0	);
	setRel(choice, Rule,              LEQ	);                                 
	setRel(choice, name,              0	);
	setRel(choice, terminal,          0	);
	setRel(choice, nonterminal,       0	);
	setRel(choice, vocabsymbol,       0	);
	setRel(choice, semicolon,         0	);
	setRel(choice, choice,            0	);
	setRel(choice, becomes,           0	);
	setRel(choice, rulenumber,        0	);
	setRel(choice, startdec,          0	);
	setRel(choice, lambda,            LES	);                                 
	setRel(choice, end,               0	);
	
	setRel(becomes, Start,            0	);
	setRel(becomes, Line,             0	);
	setRel(becomes, Deriv,            0	);
	setRel(becomes, NTList,           0	);
	setRel(becomes, Prod,             0	);
	setRel(becomes, Rule,             LEQ	);                                 
	setRel(becomes, name,             0	);
	setRel(becomes, terminal,         0	);
	setRel(becomes, nonterminal,      0	);
	setRel(becomes, vocabsymbol,      0	);
	setRel(becomes, semicolon,        0	);
	setRel(becomes, choice,           0	);
	setRel(becomes, becomes,          0	);
	setRel(becomes, rulenumber,       0	);
	setRel(becomes, startdec,         0	);
	setRel(becomes, lambda,           LES	);                                 
	setRel(becomes, end,              0	);
	
	setRel(rulenumber, Start,         0	);
	setRel(rulenumber, Line,          0	);
	setRel(rulenumber, Deriv,         0	);
	setRel(rulenumber, NTList,        0	);
	setRel(rulenumber, Prod,          0	);
	setRel(rulenumber, Rule,          0	);
	setRel(rulenumber, name,          0	);
	setRel(rulenumber, terminal,      0	);
	setRel(rulenumber, nonterminal,   0	);
	setRel(rulenumber, vocabsymbol,   EQL	);                                 
	setRel(rulenumber, semicolon,     0	);
	setRel(rulenumber, choice,        0	);
	setRel(rulenumber, becomes,       0	);
	setRel(rulenumber, rulenumber,    0	);
	setRel(rulenumber, startdec,      0	);
	setRel(rulenumber, lambda,        0	);
	setRel(rulenumber, end,           0	);
	
	// s terminal the start symbol declaration
	// from the nonterminal alphabet
	setRel(startdec, Start,           0	);
	setRel(startdec, Line,            0	);
	setRel(startdec, Deriv,           0	);
	setRel(startdec, NTList,          0	);
	setRel(startdec, Prod,            0	);
	setRel(startdec, Rule,            0	);
	setRel(startdec, name,            0	);
	setRel(startdec, terminal,        0	);
	setRel(startdec, nonterminal,     0	);
	setRel(startdec, vocabsymbol,     0	);
	setRel(startdec, semicolon,       GTR	);                                 
	setRel(startdec, choice,          0	);
	setRel(startdec, becomes,         0	);
	setRel(startdec, rulenumber,      0	);
	setRel(startdec, startdec,        0	);
	setRel(startdec, lambda,          0	);
	setRel(startdec, end,             0	);
	
	setRel(lambda, Start,             0	);
	setRel(lambda, Line,              0	);
	setRel(lambda, Deriv,             0	);
	setRel(lambda, NTList,            0	);
	setRel(lambda, Prod,              0	);
	setRel(lambda, Rule,              0	);
	setRel(lambda, name,              0	);
	setRel(lambda, terminal,          0	);
	setRel(lambda, nonterminal,       0	);
	setRel(lambda, vocabsymbol,       GTR	);
	setRel(lambda, semicolon,         GTR	);                                 
	setRel(lambda, choice,            GTR	);                                 
	setRel(lambda, becomes,           0	);
	setRel(lambda, rulenumber,        0	);
	setRel(lambda, startdec,          0	);
	setRel(lambda, lambda,            0	);
	setRel(lambda, end,               0	);
	
	setRel(end, Start,                0	);
	setRel(end, Line,                 LES	);                                 
	setRel(end, Deriv,                LES	);                                 
	setRel(end, NTList,               LES	);                                 
	setRel(end, Prod,                 LES	);                                 
	setRel(end, Rule,                 0	);
	setRel(end, name,                 LES	);                                 
	setRel(end, terminal,             LES	);                                 
	setRel(end, nonterminal,          LES	);                                 
	setRel(end, vocabsymbol,          0	);
	setRel(end, semicolon,            0	);
	setRel(end, choice,               0	);
	setRel(end, becomes,              0	);
	setRel(end, rulenumber,           LES	);
	setRel(end, startdec,             LES	);
	setRel(end, lambda,               0	);
	setRel(end, end,                  0	);
}
