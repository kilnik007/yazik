#include "interpreter.h"

interpreter::interpreter(Parser link_on_tree)
{
	this->link_on_tree = link_on_tree;
}

void interpreter::ExecuteFunction(RootObject* parent, int StartPosition) {
	for (int i = StartPosition; i < parent->sonsMass.size(); i++) {
		if (parent->sonsMass.at(i)->getName() == "new_line") {
			ExecuteValueLine(parent->sonsMass.at(i)->sonsMass.at(0));
		}

		if (parent->sonsMass.at(i)->getName() == "WAHREND") {
			ExecuteWhile(parent->sonsMass.at(i));
		}

		if (parent->sonsMass.at(i)->getName() == "WENN") {
			ExecuteIf(parent->sonsMass.at(i));
		}
	}
}

bool interpreter::ExecuteBoolLine(RootObject* parent) {
	int firstOperand = ExecuteValueLine(parent->sonsMass.at(1));
	int secondOperand = ExecuteValueLine(parent->sonsMass.at(0));

	if (parent->getName() == "greater") {
		if (firstOperand > secondOperand) {
			return true;
		} else {
			return false;
		}
	}

	if (parent->getName() == "GLEICH") {
		if (firstOperand == secondOperand) {
			return true;
		} else {
			return false;
		}
	}

	if (parent->getName() == "lower") {
		if (firstOperand < secondOperand) {
			return true;
		} else {
			return false;
		}
	}

	return false;
}

int interpreter::ExecuteValueLine(RootObject* parent) {
	if (parent->getName() == "GLEICH" || parent->getName() == "PLUS" || parent->getName() == "MINUS" ||
		parent->getName() == "MULTIPLIZIEREN" || parent->getName() == "TEILEN") {
		if (parent->getName() == "GLEICH") {
			if (parent->sonsMass.at(0)->getName() == "PLUS") {
				parent->sonsMass.at(1)->setValue(ExecuteValueLine(parent->sonsMass.at(0)));
			} else if (parent->sonsMass.at(0)->getName() == "MULTIPLIZIEREN") {
				parent->sonsMass.at(1)->setValue(ExecuteValueLine(parent->sonsMass.at(0)));
			} else if (parent->sonsMass.at(0)->getName() == "MINUS") {
				parent->sonsMass.at(1)->setValue(ExecuteValueLine(parent->sonsMass.at(0)));
			} else {
				parent->sonsMass.at(1)->setValue(parent->sonsMass.at(0)->getValue());
			}
			
			return parent->sonsMass.at(1)->getValue();
		}

		if (parent->getName() == "PLUS") {
			return ExecuteValueLine(parent->sonsMass.at(0)) + ExecuteValueLine(parent->sonsMass.at(1));
		}

		if (parent->getName() == "MINUS") {
			int t = ExecuteValueLine(parent->sonsMass.at(1)) - ExecuteValueLine(parent->sonsMass.at(0));
			return t;
		}

		if (parent->getName() == "MULTIPLIZIEREN") {
			return ExecuteValueLine(parent->sonsMass.at(0)) * ExecuteValueLine(parent->sonsMass.at(1));
		}

		if (parent->getName() == "TEILEN") {
			return ExecuteValueLine(parent->sonsMass.at(1)) + ExecuteValueLine(parent->sonsMass.at(0));
		}
	} else {
		return parent->getValue();
	}

	return 0;
}

void interpreter::ExecuteIf(RootObject* parent) {
	if (ExecuteBoolLine(parent->sonsMass.at(0)->sonsMass.at(0)) == true) {
		ExecuteFunction(parent, 1);
	}
}

void interpreter::ExecuteWhile(RootObject* parent) {
	while (ExecuteBoolLine(parent->sonsMass.at(0)->sonsMass.at(0)) == true) {
		ExecuteFunction(parent, 1);
		ExecuteBoolLine(parent->sonsMass.at(0)->sonsMass.at(0));
	}
}