/*
 *  PrecedenceTable.cpp
 *  parser
 *
 */

#include "PrecedenceTable.h"

/*
 * PRECEDENCE_TABLE CONSTRUCTOR
 *
 * return PrecedenceTable <pointer>
 * with all relations already set
 *
 * make a data table large enough to hold all symbols up to end
 * client methods are ->set() and ->get()
 */
PrecedenceTable::PrecedenceTable() : DataTable(end, end)
{
	// S Production
	set(Start, Start,              0	);
	set(Start, Line,               0	);
	set(Start, Deriv,              0	);
	set(Start, NTList,             0	);
	set(Start, Production,         0	);
	set(Start, Rule,               0	);
	set(Start, name,               0	);
	set(Start, terminal,           0	);
	set(Start, nonterminal,        0	);
	set(Start, vocabsymbol,        0	);
	set(Start, semicolon,          0	);
	set(Start, choice,             0	);
	set(Start, becomes,            0	);
	set(Start, rulenumber,         0	);
	set(Start, startdec,           0	);
	set(Start, lambda,             0	);
	set(Start, end,                0	);
	
	// L Production
	set(Line, Start,               0	);
	set(Line, Line,                0	);
	set(Line, Deriv,               EQL	);
	set(Line, NTList,              LES	);
	set(Line, Production,          LES	);
	set(Line, Rule,                0	);
	set(Line, name,                LES	);                                 
	set(Line, terminal,            LES	);                                 
	set(Line, nonterminal,         LES	);                                 
	set(Line, vocabsymbol,         0	);
	set(Line, semicolon,           0	);
	set(Line, choice,              0	);
	set(Line, becomes,             0	);
	set(Line, rulenumber,          LES	);                                 
	set(Line, startdec,            LES	);                                 
	set(Line, lambda,              0	);
	set(Line, end,                 GTR	);                                 
	
	// D Production
	set(Deriv, Start,              0	);
	set(Deriv, Line,               0	);
	set(Deriv, Deriv,              0	);
	set(Deriv, NTList,             0	);
	set(Deriv, Production,         0	);
	set(Deriv, Rule,               0	);
	set(Deriv, name,               0	);
	set(Deriv, terminal,           0	);
	set(Deriv, nonterminal,        0	);
	set(Deriv, vocabsymbol,        0	);
	set(Deriv, semicolon,          EQL	);                                 
	set(Deriv, choice,             0	);
	set(Deriv, becomes,            0	);
	set(Deriv, rulenumber,         0	);
	set(Deriv, startdec,           0	);
	set(Deriv, lambda,             0	);
	set(Deriv, end,                0	);
	
	// X Production (allows a list of symbols t or nt)
	set(NTList, Start,             0	);
	set(NTList, Line,              0	);
	set(NTList, Deriv,             0	);
	set(NTList, NTList,            0	);
	set(NTList, Production,        0	);
	set(NTList, Rule,              0	);
	set(NTList, name,              0	);
	set(NTList, terminal,          0	);
	set(NTList, nonterminal,       0	);
	set(NTList, vocabsymbol,       EQL	);                                 
	set(NTList, semicolon,         GTR	);                                 
	set(NTList, choice,            0	);
	set(NTList, becomes,           0	);
	set(NTList, rulenumber,        0	);
	set(NTList, startdec,          0	);
	set(NTList, lambda,            0	);
	set(NTList, end,               0	);
	
	// P Produciton
	set(Production, Start,         0	);
	set(Production, Line,          0	);
	set(Production, Deriv,         0	);
	set(Production, NTList,        0	);
	set(Production, Production,    0	);
	set(Production, Rule,          0	);
	set(Production, name,          0	);
	set(Production, terminal,      0	);
	set(Production, nonterminal,   0	);
	set(Production, vocabsymbol,   0	);
	set(Production, semicolon,     GTR	);                                 
	set(Production, choice,        EQL	);
	set(Production, becomes,       0	);
	set(Production, rulenumber,    0	);
	set(Production, startdec,      0	);
	set(Production, lambda,        0	);
	set(Production, end,           0	);
	
	// R Production
	set(Rule, Start,               0	);
	set(Rule, Line,                0	);
	set(Rule, Deriv,               0	);
	set(Rule, NTList,              0	);
	set(Rule, Production,          0	);
	set(Rule, Rule,                0	);
	set(Rule, name,                0	);
	set(Rule, terminal,            0	);
	set(Rule, nonterminal,         0	);
	set(Rule, vocabsymbol,         EQL	);                                 
	set(Rule, semicolon,           GTR	);                                 
	set(Rule, choice,              GTR	);                                 
	set(Rule, becomes,             0	);
	set(Rule, rulenumber,          0	);
	set(Rule, startdec,            0	);
	set(Rule, lambda,              0	);
	set(Rule, end,                 0	);
	
	// n terminal
	set(name, Start,               0	);
	set(name, Line,                0	);
	set(name, Deriv,               0	);
	set(name, NTList,              0	);
	set(name, Production,          0	);
	set(name, Rule,                0	);
	set(name, name,                0	);
	set(name, terminal,            0	);
	set(name, nonterminal,         0	);
	set(name, vocabsymbol,         0	);
	set(name, semicolon,           GTR	);
	set(name, choice,              0	);
	set(name, becomes,             0	);
	set(name, rulenumber,          0	);
	set(name, startdec,            0	);
	set(name, lambda,              0	);
	set(name, end,                 0	);
	
	// t terminal (terminal listing declaration)
	set(terminal, Start,           0	);
	set(terminal, Line,            0	);
	set(terminal, Deriv,           0	);
	set(terminal, NTList,          0	);
	set(terminal, Production,      0	);
	set(terminal, Rule,            0	);
	set(terminal, name,            0	);
	set(terminal, terminal,        0	);
	set(terminal, nonterminal,     0	);
	set(terminal, vocabsymbol,     EQL	);                                 
	set(terminal, semicolon,       0	);
	set(terminal, choice,          0	);
	set(terminal, becomes,         0	);
	set(terminal, rulenumber,      0	);
	set(terminal, startdec,        0	);
	set(terminal, lambda,          0	);
	set(terminal, end,             0	);
	
	// nt terminal (nonterminal listing declaration)
	set(nonterminal, Start,        0	);
	set(nonterminal, Line,         0	);
	set(nonterminal, Deriv,        0	);
	set(nonterminal, NTList,       0	);
	set(nonterminal, Production,   0	);
	set(nonterminal, Rule,         0	);
	set(nonterminal, name,         0	);
	set(nonterminal, terminal,     0	);
	set(nonterminal, nonterminal,  0	);
	set(nonterminal, vocabsymbol,  EQL	);                                 
	set(nonterminal, semicolon,    0	);
	set(nonterminal, choice,       0	);
	set(nonterminal, becomes,      0	);
	set(nonterminal, rulenumber,   0	);
	set(nonterminal, startdec,     0	);
	set(nonterminal, lambda,       0	);
	set(nonterminal, end,          0	);
	
	// a terminal (any symbol in the input alphabet)
	set(vocabsymbol, Start,        0	);
	set(vocabsymbol, Line,         0	);
	set(vocabsymbol, Deriv,        0	);
	set(vocabsymbol, NTList,       0	);
	set(vocabsymbol, Production,   0	);
	set(vocabsymbol, Rule,         0	);
	set(vocabsymbol, name,         0	);
	set(vocabsymbol, terminal,     0	);
	set(vocabsymbol, nonterminal,  0	);
	set(vocabsymbol, vocabsymbol,  GTR	);                                 
	set(vocabsymbol, semicolon,    GTR	);                                 
	set(vocabsymbol, choice,       GTR	);                                 
	set(vocabsymbol, becomes,      EQL	);                                 
	set(vocabsymbol, rulenumber,   0	);
	set(vocabsymbol, startdec,     0	);
	set(vocabsymbol, lambda,       GTR	);                                 
	set(vocabsymbol, end,          0	);
	
	set(semicolon, Start,          0	);
	set(semicolon, Line,           0	);
	set(semicolon, Deriv,          0	);
	set(semicolon, NTList,         0	);
	set(semicolon, Production,     0	);
	set(semicolon, Rule,           0	);
	set(semicolon, name,           GTR	);                                 
	set(semicolon, terminal,       GTR	);                                 
	set(semicolon, nonterminal,    GTR	);                                 
	set(semicolon, vocabsymbol,    0	);
	set(semicolon, semicolon,      0	);
	set(semicolon, choice,         0	);
	set(semicolon, becomes,        0	);
	set(semicolon, rulenumber,     GTR	);                                 
	set(semicolon, startdec,       GTR	);                                 
	set(semicolon, lambda,         0	);
	set(semicolon, end,            GTR	);
	
	// or terminal
	set(choice, Start,             0	);
	set(choice, Line,              0	);
	set(choice, Deriv,             0	);
	set(choice, NTList,            0	);
	set(choice, Production,        0	);
	set(choice, Rule,              LEQ	);                                 
	set(choice, name,              0	);
	set(choice, terminal,          0	);
	set(choice, nonterminal,       0	);
	set(choice, vocabsymbol,       0	);
	set(choice, semicolon,         0	);
	set(choice, choice,            0	);
	set(choice, becomes,           0	);
	set(choice, rulenumber,        0	);
	set(choice, startdec,          0	);
	set(choice, lambda,            LES	);                                 
	set(choice, end,               0	);
	
	set(becomes, Start,            0	);
	set(becomes, Line,             0	);
	set(becomes, Deriv,            0	);
	set(becomes, NTList,           0	);
	set(becomes, Production,       0	);
	set(becomes, Rule,             LEQ	);                                 
	set(becomes, name,             0	);
	set(becomes, terminal,         0	);
	set(becomes, nonterminal,      0	);
	set(becomes, vocabsymbol,      0	);
	set(becomes, semicolon,        0	);
	set(becomes, choice,           0	);
	set(becomes, becomes,          0	);
	set(becomes, rulenumber,       0	);
	set(becomes, startdec,         0	);
	set(becomes, lambda,           LES	);                                 
	set(becomes, end,              0	);
	
	set(rulenumber, Start,         0	);
	set(rulenumber, Line,          0	);
	set(rulenumber, Deriv,         0	);
	set(rulenumber, NTList,        0	);
	set(rulenumber, Production,    0	);
	set(rulenumber, Rule,          0	);
	set(rulenumber, name,          0	);
	set(rulenumber, terminal,      0	);
	set(rulenumber, nonterminal,   0	);
	set(rulenumber, vocabsymbol,   EQL	);                                 
	set(rulenumber, semicolon,     0	);
	set(rulenumber, choice,        0	);
	set(rulenumber, becomes,       0	);
	set(rulenumber, rulenumber,    0	);
	set(rulenumber, startdec,      0	);
	set(rulenumber, lambda,        0	);
	set(rulenumber, end,           0	);
	
	// s terminal the start symbol declaration
	// from the nonterminal alphabet
	set(startdec, Start,           0	);
	set(startdec, Line,            0	);
	set(startdec, Deriv,           0	);
	set(startdec, NTList,          0	);
	set(startdec, Production,      0	);
	set(startdec, Rule,            0	);
	set(startdec, name,            0	);
	set(startdec, terminal,        0	);
	set(startdec, nonterminal,     0	);
	set(startdec, vocabsymbol,     0	);
	set(startdec, semicolon,       GTR	);                                 
	set(startdec, choice,          0	);
	set(startdec, becomes,         0	);
	set(startdec, rulenumber,      0	);
	set(startdec, startdec,        0	);
	set(startdec, lambda,          0	);
	set(startdec, end,             0	);
	
	set(lambda, Start,             0	);
	set(lambda, Line,              0	);
	set(lambda, Deriv,             0	);
	set(lambda, NTList,            0	);
	set(lambda, Production,        0	);
	set(lambda, Rule,              0	);
	set(lambda, name,              0	);
	set(lambda, terminal,          0	);
	set(lambda, nonterminal,       0	);
	set(lambda, vocabsymbol,       GTR	);
	set(lambda, semicolon,         GTR	);                                 
	set(lambda, choice,            GTR	);                                 
	set(lambda, becomes,           0	);
	set(lambda, rulenumber,        0	);
	set(lambda, startdec,          0	);
	set(lambda, lambda,            0	);
	set(lambda, end,               0	);
	
	set(end, Start,                0	);
	set(end, Line,                 LES	);                                 
	set(end, Deriv,                LES	);                                 
	set(end, NTList,               LES	);                                 
	set(end, Production,           LES	);                                 
	set(end, Rule,                 0	);
	set(end, name,                 LES	);                                 
	set(end, terminal,             LES	);                                 
	set(end, nonterminal,          LES	);                                 
	set(end, vocabsymbol,          0	);
	set(end, semicolon,            0	);
	set(end, choice,               0	);
	set(end, becomes,              0	);
	set(end, rulenumber,           LES	);
	set(end, startdec,             LES	);
	set(end, lambda,               0	);
	set(end, end,                  0	);
}
