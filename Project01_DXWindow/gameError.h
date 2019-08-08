#pragma once
#ifndef _GAMERROR_H
#define _GAMEERROR_H
#define WIN32_LEAN_AND_MEAN
class GameError;
#include <string>
#include <exception>
namespace gameErrorNS
{
	const int FATAL_ERROR = -1;
	const int WARNING = 1;

}

class GameError : public std::exception
{
private:
	int errorCode;
	std::string message;
public:
	GameError() :errorCode(gameErrorNS::FATAL_ERROR), message("Undefinef Error in Game") {}
	GameError(const GameError& e) :std::exception(e), errorCode(e.errorCode), message(e.message) {}
	GameError(int code, const std::string &s) :errorCode(code), message(s) {}
	GameError& operator=(const GameError& rhs) 
	{
	std::exception::operator=(rhs);
		this->errorCode = rhs.errorCode;
		this->message = rhs.message;
	}
	virtual ~GameError() {};
	virtual const char* what() const { return this->getMessage(); }
	const char* getMessage() const { return message.c_str(); }
	int getErrorCode() const { return errorCode; }


};

#endif