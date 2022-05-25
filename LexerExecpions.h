#pragma once
#include <iostream>
#include <string>
#include <exception>


class LexerException : public std::exception
{
public:
	LexerException(std::string error);
	LexerException(std::string error, int line_error);
	std::string what();
	std::string whatPars();
private:
	std::string m_error;
	int line_error;
};
