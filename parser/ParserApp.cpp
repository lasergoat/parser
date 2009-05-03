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
	G = new ParsingGrammar();
	G_prime = new InputGrammar();
	
	// open file with name given for reading
	input.open(filename, std::ifstream::in);
	
	// Push the intial endsym ($) into stack
	Symbol* endsym = new Symbol( end, std::string("$") );
	semanticStack.push(endsym);        
	
	// start the current symbol as the initial endsym ($)
	currentSymbol = endsym;
	
	if(DEBUG_TRACING) std::cout << "G->getRel(end, Name): " << G->getRel(end, name) << "\n";
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
			currentSymbol->type_value = G->vocabSymbolAsString(name);
			
			if(DEBUG_TRACING) std::cout << "found name declaration, ignoring: " << tempString << "\n";
		}
		else
		{
			currentSymbol = new Symbol();
			currentSymbol->token_type = G->getSymbolTypeFromInputString(tempString);
			currentSymbol->token_value = tempString;
			currentSymbol->type_value = G->vocabSymbolAsString((vocab_t)currentSymbol->token_type);
			
			if(DEBUG_TRACING) std::cout << "found normal statement, type: " << currentSymbol->token_type;
			if(DEBUG_TRACING) std::cout << " value: " << tempString << "\n";
		}
		
		// find relation between top and current
		Symbol * top = semanticStack.top();
		parserRelation rel = (parserRelation)G->getRel(top->token_type, currentSymbol->token_type);
		
		// trace out the relationship we just found
		if(DEBUG_TRACING) std::cout << "found relation between current and top (rel): " << rel << "\n";
		if(DEBUG_TRACING) std::cout << "True Relation: " << G->getRel(top->token_type, currentSymbol->token_type) << std::endl;
		
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
			parserRelation tempRel = (parserRelation) G->getRel(semanticStack.top()->token_type, nt);
			
			// do what is called for with this symbol (a nonterminal)
			semanticAction(nt);
			
			// do a shift operation by putting the new relation and symbol onto the stack
			Symbol * relSym = new Symbol(tempRel, "");
			Symbol * typeSym = new Symbol(nt, G->vocabSymbolAsString(nt));
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
		std::list<Symbol *>::iterator it = currentReductionList.begin();
		it != currentReductionList.end();
		it++ )
	{
		switch(reductionFactor)
		{
			case Deriv:
				if(poppedSymbols == "n ")
				{
					G_prime->grammarName = (* it)->token_value;
				}
				else if(poppedSymbols == "s ")
				{
					G_prime->startSymbol = (* it)->token_value;
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
					G_prime->nonterminalSet.insert( (* it)->token_value );
				}
				else if(poppedSymbols == "t a ")
				{
					currentDecType = T;
					it++;
					G_prime->terminalSet.insert( (* it)->token_value );
				}
				else if(poppedSymbols == "X a ")
				{
					it++;
					if(currentDecType == NT)
					{
						G_prime->nonterminalSet.insert( (*it)->token_value );
					}
					else if(currentDecType == T)
					{
						G_prime->terminalSet.insert( (* it)->token_value );
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
						G_prime->nonterminalSet.insert( (* it)->token_value );
					}
					else if(currentDecType == T)
					{
						G_prime->terminalSet.insert( (* it)->token_value );
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
				G_prime->symbolTable.push_back(*it);
				
			case Production:
				if(poppedSymbols == "P | R ")
				{
				}
				else if(poppedSymbols == "rnum a  => R ")
				{
					// G_prime->addProduction(currentReductionList);
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
						std::set<std::string>::iterator ntSetIt = G_prime->nonterminalSet.begin();
						ntSetIt != G_prime->nonterminalSet.end();
						ntSetIt++ )
					{
						if( *ntSetIt == (* it)->token_value)
						{
							G_prime->nonterminalSet.insert( (* it)->token_value );
							break;
						}
					}
					
					for(
						std::set<std::string>::iterator tSetIt = G_prime->terminalSet.begin();
						tSetIt != G_prime->terminalSet.end();
						tSetIt++ )
					{
						if( *tSetIt == (* it)->token_value )
						{
							G_prime->terminalSet.insert( (* it)->token_value );
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
			std::list<std::string>::iterator it = G->productions[i].begin();
			it != G->productions[i].end();
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
	ParserApp * engine = new ParserApp("../../input.g");
	
	// scan the input file
	// perform parsing actions on the semantic stack
	if(engine->lexer())
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
