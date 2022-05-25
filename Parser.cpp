#include "Parser.h"
#include <typeinfo>


Parser::Parser() {
	this->root.setName("root");
}

void Parser::CreateWood(std::vector<Token>::iterator programStart) {
	try {
		SimpleBranch(&this->root, programStart, Token::Kind::func, Token::Kind::end, true);
	} catch (LexerException& ex) {
		std::cout << ex.whatPars() << std::endl;
		return;
	}
}

std::vector<Token>::iterator Parser::SimpleBranch(RootObject* parentObject, std::vector<Token>::iterator functionStart,
	Token::Kind childType, Token::Kind endOfSearch, bool typeNextIteration) {
	std::vector<Token>::iterator peekNextToken = functionStart;

	while (peekNextToken->get_Kind() != endOfSearch) {
		if (functionStart->get_Kind() == childType) {
			if (childType == Token::Kind::func) {
				std::vector<Token>::iterator nextToken = functionStart + 1;

				if (nextToken->get_Kind() != Token::Kind::new_line) {
					throw LexerException("semantic error", this->currentLine);
				}

				Function* function = new Function(functionStart->get_name());
				parentObject->AddSon(function);
				function->AddParent(parentObject);

 				functionStart = functionStart + 2;
				this->currentLine += 1;

				try {
					functionStart = SimpleBranch(function, functionStart, Token::Kind::new_line,
						Token::Kind::r_figure_bracket, true);
				} catch (LexerException& ex) {
					std::cout << ex.whatPars() << std::endl;
					return nextToken;
				}
			}

			if (childType == Token::Kind::new_line) {
				std::vector<Token>::iterator nextToken = functionStart + 1;
				if (nextToken->get_Kind() != Token::Kind::var && nextToken->get_Kind() != Token::Kind::cond &&
					nextToken->get_Kind() != Token::Kind::cond_cycle && nextToken->get_Kind() != Token::Kind::cycle) {
					throw LexerException("semantic error", this->currentLine);
				}

				if (nextToken->get_Kind() == Token::Kind::var) {
					Line* line = new Line(functionStart->get_name());
					parentObject->AddSon(line);
					line->AddParent(parentObject);
					this->currentLine += 1;

					try {
						functionStart = BinaryBranch(line, functionStart, Token::Kind::op,
							Token::Kind::op);
					} catch (LexerException& ex) {
						std::cout << ex.whatPars() << std::endl;
						return nextToken;
					}
				}

				if (nextToken->get_Kind() == Token::Kind::cond) {
					Condition* condition = new Condition(nextToken->get_name());
					parentObject->AddSon(condition);
					condition->AddParent(parentObject);
					this->currentLine += 1;

					try {
						functionStart = ConditionalBranch(condition, functionStart, Token::Kind::new_line,
							Token::Kind::r_bracket, false);
					} catch (LexerException& ex) {
						std::cout << ex.whatPars() << std::endl;
						return nextToken;
					}
				}

				if (nextToken->get_Kind() == Token::Kind::cond_cycle) {
					While* whilee = new While(nextToken->get_name());
					parentObject->AddSon(whilee);
					whilee->AddParent(parentObject);
					this->currentLine += 1;

					try {
						functionStart = ConditionalBranch(whilee, functionStart, Token::Kind::new_line,
							Token::Kind::r_bracket, false);
					} catch (LexerException& ex) {
						std::cout << ex.whatPars() << std::endl;
						return nextToken;
					}
				}
			}
		}

		functionStart = functionStart + 1;
		peekNextToken = functionStart + 1;
	}

	return functionStart;
}

std::vector<Token>::iterator Parser::BinaryBranch(RootObject* parentObject, std::vector<Token>::iterator lineStart,
	Token::Kind childType, Token::Kind endOfSearch) {
	std::vector<Token>::iterator nextToken = lineStart + 1;
	std::vector<Token>::iterator doubleNext = nextToken + 1;

	if (childType == Token::Kind::op) {
		if (doubleNext->get_Kind() != Token::Kind::op) {
			throw LexerException("semantic error", this->currentLine);
		}

		try {
			BinaryBranch(parentObject, doubleNext, Token::Kind::var,
				Token::Kind::op);
		} catch (LexerException& ex) {
			std::cout << ex.whatPars() << std::endl;
			return doubleNext;
		}
	}

	if (childType == Token::Kind::var) {
		std::vector<Token>::iterator previousToken = lineStart - 1;
		doubleNext = FormulaTree(parentObject, previousToken) + 2;

	}

	return doubleNext;
}

std::vector<Token>::iterator Parser::ConditionalBranch(RootObject* parentObject, std::vector<Token>::iterator functionStart,
	Token::Kind childType, Token::Kind endOfSearch, bool typeNextIteration) {
	std::vector<Token>::iterator nextToken = functionStart + 1;
	std::vector<Token>::iterator doubleNext = nextToken + 1;

	if (doubleNext->get_Kind() != Token::Kind::var) {
		throw LexerException("semantic error", this->currentLine);
	}

	Line* firstLine = new Line(functionStart->get_name());
	parentObject->AddSon(firstLine);
	firstLine->AddParent(parentObject);
	
	try {
		BinaryBranch(firstLine, nextToken, Token::Kind::op,
			Token::Kind::end);
	} catch (LexerException& ex) {
		std::cout << ex.whatPars() << std::endl;
		return nextToken;
	}

	while (nextToken->get_Kind() != Token::Kind::new_line) {
		nextToken += 1;
	}

	nextToken += 2;
	this->currentLine += 1;

	try {
		nextToken = SimpleBranch(parentObject, nextToken, childType, endOfSearch, typeNextIteration);
	} catch (LexerException& ex) {
		std::cout << ex.whatPars() << std::endl;
		return nextToken;
	}

	this->currentLine += 1;
	return nextToken;
}

