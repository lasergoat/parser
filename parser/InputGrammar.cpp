/*
 *  InputGrammar.cpp
 *  parser
 *
 * Grammar G-Prime (G')
 * 
 */

#include "InputGrammar.h"


InputGrammar::InputGrammar()
{
	numberOfProductions = 0;
}

void InputGrammar::IncrementProductionCount()
{
	numberOfProductions++;
}
