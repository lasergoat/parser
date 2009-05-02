/*
 *  PrecedenceTable.h
 *  parser
 *
 *  Created by danek on 4/25/09.
 *
 */

#ifndef _PRECEDENCE_TABLE
#define _PRECEDENCE_TABLE

// these are double includes, but they have
// a conditional statement so the rules are
// not duplicated
#include "ParsingGrammar.h"
#include "DataTable.h"

using namespace ParsingGrammar;

class PrecedenceTable: public DataTable
{
	public:
		
		PrecedenceTable();
};

#endif
