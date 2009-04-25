/*
 *  PrecedenceTable.cpp
 *  parser
 *
 *  Created by danek on 4/25/09.
 *  Copyright 2009 University of Central Florida. All rights reserved.
 *
 */

#include "PrecedenceTable.h"


struct cmpStr
{
	bool operator()(const char* s1, const char* s2) const
	{
		return strcmp(s1, s2) < 0;
	}
};

map<string, string, int> precedenceTable;

typedef enum{ NO_REL, EQL, LES, LEQ, GTR, GEQ} relation_t;

// our ghetto precedence table
precedenceTable["S", "S"] = 0;
precedenceTable["S", "L"] = 0;
precedenceTable["S", "D"] = 0;
precedenceTable["S", "X"] = 0;
precedenceTable["S", "P"] = 0;
precedenceTable["S", "R"] = 0;
precedenceTable["S", "n"] = 0;
precedenceTable["S", "t"] = 0;
precedenceTable["S", "nt"] = 0;
precedenceTable["S", "a"] = 0;
precedenceTable["S", "sc"] = 0;
precedenceTable["S", "or"] = 0;
precedenceTable["S", "becomes"] = 0;
precedenceTable["S", "rnum"] = 0;
precedenceTable["S", "s"] = 0;
precedenceTable["S", "lambda"] = 0;

precedenceTable["S", "$"] = 0;
precedenceTable["L", "S"] = 0;
precedenceTable["L", "L"] = 0;
precedenceTable["L", "D"] = EQL;
precedenceTable["L", "X"] = LES;
precedenceTable["L", "P"] = LES;
precedenceTable["L", "R"] = 0;
precedenceTable["L", "n"] = LES;
precedenceTable["L", "t"] = LES;
precedenceTable["L", "nt"] = LES;
precedenceTable["L", "a"] = 0;
precedenceTable["L", "sc"] = 0;
precedenceTable["L", "or"] = 0;
precedenceTable["L", "becomes"] = 0;
precedenceTable["L", "rnum"] = LES;
precedenceTable["L", "s"] = LES;
precedenceTable["L", "lambda"] = 0;
precedenceTable["L", "$"] = EQL;

precedenceTable["D", "S"] = 0;
precedenceTable["D", "L"] = 0;
precedenceTable["D", "D"] = 0;
precedenceTable["D", "X"] = 0;
precedenceTable["D", "P"] = 0;
precedenceTable["D", "R"] = 0;
precedenceTable["D", "n"] = 0;
precedenceTable["D", "t"] = 0;
precedenceTable["D", "nt"] = 0;
precedenceTable["D", "a"] = 0;
precedenceTable["D", "sc"] = LEQ;
precedenceTable["D", "or"] = 0;
precedenceTable["D", "becomes"] = 0;
precedenceTable["D", "rnum"] = 0;
precedenceTable["D", "s"] = 0;
precedenceTable["D", "lambda"] = 0;
precedenceTable["D", "$"] = 0;

precedenceTable["X", "S"] = 0;
precedenceTable["X", "L"] = 0;
precedenceTable["X", "D"] = 0;
precedenceTable["X", "X"] = 0;
precedenceTable["X", "P"] = 0;
precedenceTable["X", "R"] = 0;
precedenceTable["X", "n"] = 0;
precedenceTable["X", "t"] = 0;
precedenceTable["X", "nt"] = 0;
precedenceTable["X", "a"] = LEQ;
precedenceTable["X", "sc"] = GTR;
precedenceTable["X", "or"] = 0;
precedenceTable["X", "becomes"] = 0;
precedenceTable["X", "rnum"] = 0;
precedenceTable["X", "s"] = 0;
precedenceTable["X", "lambda"] = 0;
precedenceTable["X", "$"] = 0;

precedenceTable["P", "S"] = 0;
precedenceTable["P", "L"] = 0;
precedenceTable["P", "D"] = 0;
precedenceTable["P", "X"] = 0;
precedenceTable["P", "P"] = 0;
precedenceTable["P", "R"] = 0;
precedenceTable["P", "n"] = 0;
precedenceTable["P", "t"] = 0;
precedenceTable["P", "nt"] = 0;
precedenceTable["P", "a"] = 0;
precedenceTable["P", "sc"] = GTR;
precedenceTable["P", "or"] = 0;
precedenceTable["P", "becomes"] = 0;
precedenceTable["P", "rnum"] = 0;
precedenceTable["P", "s"] = 0;
precedenceTable["P", "lambda"] = 0;
precedenceTable["P", "$"] = 0;

