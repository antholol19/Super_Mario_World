#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>

class Component
{
public:
	virtual ~Component(){}
	virtual void update(float deltaTime) = 0;
	virtual void setName(std::string name) = 0;
};

#endif // !COMPONENT_H

