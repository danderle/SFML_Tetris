#include "StateMachine.h"

void StateMachine::AddState(std::unique_ptr<IState> _newState, bool _isReplacing)
{
	isAdding = true;
	isReplacing = _isReplacing;
	newState = std::move(_newState);
}

void StateMachine::RemoveState()
{
	isRemoving = true;
}

void StateMachine::ProcessStateChanges()
{
	if (isRemoving && !states.empty())
	{
		states.pop();
		if (!states.empty())
		{
			states.top()->Resume();
		}
		isRemoving = false;
	}
	if (isAdding)
	{
		if (!states.empty())
		{
			if (isReplacing)
			{
				states.pop();
			}
			else
			{
				states.top()->Pause();
			}
		}
		states.push(std::move(newState));
		states.top()->Init();
		isAdding = false;
	}
	
}

std::unique_ptr<IState>& StateMachine::GetActiveState()
{
	return states.top();
}


