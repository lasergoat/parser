/*
 *  ParserApp.h
 *  parser
 *
 */

#ifndef _PARSER_APP
#define _PARSER_APP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stack>

#include "ParsingGrammar.h"
#include "InputGrammar.h"

using namespace ParsingDefinitions;

class ParserApp
{
	public:
		
		ParserApp( const char * filename);
		bool lexer();
		
		ParsingGrammar	* G;
		InputGrammar	* G_prime;
		
	private:
		
		std::ifstream input;
		
		std::stack<Symbol *> semanticStack;
		
		Symbol * currentSymbol;
		vocab_t searchProductionToReduce();
		
		std::list<Symbol *> currentReductionList;
		
		void semanticAction(vocab_t reductionFactor);
		
		std::string poppedSymbols;
};

#endif
