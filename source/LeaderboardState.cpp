#include "include\LeaderboardState.h"

extern const int screenWidth;
extern const int screenHeight;
extern const char* highScoreText;
extern const char* invadersFont;

LeaderboardState::LeaderboardState()
{
}

LeaderboardState::~LeaderboardState()
{
}

void LeaderboardState::Initialize()
{
	scores.LoadScores();
	scores.SortScores();
}

void LeaderboardState::Update(float a_timeStep, StateMachine* a_SMP)
{
	//256 = esc key
	if (IsKeyDown(256))
	{
		BaseState* lastState = a_SMP->PopState();
		delete lastState;
		return;
	}
}

void LeaderboardState::Draw()
{
	char score[20];
	int y = screenHeight - 100;
	int count = 0;

	SetFont(invadersFont);
	DrawString(highScoreText, screenWidth *0.425f, screenHeight - 2);

	const std::list<int> scoreList = scores.GetScores();
	for (std::list<int>::const_iterator it = scoreList.begin(); it != scoreList.end(); it++)
	{
		sprintf(score, "%05d", *it);
		//(screenWidth >> 1) - this is bit-shifting and equivalent to (screenWidth *0.5f) and the person who chose this 
		//should be damn ashamed of themselves...
		DrawString(score, screenWidth >> 1, y);
		y -= 40;
		count++;
		if (count >= 5)
			break;
	}
}

void LeaderboardState::Destroy()
{
	scores.SaveScores();
}

void LeaderboardState::SetPlayersScore(int a_score)
{
	scores.AddScore(a_score);
}