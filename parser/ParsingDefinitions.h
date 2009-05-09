/*
 *  ParsingDefinitions.h
 *  parser
 *
 */

#ifndef _PARSING_DEFINITIONS
#define _PARSING_DEFINITIONS

#include <string>

namespace ParsingDefinitions
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
		Prod,			// P
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
	
	
	/*
	 * SYMBOL
	 *
	 * holds
	 *  - type
	 *  - value
	 */
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
	
	
	/*
	 * PRODUCTION
	 *
	 * holds
	 *  - leftPart
	 *  - rightPart
	 */
	class Production
	{
		public:
			Production() {};
			Production(vocab_t left, std::string right);
			
			vocab_t leftPart;
			std::string rightPart;
	};
};

#endif