std::vector<Token>::iterator Parser::FormulaTree(RootObject* parentObject, std::vector<Token>::iterator lineStart) {
	std::vector<RootObject*> OperandStack;
	std::vector<RootObject*> OperatorStack;

	while (lineStart->get_Kind() != Token::Kind::new_line) {
		if (lineStart->get_Kind() == Token::Kind::var || lineStart->get_Kind() == Token::Kind::num) {
			bool alredyExists = false;

			for (int i = 0; i < this->root.variableMass.size(); i++) {
				if (this->root.variableMass.at(i)->getName() == lineStart->get_name() && this->root.variableMass.at(i)->getName() != "") {
					alredyExists = true;
					OperandStack.push_back(root.variableMass.at(i));
					break;
				}
			}

			if (alredyExists == false) {
				Variable* variable = new Variable(lineStart->get_value(), lineStart->get_name());
				OperandStack.push_back(variable);
				this->root.variableMass.push_back(variable);
			}

		} else if (lineStart->get_Kind() == Token::Kind::op) {
				int operationPriority = 0;

				if (lineStart->get_name() == "GLEICH" || lineStart->get_name() == "lower" || lineStart->get_name() == "greater") {
					operationPriority = 0;
				}

				if (lineStart->get_name() == "PLUS" || lineStart->get_name() == "MINUS") {
					operationPriority = 1;
				}

				if (lineStart->get_name() == "MULTIPLIZIEREN" || lineStart->get_name() == "TEILEN") {
					operationPriority = 2;
				}

				Formula* formula = new Formula(lineStart->get_name(), operationPriority);

				if (OperatorStack.size() != 0) {
					while (OperatorStack.back()->GetOperationPriority() > formula->GetOperationPriority() &&
						OperatorStack.back()->GetOperationPriority() >= 0) {
						OperandStack.back()->AddParent(OperatorStack.back());
						OperatorStack.back()->AddSon(OperandStack.back());
						OperandStack.pop_back();

						OperandStack.back()->AddParent(OperatorStack.back());
						OperatorStack.back()->AddSon(OperandStack.back());
						OperandStack.pop_back();

						OperandStack.push_back(OperatorStack.back());
						OperatorStack.pop_back();

						if (OperatorStack.size() == 0) {
							break;
						}
					}

					OperatorStack.push_back(formula);
				} else {
					OperatorStack.push_back(formula);
				}
			} else if (lineStart->get_Kind() == Token::Kind::l_square_bracket ||
					lineStart->get_Kind() == Token::Kind::r_square_bracket) {
					if (lineStart->get_Kind() == Token::Kind::l_square_bracket) {
						Formula* formula = new Formula(lineStart->get_name(), -1);
						OperatorStack.push_back(formula);
					} else {
						while (OperatorStack.back()->GetOperationPriority() != -1) {
							OperandStack.back()->AddParent(OperatorStack.back());
							OperatorStack.back()->AddSon(OperandStack.back());
							OperandStack.pop_back();

							OperandStack.back()->AddParent(OperatorStack.back());
							OperatorStack.back()->AddSon(OperandStack.back());
							OperandStack.pop_back();

							OperandStack.push_back(OperatorStack.back());
							OperatorStack.pop_back();
						}

						OperatorStack.pop_back();
					}
				} else {
					throw LexerException("semantic error", this->currentLine);
				}

		lineStart += 1;
	}

	if (OperandStack.size() != OperatorStack.size() + 1) {
		throw LexerException("semantic error", this->currentLine);
	}

	parentObject->AddSon(OperatorStack[0]);
	OperatorStack[0]->AddParent(parentObject);

	while (OperatorStack.size() != 0) {
		OperandStack.back()->AddParent(OperatorStack.back());
		OperatorStack.back()->AddSon(OperandStack.back());
		OperandStack.pop_back();

		OperandStack.back()->AddParent(OperatorStack.back());
		OperatorStack.back()->AddSon(OperandStack.back());
		OperandStack.pop_back();

		OperandStack.push_back(OperatorStack.back());
		OperatorStack.pop_back();
	}

	return lineStart;
}

void Parser::DrawTree(RootObject root, std::string ot)
{
	std::string indent = "   ";
	RootObject* parent = root.getParent();

	while (parent != nullptr) {
		parent = parent->getParent();
		std::cout << indent;
	}

	if (root.getName() != "") {
		std::cout << root.getName();
	} else {
		std::cout << root.getValue();
	}

	for (int i = 0; i < root.sonsMass.size(); i++) {
		std::cout << std::endl;
		DrawTree(*root.sonsMass.at(i), ot);
	}
}

RootObject Parser::GetRoot()
{
	return this->root;
}


