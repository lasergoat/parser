/*
 *  PrecedenceTable.h
 *  parser
 *
 * Grammar G-Prime (G')
 * 
 */

#ifndef _INPUT_GRAMMAR
#define _INPUT_GRAMMAR

#include "Grammar.h"

using namespace ParsingDefinitions;

class InputGrammar: public Grammar
{
	public:
		InputGrammar();
		
		void IncrementProductionCount();
		std::string grammarName;
		std::string startSymbol;
		
		std::list<Symbol*> symbolTable;
		std::set<std::string> nonterminalSet;
		std::set<std::string> terminalSet;
	
	private:
		int numberOfProductions;
};

#endif
