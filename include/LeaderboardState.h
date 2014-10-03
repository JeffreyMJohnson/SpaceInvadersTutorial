#pragma once

#ifndef _LEADERBOARD_STATE_H_
#include "BaseState.h"
#include "Highscores.h"
#include "AIE.h"
#include "StateMachine.h"

class LeaderboardState : public BaseState
{
public:
	LeaderboardState();
	~LeaderboardState();

	void Initialize();
	void Update(float a_timeStep, StateMachine* a_SMP);
	void Draw();
	void Destroy();

	void SetPlayersScore(int a_score);

private:
	Highscores scores;
};

#endif //_LEADERBOARD_STATE_H_