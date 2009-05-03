/*
 *  DataTable.h
 *  parser
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

