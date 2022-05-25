#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "interpreter.h"

#include "RootObject.h"


int main() {
	std::string character_stream = "FUNKTION \
                                  \n{ \
                                  \n   v GLEICH 1  \
		                          \n   a GLEICH 10 \
		                          \n   b GLEICH 45 \
                                  \n   WENN v PLUS 10 > 0 \
                                  \n   ( \
                                  \n      a GLEICH a PLUS 5 \
                                  \n      b GLEICH 10 MULTIPLIZIEREN [ 2 PLUS 4 ] PLUS 34 \
                                  \n   ) \
                                  \n   WAHREND a < b \
                                  \n   ( \
                                  \n      a GLEICH a PLUS 5 \
                                  \n      b GLEICH b MINUS 2 \
                                  \n   ) \
                                  \n}";

	std::string prog = "FUNKTION \
						\n{ \
						\n	a GLEICH 10 \
						\n  b GLEICH 45 \
						\n  a GLEICH a PLUS b MULTIPLIZIEREN 10 \
						\n }";

	std::cout << character_stream << std::endl;
	Lexer My_lxer;
	My_lxer.Pars_text(character_stream);
	My_lxer.Lexer_analis();
	My_lxer.Get_Token_mass();
	
	Parser pr;
	pr.CreateWood(My_lxer.get_Begin());
	RootObject rt = pr.GetRoot();
	pr.DrawTree(rt, " ");

	std::cout << std::endl;

	for (int i = 0; i < pr.GetRoot().variableMass.size(); i++) {
		std::cout << pr.GetRoot().variableMass.at(i)->getString() << "  ";
	}

	std::cout << pr.GetRoot().sonsMass.at(0)->getString() << std::endl;

	interpreter Interpreter(pr);

	Interpreter.ExecuteFunction(pr.GetRoot().sonsMass.at(0), 0);

	std::cout << std::endl;

	for (int i = 0; i < pr.GetRoot().variableMass.size(); i++) {
		std::cout << pr.GetRoot().variableMass.at(i)->getString() << "  ";
	}
	
	return 0;
}