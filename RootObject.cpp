#include "RootObject.h"

RootObject::RootObject() {}

RootObject::~RootObject() {

}

RootObject::RootObject(int value, std::string name) {
    this->value = value;
    this->name = name;
}


int RootObject::GetOperationPriority() {
    return this->operationPriority;
}

RootObject::RootObject(std::string name) {
    this->name = name;
}

RootObject::RootObject(std::string name, int operationPriority) {
    this->name = name;
    this->operationPriority = operationPriority;
}


RootObject* RootObject::get_sus() {
    return sonsMass[0]; 
}

void RootObject::AddSon(RootObject* sonPointer) {
    sonsMass.push_back(sonPointer);
}

void RootObject::AddParent(RootObject* Parent) {
    this->parentObject = Parent;
}

std::string RootObject::getString() {
    return this->name + std::to_string(this->value);
}

RootObject* RootObject::getParent() {
    return this->parentObject;
}

RootObject* RootObject::getType() {
    return nullptr;
}

int RootObject::getValue() {
    return this->value;
}

std::string RootObject::getName() {
    return this->name;
}

void RootObject::setName(std::string name) {
    this->name = name;
}

void RootObject::setValue(int value) {
    this->value = value;
}