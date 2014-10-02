#pragma once
#ifndef _MAIN_MENU_STATE_H_
#include "BaseState.h"
#include "AIE.h"
#include "StateMachine.h"
#include "GameState.h"

class MainMenuState : public BaseState
{
public:
	MainMenuState();
	~MainMenuState();

	void Initialize();
	void Update(float a_timeStep, StateMachine* a_SMPointer);
	void Draw();
	void Destroy();

private:
	unsigned int arcadeMarquee;
};
#endif // !_MAIN_MENU_STATE_H_


