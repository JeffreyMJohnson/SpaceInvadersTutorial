#include "MainMenuState.h"


extern const int screenWidth;
extern const int screenHeight;

extern const char* invadersFont;

extern const char* insertCoinsText;
extern const char* creditText;

MainMenuState::MainMenuState()
{

}


MainMenuState::~MainMenuState()
{

}

void MainMenuState::Initialize()
{
	arcadeMarquee = CreateSprite("./images/Space-Invaders-Marquee.png", screenWidth, screenHeight, false);
	MoveSprite(arcadeMarquee, 0, screenHeight);
}

void MainMenuState::Update(float a_timeStep, StateMachine* a_SMPointer)
{
	//257 code for enter key
	if (IsKeyDown(257))
	{
		a_SMPointer->PushState(new GameState());
	}
	else if (IsKeyDown('Q'))
	{
		//change state to end;
	}
}

void MainMenuState::Draw()
{
	SetFont(invadersFont);
	DrawSprite(arcadeMarquee);
	DrawString(insertCoinsText, screenWidth * 0.37f, screenHeight * 0.5f);
	DrawString(creditText, screenWidth * 0.25f, screenHeight * 0.4f);
}

void MainMenuState::Destroy()
{
	DestroySprite(arcadeMarquee);
}
