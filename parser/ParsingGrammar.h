/*
 *  ParsingGrammar.h
 *  parser
 *
 *  Created by danek on 4/26/09.
 *  Copyright 2009 University of Central Florida. All rights reserved.
 *
 */

#ifndef _PARSING_GRAMMAR
#define _PARSING_GRAMMAR

namespace ParsingGrammar
{
	/*
	 * PARSER RELATIONS
	 *
	 */
	enum parserRelation
	{
		NO_REL,
		EQL,
		LES,
		LEQ,
		GTR,
		GEQ
	};

	/*
	 * PARSER VOCABULARY
	 * (terminals and non terminals)
	 *
	 */
	enum vocab_t
	{
		Start = 20,		// S
		Line,			// L
		Deriv,			// D
		NTList,			// X
		Production,		// P
		Rule,			// R
		name,			// n
		terminal,		// t
		nonterminal,	// nt
		vocabsymbol,	// a
		semicolon,		// ; (sc)
		choice,			// | (or)
		becomes,		// =>
		rulenumber,		// rnum
		startdec,		// s (start symbol declaration)
		lambda,			// lambda
		end,			// $ (end of input)
		error = -1
	};

	enum symbolType
	{
		NT,				// nonterminal
		T,				// terminal
		S				// start
	};
	
};

#endif

