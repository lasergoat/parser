/*
 *  Grammar.cpp
 *  parser
 *
 */

#include "Grammar.h"

/*
 * GET_REL
 *
 * return relationship from requested coordinates
 */
parserRelation Grammar::getRel(int a, int b)
{
	return (parserRelation) precedenceMatrix->get( a, b );
}


/*
 * SET_REL
 *
 * return void
 * sets relationship from requested coordinates
 */
void Grammar::setRel(int a, int b, int rel)
{
	precedenceMatrix->set( a, b, rel);
}
