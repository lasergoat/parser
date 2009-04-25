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

using namespace std;

int main()
{
	FILE* file = fopen("input.g", "r");
	
	std::string token;
	
	token = getNextToken(file);
	
	while(token != "$")
	{
		//State1: token is a comment
		if(token == "#")
		{
			fscanf(file, "\n");
			getNextToken(file);
			continue;
		}
		
		else if(
	}
				
	
	return 0;
}

string getNextToken(FILE* fin)
{
	string tkn;
	fscanf(fin, "%s ", tkn);
	return tkn;
}