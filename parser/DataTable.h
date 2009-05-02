/*
 *  DataTable.h
 *  parser
 *
 *  Created by danek on 4/26/09.
 *  Copyright 2009 University of Central Florida. All rights reserved.
 *
 *  A non resizeable table
 */

#ifndef _DataTable
#define _DataTable

class DataTable
{
	public:
		DataTable(int w, int h);
		void set(int a, int b, int s);
		int get(int a, int b);
	
	protected:
		int *matrix;
		int width;
		int height;
};

#endif

