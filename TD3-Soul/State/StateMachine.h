#pragma once
#include "StateNode.h"
#include <string>
#include <unordered_map>

class StateMachine
{
public:
	StateMachine() = default;
	~StateMachine() = default;

	void onUpdate();
	void SetEntry(const std::string& id);
	void SwitchTo(const std::string& id);
	void RegisterState(const std::string& id, StateNode* state);

	string GetCurrentState() { return currentState->name; }



private:
	bool needInit = true;
	StateNode* currentState = nullptr;
	std::unordered_map<std::string, StateNode*> statePool;

};
