#pragma once
#include <memory>
#include <stack>
#include "IState.h"

class StateMachine
{
public:
	StateMachine() = default;

	void AddState(std::unique_ptr<IState> newState, bool isReplacing = true);
	void RemoveState();
	void ProcessStateChanges();

	std::unique_ptr<IState>& GetActiveState();

private:
	std::stack<std::unique_ptr<IState>> states;
	std::unique_ptr<IState> newState;
	bool isRemoving;
	bool isAdding;
	bool isReplacing;
};

