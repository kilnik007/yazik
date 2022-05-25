#include "Token.h"

Token::Token(Kind type, int value, std::string name) {
	this->type = type;
	this->value = value;
	this->name = name;
}

Token::Token(Kind type, std::string name) {
	this->type = type;
	this->name = name;
}

std::string Token::Get_string() {
	std::string type;
	bool isNumber = false;

	switch (this->type) {
	case Kind::l_bracket:
		type = "l_bracket";
		break;
	case Kind::r_bracket:
		type = "r_bracket";
		break;
	case Kind::var:
		type = "var";
		break;
	case Kind::num:
		type = "num";
		isNumber = true;
		break;
	case Kind::new_line:
		type = "new_line";
		break;
	case Kind::cond_cycle:
		type = "WAHREND";
		break;
	case Kind::cycle:
		type = "cycle";
		break;
	case Kind::cond:
		type = "WENN";
		break;
	case Kind::func:
		type = "func";
		break;
	case Kind::end:
		type = "end";
		break;
	case Kind::l_figure_bracket:
		type = "l_figure_bracket";
		break;
	case Kind::r_figure_bracket:
		type = "r_figure_bracket";
		break;
	case Kind::op:
		type = "op";
		break;
	case Kind::l_square_bracket:
		type = "l_square_bracket";
		break;
	case Kind::r_square_bracket:
		type = "r_square_bracket";
		break;
	default:
		break;
	}

	if (isNumber == true) {
		return "type of object {" + type + "} value of object {" + std::to_string(this->value) + "}" + " name of object {" + this->name + "}";
	}

	return "type of object {" + type + "} value of object {" + "}" + " name of object {" + this->name + "}";
}

Token::Kind Token::get_Kind() {
	return this->type;
}

int Token::get_value() {
	return this->value;
}

std::string Token::get_name() {
	return this->name;
}


