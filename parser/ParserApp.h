/*
 *  ParserApp.h
 *  parser
 *
 *  Created by danek on 4/30/09.
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
				Symbol() {};
				Symbol(int tt, std::string tv);
				
				//  0 - 19 : Relation
				// 20 - 36 : Vocab Symbol
				int token_type;
				std::string token_value;
			    std::string type_value;
		};
		
		std::ifstream input;
		std::stack<ParserApp::Symbol*> semanticStack;
		PrecedenceTable* table;
		Symbol* currentSymbol;
		ParsingGrammar::vocab_t getSymbolTypeFromInputString(std::string str);
		vocab_t searchProductionToReduce();
		std::string vocabSymbolAsString(vocab_t type);
		std::list<std::string> grammar_productions[end];
		std::list<Symbol*> currentReductionList;
		
		void semanticAction(vocab_t reductionFactor);
		
		std::string poppedSymbols;
		
		std::set<std::string> nonterminalSet;
		std::set<std::string> terminalSet;
		
		std::string grammarName;
		std::string startSymbol;
		
		std::list<Symbol*> symbolTable;
};

#endif
