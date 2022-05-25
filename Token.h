#pragma once
#include <string>
#include <iostream>

class Token {
public:
	enum class Kind {
		op,
		var,
		r_bracket,
		l_bracket,
		num,
		new_line,
		cond,
		cycle,
		cond_cycle,
		func,
		end,
		l_figure_bracket,
		r_figure_bracket,
		l_square_bracket,
		r_square_bracket
	};

	Token(Kind type, int value, std::string name);
	Token(Kind type, std::string name);
	std::string Get_string();
	Token::Kind get_Kind();
	int get_value();
	std::string get_name();
private:
	Kind type;
	int value;
	std::string name;
};
