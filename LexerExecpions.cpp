#include "LexerExecpions.h"


LexerException::LexerException(std::string error)
{
	this->m_error = error;
}

LexerException::LexerException(std::string error, int line_error)
{
	this->line_error = line_error;
	this->m_error = error;
}

std::string LexerException::what()
{
	return this->m_error.c_str();
}

std::string LexerException::whatPars()
{
	return this->m_error + "\nline of error {" + std::to_string(this->line_error) + "}";
}