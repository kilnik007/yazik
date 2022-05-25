#pragma once
#include <vector>

#include "Lexer.h"
#include "LexerExecpions.h"
#include "Token.h"

#include "RootObject.h"
#include "Function.h"
#include "While.h"
#include "Condition.h"
#include "Line.h"
#include "Formula.h"
#include "Variable.h"


class Parser {
public:
	Parser();
	void CreateWood(std::vector<Token>::iterator programStart);

	std::vector<Token>::iterator SimpleBranch(RootObject* parentObject, std::vector<Token>::iterator functionStart,
		Token::Kind childType, Token::Kind endOfSearch, bool typeNextIteration);

	std::vector<Token>::iterator BinaryBranch(RootObject* parentObject, std::vector<Token>::iterator lineStart,
		Token::Kind childType, Token::Kind endOfSearch);

	std::vector<Token>::iterator ConditionalBranch(RootObject* parentObject, std::vector<Token>::iterator functionStart,
		Token::Kind childType, Token::Kind endOfSearch, bool typeNextIteration);


	std::vector<Token>::iterator FormulaTree(RootObject* parentObject, std::vector<Token>::iterator functionStart);
	void DrawTree(RootObject root, std::string ot);
	RootObject GetRoot();
private:
	RootObject root;
	int currentLine = 1;
};