#pragma once
#include <regex>
#include <string>
#include <iostream>
#include <vector>
#include "Token.h"
#include "LexerExecpions.h"


class Lexer
{
public:
	std::string Next_token(std::string text);
	void Lexer_analis();
	void Get_Token_mass();
	void Pars_text(std::string text);
	std::vector<Token>::iterator get_Begin();
private:
	std::vector<Token> Token_mass;
	std::vector<std::string> lexem_mass;
};

