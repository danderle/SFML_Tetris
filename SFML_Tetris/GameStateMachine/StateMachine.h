#pragma once
#include <memory>
#include <stack>
#include "State.h"

class StateMachine
{
public:
	StateMachine() = default;

	void AddState(std::unique_ptr<State> newState, bool isReplacing = true);
	void RemoveState();
	void ProcessStateChanges();

	std::unique_ptr<State>& GetActiveState();

private:
	std::stack<std::unique_ptr<State>> states;
	std::unique_ptr<State> newState;
	bool isRemoving;
	bool isAdding;
	bool isReplacing;
};