precedenceTable["R", "S"] = 0;
precedenceTable["R", "L"] = 0;
precedenceTable["R", "D"] = 0;
precedenceTable["R", "X"] = 0;
precedenceTable["R", "P"] = 0;
precedenceTable["R", "R"] = 0;
precedenceTable["R", "n"] = 0;
precedenceTable["R", "t"] = 0;
precedenceTable["R", "nt"] = 0;
precedenceTable["R", "a"] = LEQ;
precedenceTable["R", "sc"] = GTR;
precedenceTable["R", "or"] = GTR;
precedenceTable["R", "becomes"] = 0;
precedenceTable["R", "rnum"] = 0;
precedenceTable["R", "s"] = 0;
precedenceTable["R", "lambda"] = 0;
precedenceTable["R", "$"] = 0;

precedenceTable["n", "S"] = 0;
precedenceTable["n", "L"] = 0;
precedenceTable["n", "D"] = 0;
precedenceTable["n", "X"] = 0;
precedenceTable["n", "P"] = 0;
precedenceTable["n", "R"] = 0;
precedenceTable["n", "n"] = 0;
precedenceTable["n", "t"] = 0;
precedenceTable["n", "nt"] = 0;
precedenceTable["n", "a"] = 0;
precedenceTable["n", "sc"] = 0;
precedenceTable["n", "or"] = 0;
precedenceTable["n", "becomes"] = 0;
precedenceTable["n", "rnum"] = 0;
precedenceTable["n", "s"] = 0;
precedenceTable["n", "lambda"] = 0;
precedenceTable["n", "$"] = 0;

precedenceTable["t", "S"] = 0;
precedenceTable["t", "L"] = 0;
precedenceTable["t", "D"] = 0;
precedenceTable["t", "X"] = 0;
precedenceTable["t", "P"] = 0;
precedenceTable["t", "R"] = 0;
precedenceTable["t", "n"] = 0;
precedenceTable["t", "t"] = 0;
precedenceTable["t", "nt"] = 0;
precedenceTable["t", "a"] = LEQ;
precedenceTable["t", "sc"] = 0;
precedenceTable["t", "or"] = 0;
precedenceTable["t", "becomes"] = 0;
precedenceTable["t", "rnum"] = 0;
precedenceTable["t", "s"] = 0;
precedenceTable["t", "lambda"] = 0;
precedenceTable["t", "$"] = 0;

precedenceTable["nt", "S"] = 0;
precedenceTable["nt", "L"] = 0;
precedenceTable["nt", "D"] = 0;
precedenceTable["nt", "X"] = 0;
precedenceTable["nt", "P"] = 0;
precedenceTable["nt", "R"] = 0;
precedenceTable["nt", "n"] = 0;
precedenceTable["nt", "t"] = 0;
precedenceTable["nt", "nt"] = 0;
precedenceTable["nt", "a"] = LEQ;
precedenceTable["nt", "sc"] = 0;
precedenceTable["nt", "or"] = 0;
precedenceTable["nt", "becomes"] = 0;
precedenceTable["nt", "rnum"] = 0;
precedenceTable["nt", "s"] = 0;
precedenceTable["nt", "lambda"] = 0;
precedenceTable["nt", "$"] = 0;

precedenceTable["a", "S"] = 0;
precedenceTable["a", "L"] = 0;
precedenceTable["a", "D"] = 0;
precedenceTable["a", "X"] = 0;
precedenceTable["a", "P"] = 0;
precedenceTable["a", "R"] = 0;
precedenceTable["a", "n"] = 0;
precedenceTable["a", "t"] = 0;
precedenceTable["a", "nt"] = 0;
precedenceTable["a", "a"] = GTR;
precedenceTable["a", "sc"] = GTR;
precedenceTable["a", "or"] = GTR;
precedenceTable["a", "becomes"] = LEQ;
precedenceTable["a", "rnum"] = 0;
precedenceTable["a", "s"] = 0;
precedenceTable["a", "lambda"] = GTR;
precedenceTable["a", "$"] = 0;

precedenceTable["sc", "S"] = 0;
precedenceTable["sc", "L"] = 0;
precedenceTable["sc", "D"] = 0;
precedenceTable["sc", "X"] = 0;
precedenceTable["sc", "P"] = 0;
precedenceTable["sc", "R"] = 0;
precedenceTable["sc", "n"] = GTR;
precedenceTable["sc", "t"] = GTR;
precedenceTable["sc", "nt"] = GTR;
precedenceTable["sc", "a"] = 0;
precedenceTable["sc", "sc"] = 0;
precedenceTable["sc", "or"] = 0;
precedenceTable["sc", "becomes"] = 0;
precedenceTable["sc", "rnum"] = GTR;
precedenceTable["sc", "s"] = GTR;
precedenceTable["sc", "lambda"] = 0;
precedenceTable["sc", "$"] = 0;

