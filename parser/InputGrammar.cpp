/*
 *  InputGrammar.cpp
 *  parser
 *
 * Grammar G-Prime (G')
 * 
 */

#include "InputGrammar.h"


InputGrammar::InputGrammar() {}


InputGrammar::InputGrammar( int numberOfProductions )
{
	precedenceMatrix = new DataTable( numberOfProductions, numberOfProductions );
}
