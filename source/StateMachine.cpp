#include "StateMachine.h"


StateMachine::StateMachine()
{
}


StateMachine::~StateMachine()
{
}


void StateMachine::PushState(BaseState* a_gameState)
{
	stateStack.push_back(a_gameState);
	a_gameState->Initialize();
}

BaseState* StateMachine::PopState()
{
	BaseState* lastState = stateStack.back();
	stateStack.pop_back();
	lastState->Destroy();
	return lastState;
}

BaseState* StateMachine::SwitchState(BaseState* a_gameState)
{
	BaseState* lastState = stateStack.back();
	lastState->Destroy();
	
	stateStack.pop_back();
	stateStack.push_back(a_gameState);
	a_gameState->Initialize();

	return lastState;
}

void StateMachine::Update(float a_timeStep)
{
	stateStack.back()->Update(a_timeStep, this);
}

void StateMachine::Draw()
{
	stateStack.back()->Draw();
}
