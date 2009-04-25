
#include "AppError.h"

	const string AppError::NOERROR = "";

	AppError::AppError()
	{
		//default constructor
		msg = origin = NOERROR;
	}

	AppError::AppError(string why, string where)
	{
		// constructor
		msg = why;
		origin = where;
	}

	void AppError::appendMsg(string str)
	{
		msg = msg + ":" + str;
	}

	void AppError::appendOrg(string str)
	{
		origin = origin + ":" + str;
	}
