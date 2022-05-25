#pragma once
#include <vector>
#include <string>

class RootObject
{
public:
	RootObject();
	~RootObject();
	RootObject(int value, std::string name);
	RootObject(std::string name);
	RootObject(std::string name, int operationPriority);
	RootObject* get_sus();
	void AddSon(RootObject* sonPointer);
	void AddParent(RootObject* Parent);
	int GetOperationPriority();

	std::string getString();
	RootObject* getParent();
	RootObject* getType();
	int getValue();
	std::string getName();
	void setName(std::string name);
	void setValue(int value);

	std::vector<RootObject*> sonsMass;
	std::vector<RootObject*> variableMass;
protected:
	std::string name;
	int value;
	RootObject* parentObject;
	int operationPriority;
};
