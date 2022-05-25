#pragma once
#include <string>
#include "RootObject.h"


class Variable : public RootObject
{
public:
	Variable(int value, std::string name);
private:
};