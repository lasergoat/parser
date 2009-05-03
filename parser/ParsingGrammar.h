/*
 *  ParsingGrammar.h
 *  parser
 *
 * Grammar G
 * 
 */

#ifndef _PARSING_GRAMMAR
#define _PARSING_GRAMMAR

#include "Grammar.h"

using namespace ParsingDefinitions;

class ParsingGrammar: public Grammar
{
	public:
		ParsingGrammar();
		std::string vocabSymbolAsString(vocab_t type);
		vocab_t getSymbolTypeFromInputString(std::string str);
		
	private:
		void constructProductions();
		void computePrecedenceMatrix();
};

#endif
