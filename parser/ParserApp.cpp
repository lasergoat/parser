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
#include <stack>
#include "PrecedenceTable.h"

typedef struct { 
	char* token;
	int type; //0 == Nonterminal, 1 = terminal
	bool isStart = false;
} symbol;

parserVocab getSymbolType(char* symbolName);

symbol symbolTable[100];

int main()
{
	std::ifstream input("../../input.g", std::ifstream::in);
	
	
	/* Stack */
	std::stack<int> Stack;
	
	Stack.push((parserVocab) end);
	char tk, ignore;
	int i;

	
	PrecedenceTable *table = new PrecedenceTable();
	
	while( input.good() )
	{
		char currentSymbol[100];
		
		//char tempString[20] = {0};
		i = 0;
		
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
			tk =(char) input.get();
		}
		
		
		if(tk == '!')
		{
			input.unget();
			input.getline(currentSymbol, 100);
		}
		else
		{
			input.unget();
			input >> currentSymbol;
		}
		
		parserVocab symbolType = getSymbolType(currentSymbol);
		
		/*else if( tk == '!')
		{
			char tempString[20];
			i = 0;
			do
			{
				temp = (char) input.get();
				tempString[i++] = temp;
			}
			while( temp != ':');
			tempString[i] = 0;
			// tk is now ':'
			
			std::cout << tempString << "\n";
			// see what tempString has in it
			if(strcmp(tempString, "name") == 0)
			{
				char tempString[20];
				i = 0;
				do
				{
					
					temp = (char) input.get();
					tempString[i++] = temp;
				}
				while(temp != ';');
				tempString[i] = 0;
				char* grammarName = tempString;
				parserRelation relation = (parserRelation) table->get((parserVocab) Stack.top(), (parserVocab) name);
				if(relation == LES || relation == EQL || relation == LEQ)
				{
					Stack.push(relation);
					Stack.push(name);
				}
			}
			else if(strcmp(tempString, "start") == 0)
			{
				// start symbol
			}
			else if(strcmp(tempString, "non-terminals") == 0)
			{
				// read in non terms
			}
			else if(strcmp(tempString, "terminals") == 0)
			{
				// read terms
			}
		}*/
        
		
	}
	
	input.close();
	
	return 0;
}

parserVocab getSymbolType(char* symbolName)
{
	char temp[100];
	//State 1: Could be a nonterminal dec, terminal dec, or name dec
	//           -need to find it here, and make sure its correct
	if(symbolName[0] == '!')
	{ 
		int i = 1;
		while(symbolName[i] != ':' || symbolName[i] != 0)
		{
			temp[i] = symbolName[i];
			i++;
		}
		
		if(!strcmp("name:", temp))
		{
			return name;
		}
		else if(!strcmp("non-terminals:", temp))
		{
			return nonterminal;
		}
		else if(!strcmp("terminals:", temp))
		{
			return terminal;
		}
		else
		{
			return error;
		}
		
	} else if(isnumber(symbolName[0])) //State 2: number
	{
		if(symbolName[1] == ':')
		{
			return rulenumber;
		}
		else return error;
	} else if(isalpha(symbolName[0]))
	{
	    if(!strcmp("lambda;", symbolName))
		{
			return lambda;
		}
		else
		{
			if(findSymbolInTable(temp) != NULL)
			{
				return vocabsymbol;
			}
			else
			{
				return error;
			}//assuming nonterminals and terminals are defined by one letter
	}
}

