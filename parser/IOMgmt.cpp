#include <iomanip>
#include <cstdlib>
#include <cctype>
using namespace std;

#include "IOMgmt.h"
using namespace IOMgmt;

	namespace IOMgmt
	{
	    const string IOError::IOERROR = "IOError{}";
		const string TokenError::TOKENERROR = "TokenError{}";
	    const string Tokenizer::DELIMS = " \t\n";

		IOMgr io;

		/*************************************************************************
		* IOError
		*************************************************************************/
		IOError::IOError()
		{
		}
	
		IOError::IOError(string Msg)
		{
			// constructor
			appendMsg(Msg);
			appendOrg(IOERROR);
		}

	    IOError::IOError(string Msg, string Org) : AppError(Msg,IOERROR)
		{
			// constructor
		    appendOrg(Org);
	    }

		/*************************************************************************
		* TokenError
		*************************************************************************/
		TokenError::TokenError()
		{
		}

		TokenError::TokenError(string Msg)
		{
			// constructor
			appendMsg(Msg);
			appendOrg(TOKENERROR);
		}

	    TokenError::TokenError(string Msg, string Org) : AppError(Msg,TOKENERROR)
		{
			// constructor
			appendOrg(Org);
		}

		/*************************************************************************
		* IOMgr
		*************************************************************************/
	    IOMgr::IOMgr() 
		{
			// default constructor
			fileName = "";
			cursor = 0;
		}

		void IOMgr::promptForFile(ifstream &file, string prompt)
		{
			// get the file name from the input mgr
			string name = userResponse(prompt);
			openFile(file, name);
		}
	
		void IOMgr::promptForFile(ofstream &file, string prompt)
		{
			string name = userResponse(prompt);
			openFile(file, name);
		}
	
		string IOMgr::userResponse(string p)
		{
			string name;
		
			for( ; ; )
			{
				cout << p;
				cin >> name;
			
				if(name.length() > 0) {
					break;
				}
			
				cout << endl << "Null file name! Please re-enter." << endl;
			}
		
			return name;
		}
	
		void IOMgr::openFile(ifstream& file, string name) throw(IOError)
		{
			fileName = name;
			openFile(file);
		}
	
		void IOMgr::openFile(ofstream& file, string name) throw(IOError)
		{
			fileName = name;
			openFile(file);
		}
	
		void IOMgr::openFile(ifstream &file) throw(IOError)
		{
			string msg = "Input";
		
			if(!fileName.length())
			{
				throw IOError(string("File name not defined!"),
							  string("IOMgr::openFile(" + msg + ")"));
			}

			file.open(fileName.c_str(), ios::in);
		
			if(file.fail())
			{
				throw IOError(string(msg + " File Not Found!"),
							  string("IOMgr:openFile(" + msg + ")"));
			}
		}

		void IOMgr::openFile(ofstream &file) throw(IOError)
		{
			string msg = "Output";
		
			if(!fileName.length())
			{
				throw IOError(string("File name not defined!"),
							  string("IOMgr::openFile(" + msg + ")"));
			}

			file.open(fileName.c_str(), ios::out);
		
			if(file.fail())
			{
				throw IOError(string(msg + " File Not Found!"),
							  string("IOMgr:openFile(" + msg + ")"));
			}
		}

		string IOMgr::getName() const
		{
			return fileName;
		}

		void IOMgr::setCursor(ifstream &file)  throw( IOError )
		{
			if( fileName == "" ) throw IOError("InMgr object is not enabled!","Inmgr::setFilePos()");
			cursor = file.tellg();
		}

		void IOMgr::resetCursor(ifstream &file) throw( IOError )
		{
			if( fileName == "" ) throw IOError("InMgr object is not enabled!","Inmgr::resetFilePos()");
			file.seekg( cursor );
		}

		void IOMgr::close(ifstream &file) throw( IOError )
		{
			if( fileName == "" ) throw IOError("InMgr object is not enabled!","Inmgr::resetFilePos()");
			file.close();
		}

		/*************************************************************************
		* Tokenizer
		*************************************************************************/
		Tokenizer::Tokenizer() throw (IOError)
		{
			// constructor
			IOMgr FinMgr;
			delims = DELIMS;
			discard = "";

			try
			{
				// get the file name from the input manager
				FinMgr.promptForFile(fin, "Enter input file name: ");
			}
			catch(IOError& e)
			{
				e.appendOrg(string(":Tokenizer()"));
				throw;
			}
		}

		bool Tokenizer::more()
		{
			// gives false if EOF and putback buffer is empty
			return !fin.eof() || backbuff.length();
		} 

		char Tokenizer::nextChar()
		{
			// return the next character
			// if there is on in the backbuffer, use it first
			char sym = 0;

			if(backbuff.length())
			{
				sym = backbuff[0];
				backbuff = backbuff.substr(1, backbuff.length() - 1);
				return sym;
			}

			if(fin.good() && !sym)
			{
				fin.get(sym);
			}

			return sym;
		}

		bool Tokenizer::isDelim(char x)
		{
			for(int i = 0; i < delims.length(); i++)
			{
				if(x == delims[i])
				{
					return true;
				}
			}
	
			return false;
		}

		string Tokenizer::scan()
		{
			// delivers next token
			string token = "";
			char sym;

			if(fin.eof())
			{
				return token;
			}

			discard = "";
			sym = nextChar();
			
			while(!fin.eof() && isDelim(sym))
			{
				// read in delimiters until first non delimiter
				discard = discard + sym;
				sym = nextChar();
			}

			if(fin.eof())
			{
				return token;
			}

			token = token + sym;
			sym = nextChar();

			while(!fin.eof() && !isDelim(sym))
			{
				// read in all non delimiters until the first delimiter
				token = token + sym;
				sym = nextChar();
			}
		
			if(!fin.eof())
			{
				// put the delimiter back since its part of the next token sequence
				fin.putback(sym);
			}

			return token;
		}

		void Tokenizer::setDelims(string symbols) throw(TokenError)
		{
			if(!symbols.length())
			{
				throw IOError(string("Null delimiter string"),
							  string("Tokenizer.SetDelims"));
			}
		
			delims = symbols;
		}

		string Tokenizer::getDelims()
		{
			return delims;
		}

		string Tokenizer::getDiscard()
		{
			return discard;
		}

		void Tokenizer::reset()
		{
			delims = DELIMS;
		}

		void Tokenizer::putBack(string token)
		{
			backbuff = token + backbuff;
		}

	}
