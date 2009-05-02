/*
 *  ParserApp.cpp
 *  parser
 *
 *  Daniel Walker
 *  Austin Montoya
 *
 */

#include "ParserApp.h"


/*
 * PARSER_APP CONSTRUCTOR
 *
 * return ParserApp <pointer>
 *
 * sets up periphrials ie. input file etc.
 * constructs the precedence table for G
 * inits the semantic stack
 */
ParserApp::ParserApp( const char * filename )
{
	// this is an extension of DataTable
	// containing the relations for the parsing grammar G
	table = new PrecedenceTable();
	
	// open file with name given for reading
	input.open(filename, std::ifstream::in);
	
	// Push the intial endsym ($) into stack
	Symbol* endsym = new Symbol();
	endsym->token_type = ParsingGrammar::end;
	endsym->token_value = std::string("$");
	semanticStack.push(endsym);        
	
	// start the current symbol as the initial endsym ($)
	currentSymbol = endsym;                  
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
ParsingGrammar::vocab_t ParserApp::getSymbolTypeFromInputString(std::string str)
{
	// make string into character array
	const char * symbolName = str.c_str();
	char temp[ (int) str.length() ];
	
	// State 1: A declaration
	if(symbolName[0] == '!')
	{ 
		int i = 1;
		while(symbolName[i] != ':' || symbolName[i] != 0)
		{
			temp[i] = symbolName[i];
			i++;
		}
		
		if(!strcmp("name:", temp))
		{
			return name;
		}
		else if(!strcmp("non-terminals:", temp))
		{
			return nonterminal;
		}
		else if(!strcmp("terminals:", temp))
		{
			return terminal;
		}
		else if(!strcmp("start:", temp))
		{
			return startdec;
		}
		else
		{
			return error;
		}
	}
	
	// State 2: a number
	else if(isnumber(symbolName[0]))
	{
		if(symbolName[1] == ':')
		{
			return rulenumber;
		}
		else return error;
	}
	
	// State 3: a symbol or lambda
	else if(isalpha(symbolName[0]))
	{
		if(!strcmp("lambda;", symbolName))
		{
			return lambda;
		}
		else
		{
			// Assume that any other input that
			// is alphanumeric is a vocab symbol
			return vocabsymbol;
		}
	}
	
	// Other states, misc symbols
	else if(!strcmp("=>", temp))
	{
		return becomes;
	}
	
	else if(!strcmp(";", temp))
	{
		return semicolon;
	}
	
	else if(!strcmp("|", temp))
	{
		return choice;
	}
	
	// Error State, char was invalid
	else 
	{
		return error;
	}
}


/*
 * LEXER
 *
 * return bool
 *
 * this function runs the actions on the semantic stack
 * according to the shift/reduce algorithm
 * found @ http://en.wikipedia.org/wiki/Simple_precedence_parser
 * returns true if there were no errors
 */
bool ParserApp::lexer()
{
	char tk;
	std::string tempString;
	
	while( input.good() )
	{
		tk = (char) input.get();
		
		// State 1: token is a comment
		if(tk == '#')
		{
			// ignore entire line
			getline(input, tempString);
			continue;
		}
		
		// Token is not a comment
		// perform stack actions (shifting and reducing)
		else 
		{
			// special case for name Declaration
			input >> tempString;
			if(tempString == "!name:")
			{
				currentSymbol = new Symbol();
				currentSymbol->token_type = name;
				input >> tempString;
				currentSymbol->token_value = tempString;
			}
			else
			{
				currentSymbol = new Symbol();
				currentSymbol->token_type = getSymbolTypeFromInputString(tempString);
				currentSymbol->token_value = tempString;
			}
			
			parserRelation rel = (parserRelation) table->get(semanticStack.top()->token_type, currentSymbol->token_type);
			
			// if the relationship is Equal or Less
			// shift operation
			if(rel == LEQ || rel == EQL || rel == LES)
			{
				Symbol* relation = new Symbol();
				relation->token_type = rel;
				relation->token_value = "";
				
				semanticStack.push(relation);
				semanticStack.push(currentSymbol);
			}
			
			// Relation is Greater
			// reduce operation
			else if(rel == GTR)
			{
				// basic idea:
				// Symbol * production = searchProductionToReduce();
				// removePivot();
				// parserRelation tempRel = (parserRelation) table->get(semanticStack.top()->token_type, production->token_type);
				// stack.push(tempRel);
				// stack.push(production);
			}
			
			// always perform a reduction operation
			// Symbol * productionToReduce = searchProductionToReduce();
			// Pivot = next LES relation from top of stack
			// find the production which has the same right side as the Pivot
		}
	} // end while loop
	
	return true;
}


/*
 * MAIN
 *
 * return int
 *
 * starts the parser app
 * specifies input file
 * runs lexer
 *
 */
int main()
{
	ParserApp * App = new ParserApp("../../input.g");

	// scan the input file
	// perform parsing actions on the semantic stack
	if(App->lexer())
	{
		// parsing was successful
		// we can utilize the constructed data structures
	}
	else
	{
		// inform user of errors
	}
	
	return 0;
}