#include "Formula.h"

Formula::Formula(std::string name, int operationPriority) {
	this->name = name;
	this->operationPriority = operationPriority;
}

Formula::Formula(int value) {
	this->value = value;
}
