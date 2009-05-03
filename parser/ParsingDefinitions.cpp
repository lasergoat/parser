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
