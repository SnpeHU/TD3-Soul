#pragma once
#include <string>
#define deltaTime (1.0f/60.0f)
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
	//Object* owner = nullptr;
};
