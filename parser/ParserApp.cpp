/*
 *  ParserApp.cpp
 *  parser
 *
 *  Daniel Walker
 *  Austin Montoya
 *
 */


#include <iostream>
#include <fstream>
#include <string>
#include "PrecedenceTable.h"

int main()
{
	std::ifstream input("../../input.g", std::ifstream::in);
	
	char tk, temp, ignore;
	
	PrecedenceTable *table = new PrecedenceTable();
	
	while( input.good() )
	{
		tk = (char) input.get();
		
		// State 1: token is a comment
		if(tk == '#')
		{
			// ignore comment lines
			do
			{
				ignore = (char) input.get();
			}
			// get to the next new line
			while( ignore != '\n');
		}
		
		else if( tk == '!')
		{
			do
			{
				temp = (char) input.get();
			}
			while( temp != ':');
		}
		
	}
	
	input.close();
	
	return 0;
}

