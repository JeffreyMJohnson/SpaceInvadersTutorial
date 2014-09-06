#include "AIE.h"
#include "stdlib.h"
#include <iostream>

//magic numbers
const int screenWidth = 672;
const int screenHeight = 780;

const int playerCannonWidth = 64;
const int playerCannonHeight = 32;
const float playerCannonYPos = 100.0f;
float playerCannonXPos = screenWidth *0.5f;
const float playerMoveSpeed = 2.0f;

const float lineYPos = 45.0f;

const int COLS = 9;
const int ROWS = 5;
const float alienStartPosX = 50.0f;
const float alienStartPosY = 600.0f;
const float alienXPadding = 5.0f;
const float alienYPadding = 5.0f;

//magic strings
char* player1ScoreText = "SCORE < 1 >";
char* player2ScoreText = "SCORE < 2 >";
char* scoreText = "SCORE";
char* creditText = "CREDIT";
char* highScoreText = "HIGH SCORE";
char* insertCoinsText = "INSERT COINS";

char* player1Score = "00000";
char* player2Score = "00000";
char* highScore = "00000";
char* credit = "99";
char* playerLives = "3";

const char* invadersFont = "./fonts/invaders.fnt";


using namespace std;

enum GAMESTATES
{
		MAIN_MENU,
		GAMEPLAY,
		END
};

GAMESTATES mCurrentState = MAIN_MENU;

unsigned int mAlienShips[COLS * ROWS];

//enter key code is IsKeyDown(257)
void handleGameplayInput(const unsigned int playerCannon)
{
	if (IsKeyDown(256)) //esc key code
	{
		mCurrentState = MAIN_MENU;
	}
	if (IsKeyDown('A'))
	{
		playerCannonXPos -= playerMoveSpeed;
		if (playerCannonXPos < 32.0f)
		{
			playerCannonXPos = 32.0f;
		}
	}
	else if (IsKeyDown('S'))
	{
		playerCannonXPos += playerMoveSpeed;
		if (playerCannonXPos > screenWidth - playerCannonWidth / 2)
		{
			playerCannonXPos = screenWidth - playerCannonWidth / 2;
		}
	}
	MoveSprite(playerCannon, playerCannonXPos, playerCannonYPos);
}

void loadEnemies()
{
	//float enemyXPos = screenWidth * 0.2f;
	//float enemyYPos = screenHeight * 0.7f;
	for (int i = 0, totalCount = ROWS * COLS; i < totalCount; ++i)
	{
		mAlienShips[i] = CreateSprite("./images/invaders/invaders_1_00.png", playerCannonWidth, playerCannonHeight, true);
		//MoveSprite(mAlienShips[i], enemyXPos, enemyYPos);
		//enemyXPos += 0.12 * screenWidth;
	}
}

void drawEnemies()
{
	float xPos;
	float yPos = alienStartPosY;
	int index = 0;
	for (int row = 0; row < ROWS; ++row)
	{
		xPos = alienStartPosX; //need to initialize here due to resetting value after each row
		for (int col = 0; col < COLS; ++col, ++index)
		{
			unsigned int alien = mAlienShips[index];
			MoveSprite(alien, xPos, yPos);
			DrawSprite(alien);
			xPos += playerCannonWidth + alienXPadding;
			//++index; //manually incrementing index count
		}
		yPos -= playerCannonHeight + alienYPadding; //need to subtract because drawing from top of screen down
	}
}

int main(int argcx, char* argv[])
{
	Initialise(screenWidth, screenHeight, false, "Space Invaders Clone");
	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));
	AddFont(invadersFont);

	unsigned int playerCannon = CreateSprite("./images/cannon.png", playerCannonWidth, playerCannonHeight, true);

	//create marquee sprite
	unsigned int arcadeMarquee = CreateSprite("./images/Space-Invaders-Marquee.png", screenWidth, screenHeight, false);

	//load enemies array
	loadEnemies();

	MoveSprite(playerCannon, playerCannonXPos, playerCannonYPos);
	MoveSprite(arcadeMarquee,0,screenHeight);

	do
	{
		ClearScreen();
		SetFont(invadersFont);

		switch (mCurrentState)
		{
		case MAIN_MENU:
			
			DrawSprite(arcadeMarquee);
			DrawString(insertCoinsText, screenWidth * 0.37f, screenHeight * 0.5f);
			DrawString(creditText, screenWidth * 0.25f, screenHeight * 0.4f);
			DrawString(credit, screenWidth * 0.5f, screenHeight * 0.4f);
			//DrawString("foo", screenWidth / 2, screenHeight / 2);


			if (IsKeyDown(257))	//windows code for enter key
			{
				mCurrentState = GAMEPLAY;
			}
			break;
		case GAMEPLAY:
			DrawString(player1ScoreText, screenWidth * 0.025f, screenHeight - 2);
			DrawString(highScoreText, (screenWidth / 2) - 90, screenHeight - 2);
			DrawString(player2ScoreText, screenWidth - 150, screenHeight - 2);
			//char scoreStringBuffer[32];
			//itoa(player1Score, scoreStringBuffer, 10);
			//DrawString(scoreStringBuffer, 50, screenHeight - 45);
			DrawString(player1Score, 35, screenHeight - 30);

			//itoa(player2Score, scoreStringBuffer, 10);
			//DrawString(scoreStringBuffer, screenWidth - 100, screenHeight - 45);
			DrawString(player2Score, screenWidth - 125, screenHeight - 30);

			DrawString(highScore, screenWidth / 2 - 60, screenHeight - 30);

			DrawString(playerLives, 40, lineYPos - 2);

			DrawString(creditText, screenWidth - 200, lineYPos - 2);
			DrawString(credit, screenWidth - 75, lineYPos - 2);


			DrawLine(0, lineYPos, screenWidth, lineYPos, SColour(0x00, 0xFF, 0x00, 0xFF));

			handleGameplayInput(playerCannon);

			DrawSprite(playerCannon);
			drawEnemies();
			break;
		case END:
			;
		}
		

	} while (!FrameworkUpdate());
	
	Shutdown();

	return 0;
}

