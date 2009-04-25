#ifndef _APPERROR
#define _APPERROR

#include <string>
using namespace std;

	class AppError {

		protected:
			static const string NOERROR;
			string msg;
			string origin;

		public:
			AppError();
			AppError(string why, string where); 
			string getMsg()    const {return msg;}
			string getOrigin() const {return origin;}
			void appendMsg(string str);
			void appendOrg(string str);
	};
	
#endif