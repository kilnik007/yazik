#include <regex>
#include "Lexer.h"


void Lexer::Lexer_analis() {
	std::string result;
	std::smatch narrow;
	std::regex regular_s("\s");

	for (int it = 0; it < lexem_mass.size(); it++) {
		try {
			result = Next_token(lexem_mass.at(it));

			if (result == "GLEICH") {
				Token_mass.push_back(Token(Token::Kind::op, "GLEICH"));
			}
			if (result == "PLUS") {
				Token_mass.push_back(Token(Token::Kind::op, "PLUS"));
			}
			if (result == "MINUS") {
				Token_mass.push_back(Token(Token::Kind::op, "MINUS"));
			}
			if (result == "(") {
				Token_mass.push_back(Token(Token::Kind::l_bracket, ""));
			}
			if (result == ")") {
				Token_mass.push_back(Token(Token::Kind::r_bracket, ""));
			}
			if ('0' <= result.at(0) and result.at(0) <= '9') {
				Token_mass.push_back(Token(Token::Kind::num, stoi(result), ""));
			}
			if ('a' <= result.at(0) and result.at(0) <= 'z') {
				Token_mass.push_back(Token(Token::Kind::var, 0, result));
			}
			if (result == "\n") { 
				Token_mass.push_back(Token(Token::Kind::new_line, "new_line"));
			}
			if (result == "MULTIPLIZIEREN") {
				Token_mass.push_back(Token(Token::Kind::op, "MULTIPLIZIEREN"));
			}
			if (result == "TEILEN") {
				Token_mass.push_back(Token(Token::Kind::op, "TEILEN"));
			}
			if (result == "WENN") {
				Token_mass.push_back(Token(Token::Kind::cond, "WENN"));
			}
			if (result == "KREISLAUF") {
				Token_mass.push_back(Token(Token::Kind::cycle, ""));
			}
			if (result == "WAHREND") {
				Token_mass.push_back(Token(Token::Kind::cond_cycle, "WAHREND"));
			}
			if (result == "FUNKTION") {
				Token_mass.push_back(Token(Token::Kind::func, result));
			}
			if (result == "<") {
				Token_mass.push_back(Token(Token::Kind::op, "lower"));
			}
			if (result == ">") {
				Token_mass.push_back(Token(Token::Kind::op, "greater"));
			}
			if (result == "{") {
				Token_mass.push_back(Token(Token::Kind::l_figure_bracket, ""));
			}
			if (result == "}") {
				Token_mass.push_back(Token(Token::Kind::r_figure_bracket, ""));
			}
			if (result == "[") {
				Token_mass.push_back(Token(Token::Kind::l_square_bracket , "["));
			}
			if (result == "]") {
				Token_mass.push_back(Token(Token::Kind::r_square_bracket, "]"));
			}
		} catch (LexerException& ex) {
			std::cout << ex.what() << std::endl;
			Token_mass.clear();
			break;
		}
	}

	Token_mass.push_back(Token(Token::Kind::end, ""));
}

std::string Lexer::Next_token(std::string text) {
	std::smatch result;
	std::smatch result_number;
	std::smatch result_variable;
	std::regex regular("\\]|\\[|\\{|\\}|<|>|FUNKTION|WAHREND|KREISLAUF|WENN|MULTIPLIZIEREN|TEILEN|\\(|\\)|PLUS|GLEICH|MINUS|[a-z]+|[0-9]+|\\n");
	std::regex regular_number("[0-9]+");
	std::regex regular_variable("[a-z]+");

	if (!std::regex_match(text, result, regular)) {
		throw LexerException("{" + text + "} error lexem");
	}

	return result.str();
}

void Lexer::Get_Token_mass() {
	for (int i = 0; i < Token_mass.size(); i++) {
		std::cout << Token_mass.at(i).Get_string() << std::endl;
	}

	std::cout << Token_mass.size() << std::endl;
}

void Lexer::Pars_text(std::string text) {
	std::string word;
	int k = 0;
	std::vector<std::string> mass_word;
	mass_word.push_back("");

	for (int i = 0; i < text.size(); i++) {
		if (text.at(i) != '\n') {
			mass_word.at(k).push_back(text.at(i));
		} else {
			k++;
			mass_word.push_back("");
		}
	}

	for (int it = 0; it < mass_word.size(); it++) {
		for (int j = 0; j < mass_word.at(it).size(); j++) {
			if (mass_word.at(it).at(j) != ' ' and mass_word.at(it).at(j) != '\t') {
				word.push_back(mass_word.at(it).at(j));
			} else if (word.size() != 0) {
				lexem_mass.push_back(word);
				word.clear();
			}

			if (word.size() != 0 and j == mass_word.at(it).size() - 1) {
				lexem_mass.push_back(word);
				word.clear();
			}
		}

		if (it != mass_word.size() - 1) {
			lexem_mass.push_back("\n");
		}
	}
}

std::vector<Token>::iterator Lexer::get_Begin() {
	return this->Token_mass.begin()++;
}
