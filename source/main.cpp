#include "AIE.h"
#include <cmath>
#include <time.h>
#include <assert.h>
#include <crtdbg.h>
#include <iostream>
#include "StateMachine.h"
#include "MainMenuState.h"

using namespace std;

/*
The Original resolution of Space Invaders was 224 X 260 for comparison the Nintendo DS
has a resolution.
*/
//magic numbers
extern const int screenWidth = 672;
extern const int screenHeight = 780;

extern const float lineYPos = 45.0f;

//magic strings
extern const char* player1ScoreText = "SCORE < 1 >";
extern const char* player2ScoreText = "SCORE < 2 >";
extern const char* scoreText = "SCORE";
extern const char* creditText = "CREDIT";
extern const char* highScoreText = "HIGH SCORE";
extern const char* insertCoinsText = "INSERT COINS";

extern char* player1Score = "00000";
extern char* player2Score = "00000";
extern char* highScore = "00000";
extern char* credit = "99";
extern char* playerLives = "3";

extern string scoreAsString = "00000";

extern const char* invadersFont = "./fonts/invaders.fnt";


int main(int argcx, char* argv[])
{
	//flag to quit game gracefully
	bool quitGame = false;



	//init framework and window
	Initialise(screenWidth, screenHeight, false, "Space Invaders Clone");
	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));
	AddFont(invadersFont);

	StateMachine state;
	state.PushState(new MainMenuState());
	
	//game loop
	do
	{
		ClearScreen();

		float delta = GetDeltaTime();

		state.Update(delta);
		state.Draw();

	} while (!FrameworkUpdate() && !quitGame);

	Shutdown();
	//system("pause");
	return 0;
}