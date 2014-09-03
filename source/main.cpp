#include "AIE.h"
#include "stdlib.h"
#include <iostream>

const int screenWidth = 672;
const int screenHeight = 780;
const int playerCannonWidth = 64;
const int playerCannonHeight = 32;
const float playerCannonYPos = 40.0f;
float playerCannponXPos = screenWidth *0.5f;

char* player1ScoreText = "SCORE < 1 >";
char* player2ScoreText = "SCORE < 2 >";
char* scoreText = "SCORE";
char* creditText = "CREDIT";
char* highScoreText = "HIGH SCORE";

int player1Score = 0;
int player2Score = 0;

using namespace std;


int main(int argcx, char* argv[])
{
	Initialise(screenWidth, screenHeight, false, "Space Invaders Clone");
	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));

	unsigned int playerCannon = CreateSprite("./images/cannon.png", playerCannonWidth, playerCannonHeight, true);

	MoveSprite(playerCannon, playerCannponXPos, playerCannonYPos);

	do
	{
		ClearScreen();

		DrawString(player1ScoreText, screenWidth * 0.025f, screenHeight - 2);
		DrawString(highScoreText, (screenWidth / 2) -90, screenHeight - 2);
		DrawString(player2ScoreText, screenWidth - 180, screenHeight - 2);
		char scoreStringBuffer[32];
		itoa(player1Score, scoreStringBuffer, 10);
		DrawString(scoreStringBuffer, 50, screenHeight - 45);

		itoa(player2Score, scoreStringBuffer, 10);
		DrawString(scoreStringBuffer, screenWidth - 100, screenHeight - 45);

		if (IsKeyDown('A'))
		{
			playerCannponXPos -= 2.0f;
			if (playerCannponXPos < 32.0f)
			{
				playerCannponXPos = 32.0f;
			}
		}
		else if (IsKeyDown('S'))
		{
			playerCannponXPos += 2.0f;
			if (playerCannponXPos > screenWidth - playerCannonWidth / 2)
			{
				playerCannponXPos = screenWidth - playerCannonWidth / 2;
			}
		}
		MoveSprite(playerCannon, playerCannponXPos, playerCannonYPos);

		DrawSprite(playerCannon);

	} while (!FrameworkUpdate());
	
	Shutdown();

	return 0;
}