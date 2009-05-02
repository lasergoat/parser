/*
 *  ParserApp.h
 *  parser
 *
 *  Created by danek on 4/30/09.
 *  Copyright 2009 University of Central Florida. All rights reserved.
 *
 */

#ifndef _PARSER_APP
#define _PARSER_APP

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stack>
#include <set>
#include <list>

#include "PrecedenceTable.h"

using namespace ParsingGrammar;

class ParserApp
{
	public:
		
		ParserApp( const char * filename);
		bool parse();
		bool lexer();
		
	private:
		
		class Symbol 
		{
			public:
				int token_type; // 0 -19: Relation, 20+:Vocab Symbol
				std::string token_value;             
		};
		
		std::ifstream input;
		std::stack<ParserApp::Symbol*> semanticStack;
		PrecedenceTable* table;
		Symbol* currentSymbol;
		ParsingGrammar::vocab_t getSymbolTypeFromInputString(std::string str);
};

#endif
