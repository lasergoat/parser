/*
 *  ParserApp.h
 *  parser
 *
 *  Created by danek on 4/30/09.
 *  Copyright 2009 University of Central Florida. All rights reserved.
 *
 */

#ifndef PARSER_APP_H
#define PARSER_APP_H

#include "ParsingGrammar.h"
#include "PrecedenceTable.h"

typedef struct 
	{
		int token_type; //0 -19: Relation, 20+:Vocab Symbol
		std::string token_value;             
	} Symbol;

public class ParserApp
	{
		
		
	public:
		
		
		
	private:
		vocab_t currentSymbol;
		Symbol stack[10000];
		
		bool isRelation(Symbol s) { return s.token_type < 20; }
	}
#endif //PARSER_GRAMMAR_H
