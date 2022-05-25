#pragma once
#include "RootObject.h"
#include "Parser.h"

class interpreter
{
public:
	interpreter(Parser link_on_tree);

	void ExecuteFunction(RootObject* parent, int StartPosition);
	bool ExecuteBoolLine(RootObject* parent);
	int ExecuteValueLine(RootObject* parent);
	void ExecuteIf(RootObject* parent);
	void ExecuteWhile(RootObject* parent);

	Parser link_on_tree;
private:

};

