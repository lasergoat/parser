/*
 *  PrecedenceTable.h
 *  parser
 *
 *  Created by danek on 4/25/09.
 *
 */

#ifndef _PrecedenceTable
#define _PrecedenceTable

#include "ParsingGrammar.h"
#include "DataTable.h"
using namespace ParsingGrammar;

class PrecedenceTable: public DataTable
{
	public:
		PrecedenceTable();
};

#endif

