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
		InputGrammar( int numberOfProductions);
		
		std::string grammarName;
		std::string startSymbol;
		
		std::list<Symbol*> symbolTable;
		std::set<std::string> nonterminalSet;
		std::set<std::string> terminalSet;
};

#endif
