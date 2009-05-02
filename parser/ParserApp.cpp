/*
 *  ParserApp.cpp
 *  parser
 *
 *  Daniel Walker
 *  Austin Montoya
 *
 */

#include "ParserApp.h"
#define DEBUG_TRACING true

/*
 * Symbol Class Intake Constructor
 *
 * takes in type, value
 */
ParserApp::Symbol::Symbol(int tt, std::string tv) :
	token_type(tt),
	token_value(tv) {}


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
	Symbol* endsym = new Symbol( ParsingGrammar::end, std::string("$") );
	semanticStack.push(endsym);        
	
	// start the current symbol as the initial endsym ($)
	currentSymbol = endsym;

	//Set up the static prodctions table
	productions[Start].push_back("L "); //1
	
	productions[Line].push_back("L D sc ");//2
	productions[Line].push_back("D sc ");//2
	productions[Deriv].push_back("n ");//3
	productions[Deriv].push_back("X ");//4
	
	productions[NTList].push_back("t a ");//5
	productions[NTList].push_back("nt a ");//6
	productions[NTList].push_back("X a ");//7
	
	productions[Deriv].push_back("s ");//8
	productions[Deriv].push_back("P ");//9

	productions[Production].push_back("P | R ");//10
	productions[Production].push_back("rnum a => R ");
	
	productions[Rule].push_back("R a ");
    productions[Rule].push_back("lambda ");
	
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
	
	// return type, if not overwritten, wil be error
	ParsingGrammar::vocab_t type = error;
	
	// State 1: A declaration
	if(symbolName[0] == '!')
	{
		// copy the symbol name declaration into temp with out the '!'
		char temp[ (int) str.length() - 1 ];
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
	else if( isnumber(symbolName[0]) )
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
		// look ahead one character to see if it's a comment
		tk = (char) input.get();
		
		// State 1: token is a comment
		if(tk == '#')
		{
			// ignore entire line
			getline(input, tempString);
			
			if(DEBUG_TRACING) std::cout << "found comment: " << tempString << "\n";
			continue;
		}
		
		// if we get to here, we did not 'continue'
		// so it must not have been a comment marker '#'
		// so put the char back
		input.unget();
		
		// Token is not a comment (we know because we looked ahead)
		// perform stack actions (shifting and reducing)
		input >> tempString;
		
		//if a semicolon is included in the string we just read in, we need to
		//remove it from the string and put it back into the input buffer.
		if(tempString.length() > 1 && tempString[tempString.length() - 1] == ';')
		{
			input.unget();
			tempString[tempString.length() -1] = NULL;
		}
		
		if(DEBUG_TRACING) std::cout << "getting next token: " << tempString << "\n";
		
		// special case for name Declaration
		if(tempString == "!name:")
		{
			input >> tempString;
			currentSymbol = new Symbol( name, tempString);
			currentSymbol->token_type = name;
			currentSymbol->token_value = tempString;
			currentSymbol->type_value = vocabSymbolAsString(name);
			
			if(DEBUG_TRACING) std::cout << "found name declaration, ignoring: " << tempString << "\n";
			
			// need to put currentSymbol into symbol table or something..
			
		}
		else
		{
			currentSymbol = new Symbol();
			currentSymbol->token_type = getSymbolTypeFromInputString(tempString);
			currentSymbol->token_value = tempString;
			currentSymbol->type_value = "n";

			if(DEBUG_TRACING) std::cout << "found normal statement, type: " << currentSymbol->token_type;
			if(DEBUG_TRACING) std::cout << " value: " << tempString << "\n";
		}
		
		parserRelation rel = (parserRelation) table->get(semanticStack.top()->token_type, currentSymbol->token_type);
		if(DEBUG_TRACING) std::cout << "found relation between current and top (rel): " << rel << "\n";
		
		// if the relationship is Equal or Less
		// shift operation
		if(rel == LEQ || rel == EQL || rel == LES)
		{
			if(DEBUG_TRACING) std::cout << "relation (rel) was less or equal shifting \n";
			Symbol* relation = new Symbol(rel, "");
			
			semanticStack.push(relation);
			semanticStack.push(currentSymbol);
		}
		
		// Relation is Greater
		// reduce operation
		else if(rel == GTR)
		{
			if(DEBUG_TRACING) std::cout << "relation (rel) was greater, reducing \n";
			// basic idea:
			 vocab_t nt = searchProductionToReduce();
			//we've already implicitly removed the pivot
			 parserRelation tempRel = (parserRelation) table->get(semanticStack.top()->token_type, nt);
			 Symbol* relSym = new Symbol(tempRel, "");
			
			 //semanticAction(nt);
			semanticStack.push(relSym);
			
			Symbol* tSym = new Symbol(nt, vocabSymbolAsString(nt));
			 semanticStack.push(tSym);
		}
		
	} // end while loop
	
	return true;
}

std::string vocabSymbolAsString(vocab_t type)
{
	switch (type) {
			
		case Start::
			return "S";
			break;
			
		case Line:
			return "L";
			break;
			
		case Deriv:
			return "D";
			break;
			
		case NTList:
			return "X";
			break;
			
		case Production:
			return "P";
			break;
			
		case Rule:
			return "R";
			break;
			
		case name:
			return "n";
			break;
			
		case terminal:
			return "t";
			break;
			
		case nonterminal:
			return "nt";
			break;
			
		case vocabsymbol:
			return "a";
			break;
			
		case semicolon:
			return "sc";
			break;
			
		case choice:
			return "|";
			break;
			
		case becomes:
			return "=>";
			break;
			
		case rulenumber:
			return "rnum";
			break;
			
		case startdec:
			return "s";
			break;
			
		case lambda:
			return "lambda";
			break;
			
		case end:
			return "$";
			break;
			
		default:
			break;
	}
}
/*
 * SEARCH_PRODUCTION_TO_REDUCE
 *
 * return Symbol <pointer>
 *
 * Search the pivot in the stack the nearest < from the top
 * search in the productions of the grammar which one
 * have the same right side as the Pivot
 */
vocab_t ParserApp::searchProductionToReduce()
{
	int i = 0;
	Symbol* temp;
	std::string poppedSymbols;
	vocab_t left_part;
	
	//find pivot
	do
	{
		temp = semanticStack.top();
		semanticStack.pop();
		poppedSymbols += temp->type_value + " ";
	}
	while(
		  temp->token_type != LES &&
		  temp->token_type != LEQ &&
		  temp->token_type != end );
	
	
	if(temp->token_type == end)
	{
		if(DEBUG_TRACING)
		{
			std::cout << "Error: no production found\n";
		}
		throw new std::exception();
	}
	
	// find matching right part
	for(i = Start; i < end; i++)
	{
		std::list::iterator<std::string> it = productions[i].begin();
		for(it; it != productions[i].end(); it++)
		{
			if(*it == poppedSymbols)
			{
				if(DEBUG_TRACING) { std::cout << "Found matching right part for " << *it << ": " << i << std::endl; }  
				left_part = i;
				break;
			}
		}
	}
	
	return i;
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