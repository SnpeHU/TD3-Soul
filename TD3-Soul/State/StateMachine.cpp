#include "StateMachine.h"

void StateMachine::onUpdate()
{
	if (!currentState)
	{
		return;
	}
	if (needInit)
	{
		currentState->onEnter();
		needInit = false;
	}
	currentState->onUpdate();
}

void StateMachine::SetEntry(const std::string& id)
{
	currentState = statePool[id];
}

void StateMachine::SwitchTo(const std::string& id)
{
	if (currentState)
	{
		currentState->onExit();
	}
	currentState = statePool[id];
	if (currentState)
	{
		currentState->onEnter();
	}
}

void StateMachine::RegisterState(const std::string& id, StateNode* state)
{
	statePool[id] = state;
}

