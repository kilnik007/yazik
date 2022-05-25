#pragma once
#include <string>
#include "RootObject.h"


class Formula : public RootObject
{
public:
	Formula(std::string name, int operationPriority);
	Formula(int value);
private:

};
