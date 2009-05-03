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
	
	if(DEBUG_TRACING) std::cout << "table->get(end, Name): " << table->get(end, name) << "\n";
	
	// Set up the static prodctions table
	grammar_productions[ Start		].push_back(   "L "				); // 1
	
	grammar_productions[ Line		].push_back(   "L D sc "		); // 2
	grammar_productions[ Line		].push_back(   "D sc "			); // 3
	grammar_productions[ Deriv		].push_back(   "n "				); // 4
	grammar_productions[ Deriv		].push_back(   "X "				); // 5
	
	grammar_productions[ NTList		].push_back(   "t a "			); // 6
	grammar_productions[ NTList		].push_back(   "nt a "			); // 7
	grammar_productions[ NTList		].push_back(   "X a "			); // 8
	
	grammar_productions[ Deriv		].push_back(   "s "				); // 9
	grammar_productions[ Deriv		].push_back(   "P "				); // 10
	
	grammar_productions[ Production	].push_back(	"P | R "		); // 11
	grammar_productions[ Production	].push_back(	"rnum a => R "	); // 12
	
	grammar_productions[ Rule		].push_back(	"R a "			); // 13
	grammar_productions[ Rule		].push_back(	"lambda "		); // 14
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
	
	while( input.good() && !semanticStack.empty() )
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
		
		// if a semicolon is included in the string we just read in, we need to
		// remove it from the string and put it back into the input buffer.
		if(tempString.length() > 1 && tempString[tempString.length() - 1] == ';')
		{
			input.unget();
			tempString[tempString.length() -1] = '\0';
		}
		
		if(DEBUG_TRACING) std::cout << "getting next token: " << tempString << "\n";
		
		// special case for name Declaration
		if(tempString == "!name:")
		{
			input >> tempString;
			input.unget();
			tempString[tempString.length() - 1] = '\0';
			currentSymbol = new Symbol( name, tempString);
			currentSymbol->token_type = name;
			currentSymbol->token_value = tempString;
			currentSymbol->type_value = vocabSymbolAsString(name);
			
			if(DEBUG_TRACING) std::cout << "found name declaration, ignoring: " << tempString << "\n";
		}
		else
		{
			currentSymbol = new Symbol();
			currentSymbol->token_type = getSymbolTypeFromInputString(tempString);
			currentSymbol->token_value = tempString;
			currentSymbol->type_value = vocabSymbolAsString((vocab_t)currentSymbol->token_type);
			
			if(DEBUG_TRACING) std::cout << "found normal statement, type: " << currentSymbol->token_type;
			if(DEBUG_TRACING) std::cout << " value: " << tempString << "\n";
		}
		
		// find relation between top and current
		Symbol *top = semanticStack.top();
		parserRelation rel = (parserRelation)table->get(top->token_type, currentSymbol->token_type);
		
		// trace out the relationship we just found
		if(DEBUG_TRACING) std::cout << "found relation between current and top (rel): " << rel << "\n";
		if(DEBUG_TRACING) std::cout << "True Relation: " << table->get(top->token_type, currentSymbol->token_type) << std::endl;
		
		// if the relationship is Equal or Less
		// shift operation
		if(rel == LEQ || rel == EQL || rel == LES)
		{
			if(DEBUG_TRACING) std::cout << "relation (rel) was less or equal shifting \n";
			
			// simply add the stuff to the stack
			Symbol* relation = new Symbol(rel, "");
			semanticStack.push(relation);
			semanticStack.push(currentSymbol);
		}
		
		// Relation is Greater
		// reduce operation
		else if(rel == GTR)
		{
			if(DEBUG_TRACING) std::cout << "relation (rel) was greater, reducing \n";
			
			vocab_t nt = searchProductionToReduce();
			
			// we've already implicitly removed the pivot
			parserRelation tempRel = (parserRelation) table->get(semanticStack.top()->token_type, nt);
			
			// do what is called for with this symbol (a nonterminal)
			semanticAction(nt);
			
			// do a shift operation by putting the new relation and symbol onto the stack
			Symbol* relSym = new Symbol(tempRel, "");
			Symbol* typeSym = new Symbol(nt, vocabSymbolAsString(nt));
			semanticStack.push(relSym);
			semanticStack.push(typeSym);
		}
		
	} // end while loop
	
	return true;
}


