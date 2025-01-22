#pragma once
#include <string>
using std::string;
class StateNode
{
public:
	StateNode() = default;
	~StateNode() = default;


	virtual void onEnter() {};
	virtual void onUpdate() {};
	virtual void onExit() {};

	string name = "none";
protected:
	
};
