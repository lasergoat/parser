/*
 *  ParsingGrammar.h
 *  parser
 *
 *  Created by danek on 4/26/09.
 *  Copyright 2009 University of Central Florida. All rights reserved.
 *
 */

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
	enum parserVocab
		{
			Start,			// S
			Line,			// L
			Deriv,			// D
			Double,			// X
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
			end				// $ (end of input)
		};
};
