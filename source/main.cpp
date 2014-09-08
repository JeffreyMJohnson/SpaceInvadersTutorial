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
const float playerMoveSpeed = 500.0f;

const float lineYPos = 45.0f;

const int COLS = 9;
const int ROWS = 5;
const float alienStartPosX = 50.0f;
const float alienStartPosY = 600.0f;
const float alienXPadding = 5.0f;
const float alienYPadding = 5.0f;

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


using namespace std;

//Input handling during gameplay state
void HandleGameplayInput();

//Load array with enemy sprite ID
void LoadEnemies();

//draw enemies from array to screen
void DrawEnemies();

//main menu game state code
void UpdateMainMenu(unsigned int arcadeMarquee);

//Draw UI for gamestate on screen
void DrawUI();

//GameState code
void UpdateGameState();


enum GAMESTATES
{
	MAIN_MENU,
	GAMEPLAY,
	END
};

enum ENEMY_DIRECTION
{
	LEFT,
	RIGHT,
	DOWN
};

struct PlayerCannon
{
	unsigned int spriteID;
	float width;
	float height;

	void SetSize(float a_width, float a_height)
	{
		width = a_width;
		height = a_height;
	}

	float x;
	float y;

	void SetPosition(float a_x, float a_y)
	{
		x = a_x;
		y = a_y;
	}

	unsigned int moveLeftKey;
	unsigned int moveRightKey;
	void SetMovementKeys(unsigned int a_moveLeft, unsigned int a_moveRight)
	{
		moveLeftKey = a_moveLeft;
		moveRightKey = a_moveRight;
	}

	unsigned int leftMovementExtreme;
	unsigned int rightMovementExtreme;
	void setMovementExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme)
	{
		leftMovementExtreme = a_leftExtreme;
		rightMovementExtreme = a_rightExtreme;
	}

	void move(float a_timeStep, float a_speed)
	{
		if (IsKeyDown(moveLeftKey))
		{
			x -= a_timeStep * a_speed;
			if (x < (leftMovementExtreme + width / 2))
			{
				x = (leftMovementExtreme + width / 2);
			}
		}
		if (IsKeyDown(moveRightKey))
		{
			x+= a_timeStep * a_speed;
			if (x >(rightMovementExtreme - width / 2))
			{
				x = (rightMovementExtreme - width / 2);
			}
		}
		MoveSprite(spriteID, x, y);
	}

	

};

struct Enemy
{
	unsigned int spriteID;
	float width;
	float height;
	void SetSize(float a_width, float a_height)
	{
		width = a_width;
		height = a_height;
	}

	float x;
	float y;
	void SetPosition(float a_x, float a_y)
	{
		x = a_x;
		y = a_y;
	}

	unsigned int leftMovementExtreme;
	unsigned int rightMovementExtreme;

	void setMovementExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme)
	{
		leftMovementExtreme = a_leftExtreme;
		rightMovementExtreme = a_rightExtreme;
	}

	bool move(float a_deltaTime, int a_direction)
	{
		if (a_direction == LEFT)
		{
			//move left 
			if (x < leftMovementExtreme + width/2)
			{
				x = leftMovementExtreme + width/2;
				return true;
			}
		}
		if (a_direction == RIGHT)
		{
			//move right
			if (x > rightMovementExtreme - width/2)
			{
				x = rightMovementExtreme - width/2;
				return true;
			}
		}
		if (a_direction == DOWN)
		{
			//move towards planet
		}
	}
};

PlayerCannon player;

GAMESTATES mCurrentState = MAIN_MENU;

unsigned int mAlienShips[COLS * ROWS];



int main(int argcx, char* argv[])
{
	Initialise(screenWidth, screenHeight, false, "Space Invaders Clone");
	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));
	AddFont(invadersFont);

	player.SetSize(playerCannonWidth, playerCannonHeight);
	player.SetPosition(playerCannonXPos, playerCannonYPos);
	player.SetMovementKeys('A', 'S');
	player.setMovementExtremes(0, screenWidth);
	player.spriteID = CreateSprite("./images/cannon.png", player.width, player.height, true);
	MoveSprite(player.spriteID, player.x, player.y);
	
	//create marquee sprite
	unsigned int arcadeMarquee = CreateSprite("./images/Space-Invaders-Marquee.png", screenWidth, screenHeight, false);

	//load enemies array
	LoadEnemies();


	MoveSprite(arcadeMarquee, 0, screenHeight);

	do
	{
		ClearScreen();
		SetFont(invadersFont);

		switch (mCurrentState)
		{
		case MAIN_MENU:
			UpdateMainMenu(arcadeMarquee);


			break;
		case GAMEPLAY:
			UpdateGameState();
			break;
		case END:
			;
		}


	} while (!FrameworkUpdate());

	Shutdown();

	return 0;
}

void LoadEnemies()
{
	for (int i = 0, totalCount = ROWS * COLS; i < totalCount; ++i)
	{
		mAlienShips[i] = CreateSprite("./images/invaders/invaders_1_00.png", playerCannonWidth, playerCannonHeight, true);
	}
}

void DrawEnemies()
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

void UpdateMainMenu(unsigned int arcadeMarquee)
{
	DrawSprite(arcadeMarquee);
	DrawString(insertCoinsText, screenWidth * 0.37f, screenHeight * 0.5f);
	DrawString(creditText, screenWidth * 0.25f, screenHeight * 0.4f);
	DrawString(credit, screenWidth * 0.5f, screenHeight * 0.4f);

	if (IsKeyDown(257))	//windows code for enter key
	{
		mCurrentState = GAMEPLAY;
	}
}

void DrawUI()
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

void UpdateGameState()
{
	DrawUI();
	if (IsKeyDown(256)) //esc key code
	{
		mCurrentState = MAIN_MENU;
	}
	player.move(GetDeltaTime(), playerMoveSpeed);
	DrawSprite(player.spriteID);
	DrawEnemies();
}

