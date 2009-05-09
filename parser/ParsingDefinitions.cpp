/*
 *  ParsingDefinitions.cpp
 *  parser
 *
 */

#include "ParsingDefinitions.h"


/*
 * Symbol Class Intake Constructor
 *
 * takes in type, value
 */
ParsingDefinitions::Symbol::Symbol(int tt, std::string tv) :
	token_type(tt),
	token_value(tv) {}

/*
 * Production Class Intake Constructor
 *
 * takes in left, right
 */
ParsingDefinitions::Production::Production(vocab_t left, std::string right) :
leftPart(left),
rightPart(right) {}
