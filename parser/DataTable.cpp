/*
 *  Table.cpp
 *  parser
 *
 */

#include "DataTable.h"

DataTable::DataTable(int w, int h)
{
	width = w;
	height = h;
	matrix = new int[w * h];
}

void DataTable::set(int a, int b, int s)
{
	if(a > width || b > height)
	{
		// throw error
	}
	matrix[ a * height + b ] = s;
}

int DataTable::get(int a, int b)
{
	return matrix[ a * height + b ];
}