precedenceTable["or", "S"] = 0;
precedenceTable["or", "L"] = 0;
precedenceTable["or", "D"] = 0;
precedenceTable["or", "X"] = 0;
precedenceTable["or", "P"] = 0;
precedenceTable["or", "R"] = LEQ;
precedenceTable["or", "n"] = 0;
precedenceTable["or", "t"] = 0;
precedenceTable["or", "nt"] = 0;
precedenceTable["or", "a"] = 0;
precedenceTable["or", "sc"] = 0;
precedenceTable["or", "or"] = 0;
precedenceTable["or", "becomes"] = 0;
precedenceTable["or", "rnum"] = 0;
precedenceTable["or", "s"] = 0;
precedenceTable["or", "lambda"] = LES;
precedenceTable["or", "$"] = 0;

precedenceTable["becomes", "S"] = 0;
precedenceTable["becomes", "L"] = 0;
precedenceTable["becomes", "D"] = 0;
precedenceTable["becomes", "X"] = 0;
precedenceTable["becomes", "P"] = 0;
precedenceTable["becomes", "R"] = LEQ;
precedenceTable["becomes", "n"] = 0;
precedenceTable["becomes", "t"] = 0;
precedenceTable["becomes", "nt"] = 0;
precedenceTable["becomes", "a"] = 0;
precedenceTable["becomes", "sc"] = 0;
precedenceTable["becomes", "or"] = 0;
precedenceTable["becomes", "becomes"] = 0;
precedenceTable["becomes", "rnum"] = 0;
precedenceTable["becomes", "s"] = 0;
precedenceTable["becomes", "lambda"] = LES;
precedenceTable["becomes", "$"] = 0;

precedenceTable["rnum", "S"] = 0;
precedenceTable["rnum", "L"] = 0;
precedenceTable["rnum", "D"] = 0;
precedenceTable["rnum", "X"] = 0;
precedenceTable["rnum", "P"] = 0;
precedenceTable["rnum", "R"] = 0;
precedenceTable["rnum", "n"] = 0;
precedenceTable["rnum", "t"] = 0;
precedenceTable["rnum", "nt"] = 0;
precedenceTable["rnum", "a"] = LEQ;
precedenceTable["rnum", "sc"] = 0;
precedenceTable["rnum", "or"] = 0;
precedenceTable["rnum", "becomes"] = 0;
precedenceTable["rnum", "rnum"] = 0;
precedenceTable["rnum", "s"] = 0;
precedenceTable["rnum", "lambda"] = 0;
precedenceTable["rnum", "$"] = 0;

precedenceTable["s", "S"] = 0;
precedenceTable["s", "L"] = 0;
precedenceTable["s", "D"] = 0;
precedenceTable["s", "X"] = 0;
precedenceTable["s", "P"] = 0;
precedenceTable["s", "R"] = 0;
precedenceTable["s", "n"] = 0;
precedenceTable["s", "t"] = 0;
precedenceTable["s", "nt"] = 0;
precedenceTable["s", "a"] = 0;
precedenceTable["s", "sc"] = GTR;
precedenceTable["s", "or"] = 0;
precedenceTable["s", "becomes"] = 0;
precedenceTable["s", "rnum"] = 0;
precedenceTable["s", "s"] = 0;
precedenceTable["s", "lambda"] = 0;
precedenceTable["s", "$"] = 0;

precedenceTable["lambda", "S"] = 0;
precedenceTable["lambda", "L"] = 0;
precedenceTable["lambda", "D"] = 0;
precedenceTable["lambda", "X"] = 0;
precedenceTable["lambda", "P"] = 0;
precedenceTable["lambda", "R"] = 0;
precedenceTable["lambda", "n"] = 0;
precedenceTable["lambda", "t"] = 0;
precedenceTable["lambda", "nt"] = 0;
precedenceTable["lambda", "a"] = 0;
precedenceTable["lambda", "sc"] = GTR;
precedenceTable["lambda", "or"] = GTR;
precedenceTable["lambda", "becomes"] = 0;
precedenceTable["lambda", "rnum"] = 0;
precedenceTable["lambda", "s"] = 0;
precedenceTable["lambda", "lambda"] = 0;
precedenceTable["lambda", "$"] = 0;

precedenceTable["$", "S"] = 0;
precedenceTable["$", "L"] = LES;
precedenceTable["$", "D"] = LES;
precedenceTable["$", "X"] = LES;
precedenceTable["$", "P"] = LES;
precedenceTable["$", "R"] = 0;
precedenceTable["$", "n"] = LES;
precedenceTable["$", "t"] = LES;
precedenceTable["$", "nt"] = LES;
precedenceTable["$", "a"] = 0;
precedenceTable["$", "sc"] = 0;
precedenceTable["$", "or"] = 0;
precedenceTable["$", "becomes"] = 0;
precedenceTable["$", "rnum"] = LES;
precedenceTable["$", "s"] = LES;
precedenceTable["$", "lambda"] = 0;
precedenceTable["$", "$"] = GTR;
