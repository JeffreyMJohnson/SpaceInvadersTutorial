#include "AIE.h"
#include "Player.h"
#include "Enemy.h"
#include "stdlib.h"
#include <iostream>

using namespace std;

//magic numbers
const int screenWidth = 672;
const int screenHeight = 780;

const int playerCannonWidth = 64;
const int playerCannonHeight = 32;
const float playerCannonYPos = 100.0f;
float playerCannonXPos = screenWidth *0.5f;

const float lineYPos = 45.0f;

//enemy magic numbers
const float ENEMY_Y_SPEED = -100.0f;
const float ENEMY_X_SPEED = 100.0f;

const int COLS = 9;
const int ROWS = 5;
const float ENEMY_START_POSITION_X = 50.0f;
const float ENEMY_START_POSITION_Y = 600.0f;
const float alienXPadding = 5.0f;
const float alienYPadding = 5.0f;
//const float AlienMoveSpeed = 100.0f;

//magic strings
const char* player1ScoreText = "SCORE < 1 >";
const char* player2ScoreText = "SCORE < 2 >";
const char* scoreText = "SCORE";
const char* creditText = "CREDIT";
const char* highScoreText = "HIGH SCORE";
const char* insertCoinsText = "INSERT COINS";

char* player1Score = "00000";
char* player2Score = "00000";
char* highScore = "00000";
char* credit = "99";
char* playerLives = "3";

const char* invadersFont = "./fonts/invaders.fnt";

enum GAMESTATES
{
	MAIN_MENU,
	GAMEPLAY,
	END
};


//Load array with Alien sprite ID
void EnemiesLoad();

//Move enemies
void EnemiesMove(float a_timeDelta);

//draw enemies from array to screen
void EnemiesInitialDraw();

//main menu game state code
void MenuUpdate(unsigned int arcadeMarquee);

//Draw UI for gamestate on screen
void GameplayUIDraw();

//GameState code
void GameplayUpdate();

Player player;

Enemy mEnemies[COLS * ROWS];

GAMESTATES mCurrentState = MAIN_MENU;


int main(int argcx, char* argv[])
{
	//flag to quit game gracefully
	bool quitGame = false;

	//init framework and window
	Initialise(screenWidth, screenHeight, false, "Space Invaders Clone");
	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));
	AddFont(invadersFont);

	//init player
	player.SetSize(playerCannonWidth, playerCannonHeight);
	player.SetPosition(playerCannonXPos, playerCannonYPos);
	player.SetMovementKeys('A', 'S');
	player.SetMovementExtremes(playerCannonWidth / 2, screenWidth - (playerCannonWidth / 2));
	player.SetSpriteID(CreateSprite("./images/cannon.png", player.GetWidth(), player.GetHeight(), true));
	MoveSprite(player.GetSpriteID(), player.GetX(), player.GetY());

	//create marquee sprite
	unsigned int arcadeMarquee = CreateSprite("./images/Space-Invaders-Marquee.png", screenWidth, screenHeight, false);

	//load enemies array
	EnemiesLoad();

	EnemiesInitialDraw();

	MoveSprite(arcadeMarquee, 0, screenHeight);

	do
	{
		ClearScreen();
		SetFont(invadersFont);

		switch (mCurrentState)
		{
		case MAIN_MENU:
			MenuUpdate(arcadeMarquee);
			break;
		case GAMEPLAY:
			GameplayUpdate();
			break;
		case END:
			quitGame = true;
			break;
		}


	} while (!FrameworkUpdate() && !quitGame);

	Shutdown();
	//system("pause");
	return 0;
}

void EnemiesLoad()
{
	for (int i = 0, totalCount = ROWS * COLS; i < totalCount; ++i)
	{
		mEnemies[i].setMovementExtremes(playerCannonWidth / 2, screenWidth - (playerCannonWidth / 2));
		mEnemies[i].SetSize(playerCannonWidth, playerCannonHeight);
		mEnemies[i].SetPosition(playerCannonXPos, playerCannonYPos);
		mEnemies[i].SetSpeedX(ENEMY_X_SPEED);
		//mEnemies[i].SetSpeedY(0); //init to 0 so enemies don't move down
		mEnemies[i].SetSpriteID(CreateSprite("./images/invaders/invaders_1_00.png", mEnemies[i].GetWidth(), mEnemies[i].GetHeight(), true));
	}
}

/*
Call Move() and Draw() on each sprite
*/
void EnemiesMove(float a_timeDelta)
{
	float deltaTime = GetDeltaTime();
	for (int i = 0; i < ROWS * COLS; i++)
	{
		mEnemies[i].Move(deltaTime);
		mEnemies[i].Draw();
	}

}

/*
Draw enemies to screen in initial grid position. This is done by setting the first enemy to a constant x,y value and computing
the rest off of the position of the previous by adding a padding value for the x and y positions
*/
void EnemiesInitialDraw()
{
	float xPos;
	float yPos = ENEMY_START_POSITION_Y;
	//need a separate index variable due to using nested loop to follow col, row pattern
	int index = 0;

	for (int row = 0; row < ROWS; ++row)
	{
		xPos = ENEMY_START_POSITION_X; //need to initialize here due to resetting value after each row
		for (int col = 0; col < COLS; ++col, ++index)
		{
			//Enemy enemy = mEnemies[index];

			mEnemies[index].SetPosition(xPos, yPos);
			MoveSprite(mEnemies[index].GetSpriteID(), mEnemies[index].GetX(), mEnemies[index].GetY());
			DrawSprite(mEnemies[index].GetSpriteID());
			xPos += mEnemies[index].GetWidth() + alienXPadding;
		}
		yPos -= mEnemies[index].GetHeight() + alienYPadding; //need to subtract because drawing from top of screen down
	}
}

void MenuUpdate(unsigned int arcadeMarquee)
{
	DrawSprite(arcadeMarquee);
	DrawString(insertCoinsText, screenWidth * 0.37f, screenHeight * 0.5f);
	DrawString(creditText, screenWidth * 0.25f, screenHeight * 0.4f);
	DrawString(credit, screenWidth * 0.5f, screenHeight * 0.4f);

	if (IsKeyDown(257))	//windows code for enter key
	{
		mCurrentState = GAMEPLAY;
	}
	else if (IsKeyDown('Q')) 
	{
		mCurrentState = END;
	}
}

void GameplayUIDraw()
{
	DrawString(player1ScoreText, screenWidth * 0.025f, screenHeight - 2);
	DrawString(highScoreText, (screenWidth / 2) - 90, screenHeight - 2);
	DrawString(player2ScoreText, screenWidth - 150, screenHeight - 2);

	DrawString(player1Score, 35, screenHeight - 30);

	DrawString(player2Score, screenWidth - 125, screenHeight - 30);

	DrawString(highScore, screenWidth / 2 - 60, screenHeight - 30);

	DrawString(playerLives, 40, lineYPos - 2);

	DrawString(creditText, screenWidth - 200, lineYPos - 2);
	DrawString(credit, screenWidth - 75, lineYPos - 2);

	DrawLine(0, lineYPos, screenWidth, lineYPos, SColour(0x00, 0xFF, 0x00, 0xFF));
}

void GameplayUpdate()
{
	float timeDelta = GetDeltaTime();

	GameplayUIDraw();


	player.Move(timeDelta);
	EnemiesMove(timeDelta);

	//DEBUG: THIS IS FOR DEBUG, REMOVE FOR RELEASE
	if (IsKeyDown(256)) //esc key code
	{
		mCurrentState = MAIN_MENU;
	}
}

