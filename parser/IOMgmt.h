#ifndef _IOMGR
#define _IOMGR

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

#include "AppError.h"
#define MARGINSIZE 50

	namespace IOMgmt
	{
		/*************************************************************************
		* IOError
		*************************************************************************/
		class IOError: public AppError
		{
			public:
				IOError();
				IOError(string Msg);
				IOError(string Msg, string Org);

			private:
				static const string IOERROR;
		};

		/*************************************************************************
		* TokenError
		*************************************************************************/
		class TokenError: public AppError
		{
			public:
				TokenError();
				TokenError(string Msg);
				TokenError(string Msg, string Org);
		
			private:
				static const string TOKENERROR;
		};

		/*************************************************************************
		* IOMgr
		*************************************************************************/
		class IOMgr
		{	
			public:
				IOMgr();

				virtual void promptForFile(ifstream &file, string prompt);
				virtual void promptForFile(ofstream &file, string prompt);
				virtual void openFile(ifstream& file, string name) throw(IOError);
				virtual void openFile(ofstream& file, string name) throw(IOError);
				virtual void openFile(ifstream& file) throw(IOError);
				virtual void openFile(ofstream& file) throw(IOError);

				string userResponse(string p);
				void close(ifstream &file) throw( IOError );
				void setCursor(ifstream &file) throw( IOError );
				void resetCursor(ifstream &file) throw( IOError );
				string getName() const;

			protected:
				long cursor;
				string fileName;
		};

		/*************************************************************************
		* Tokenizer
		*************************************************************************/
		class Tokenizer
		{
			public:
				Tokenizer() throw(IOError);
				bool more();
				string scan();
				void setDelims(string symbols) throw (TokenError);
				string getDelims();
				string getDiscard();
				void reset();
				void putBack(string token);
			
			private:
				ifstream fin;
				static const string DELIMS;
				string delims;
				string backbuff;
				string discard;
				char nextChar();
				bool isDelim(char x);
		};

		extern IOMgr io;
	}

#endif