/*
 * SEMANTIC_ACTION
 *
 * return void
 *
 * carries out different things depending on:
 *  - the vocab type passed in
 *  - the current symbol
 *  - the popped symbol
 */
void ParserApp::semanticAction(vocab_t reductionFactor)
{
	symbolType currentDecType;
	
	if(DEBUG_TRACING) std::cout << "(*) Running semantic action for: " << reductionFactor << "\n";
	
	for(
		std::list<Symbol*>::iterator it = currentReductionList.begin();
		it != currentReductionList.end();
		it++ )
	{
		switch(reductionFactor)
		{
			case Deriv:
				if(poppedSymbols == "n ")
				{
					grammarName = (* it)->token_value;
				}
				else if(poppedSymbols == "s ")
				{
					startSymbol = (*it)->token_value;
				}
				else
				{
					break;
				}
				
			case NTList:
				if(poppedSymbols == "nt a ")
				{
					// this is a type (ParsingGrammar::symbolType)
					currentDecType = NT;
					it++;
					nonterminalSet.insert( (* it)->token_value );
				}
				else if(poppedSymbols == "t a ")
				{
					currentDecType = T;
					it++;
					terminalSet.insert( (* it)->token_value );
				}
				else if(poppedSymbols == "X a ")
				{
					it++;
					if(currentDecType == NT)
					{
						nonterminalSet.insert( (*it)->token_value );
					}
					else if(currentDecType == T)
					{
						terminalSet.insert( (* it)->token_value );
					}
					else
					{
						if(DEBUG_TRACING) std::cout << "ERROR: oiowejriojeaorijaoirj" << std::endl;
					}
				}
				else if(poppedSymbols == "a ")
				{
					if(currentDecType == NT)
					{
						nonterminalSet.insert( (*it)->token_value );
					}
					else if(currentDecType == T)
					{
						terminalSet.insert( (* it)->token_value );
					}
					else
					{
						if(DEBUG_TRACING) std::cout << "ERROR: oiowejriojeaorijaoirj" << std::endl;
					}
					
				}
				else
				{
					break;
				}
				
				// add to symbol table
				symbolTable.push_back(*it);
				
			case Production:
				if(poppedSymbols == "P | R ")
				{
				}
				else if(poppedSymbols == "rnum a  => R ")
				{
					// addProduction(currentReductionList);
				}
				else
				{
					break;
				}
				
			case Rule:
				if(poppedSymbols == "R a" || poppedSymbols == "a ")
				{
					if(poppedSymbols == "R a ")
					{
						it++;
					}
					
					for(
						std::set<std::string>::iterator ntSetIt = nonterminalSet.begin();
						ntSetIt != nonterminalSet.end();
						ntSetIt++ )
					{
						if( *ntSetIt == (* it)->token_value)
						{
							nonterminalSet.insert( (* it)->token_value );
							break;
						}
					}
					
					for(
						std::set<std::string>::iterator tSetIt = terminalSet.begin();
						tSetIt != terminalSet.end();
						tSetIt++ )
					{
						if( *tSetIt == (* it)->token_value )
						{
							terminalSet.insert( (* it)->token_value );
							break;
						}
					}
				}
				
			default:
				break;
		}
	}
}


/*
 * VOCAB_SYMBOL_AS_STRING
 *
 * return string with rule identifier
 * for the given vocabulary type
 */
std::string ParserApp::vocabSymbolAsString(vocab_t type)
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
			
		case Production:
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
	poppedSymbols = "";
	vocab_t left_part;
	
	//find pivot
	do
	{
		temp = semanticStack.top();
		semanticStack.pop();
		poppedSymbols += temp->type_value + " ";
		currentReductionList.push_back(temp);
	}
	while(
		  temp->token_type != LES &&
		  temp->token_type != LEQ &&
		  temp->token_type != end );
	
	
	if(temp->token_type == end)
	{
		if(DEBUG_TRACING) std::cout << "Error: no production found\n";

		throw new std::exception();
	}
	
	// find matching right part
	for(i = Start; i < end; i++)
	{
		for(
			std::list<std::string>::iterator it = grammar_productions[i].begin();
			it != grammar_productions[i].end();
			it++ )
		{
			if(*it == poppedSymbols)
			{
				if(DEBUG_TRACING) std::cout << "Found matching right part for " << (* it) << ": " << i << std::endl;
				left_part = (vocab_t) i;
				break;
			}
		}
	}
	
	return (vocab_t) i;
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
