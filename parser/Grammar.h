/*
 *  Grammar.h
 *  parser
 *
 */

#ifndef _GRAMMAR
#define _GRAMMAR

#include "DataTable.h"
#include "ParsingDefinitions.h"

#include <set>
#include <list>

#define MAX_PRODUCTIONS 200

using namespace ParsingDefinitions;

class Grammar
{
	public:
		
		// these ints may be ints or vocab_t or parserRelation, but
		// they will be downcast to ints, upon retrieval,
		// they may be cast as whatever they originally were
		parserRelation getRel(int a, int b);
		void setRel(int a, int b, int rel);
		
		// list of productions (non terminals)
		//std::list<std::string> productions[ MAX_PRODUCTIONS ];
		Production * productions[ MAX_PRODUCTIONS ];
	
	protected:
		
		// holds relationships
		DataTable * precedenceMatrix;
};

#endif
