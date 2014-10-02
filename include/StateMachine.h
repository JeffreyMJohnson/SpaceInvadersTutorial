#pragma once

#ifndef _STATE_MACHINE_H_
#include "BaseState.h"
#include <list>

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	void PushState(BaseState* a_gameState);
	BaseState* PopState();
	BaseState* SwitchState(BaseState* a_gameState);

	void Update(float a_timeStep);
	void Draw();

private:
	std::list<BaseState*> stateStack;
};
#endif // !_STATE_MACHINE_H_


