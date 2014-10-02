#pragma once

#ifndef _BASE_STATE_H_
class StateMachine;

class BaseState
{
public:
	BaseState() {};
	~BaseState() {};

	virtual void Initialize() = 0;
	virtual void Update(float a_timeStep, StateMachine* a_SMPointer) = 0;
	virtual void Draw() = 0;
	virtual void Destroy() = 0;
};
#endif // !_BASE_STATE_H_


