#include "AIE.h"
#include "Player.h"
#include "Enemy.h"
#include "stdlib.h"
#include <iostream>

//magic numbers
const int screenWidth = 672;
const int screenHeight = 780;

const int playerCannonWidth = 64;
const int playerCannonHeight = 32;
const float playerCannonYPos = 100.0f;
float playerCannonXPos = screenWidth *0.5f;

const float lineYPos = 45.0f;

//const int COLS = 9;
//const int ROWS = 5;
const int COLS = 2;
const int ROWS = 2;
const float alienStartPosX = 50.0f;
const float alienStartPosY = 600.0f;
const float alienXPadding = 5.0f;
const float alienYPadding = 5.0f;
const float AlienMoveSpeed = 100.0f;

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

enum GAMESTATES
{
	MAIN_MENU,
	GAMEPLAY,
	END
};

//enum ALIEN_DIRECTION
//{
//	LEFT,
//	RIGHT,
//	DOWN
//};

//Input handling during gameplay state
void HandleGameplayInput();

//Load array with Alien sprite ID
void LoadEnemies();

//Move enemies
void MoveEnemies(float a_timeDelta);

//draw enemies from array to screen
void DrawEnemies();

//swap direction enum right to left and vice versa
ALIEN_DIRECTION SwapDirection(const ALIEN_DIRECTION a_direction);

//main menu game state code
void UpdateMainMenu(unsigned int arcadeMarquee);

//Draw UI for gamestate on screen
void DrawUI();

//GameState code
void UpdateGameState();




//struct PlayerCannon
//{
//	
//
//	void SetSize(float a_width, float a_height)
//	{
//		width = a_width;
//		height = a_height;
//	}
//
//	
//
//	void SetPosition(float a_x, float a_y)
//	{
//		x = a_x;
//		y = a_y;
//	}
//
//	
//	void SetMovementKeys(unsigned int a_moveLeft, unsigned int a_moveRight)
//	{
//		moveLeftKey = a_moveLeft;
//		moveRightKey = a_moveRight;
//	}
//
//	
//	void setMovementExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme)
//	{
//		leftMovementExtreme = a_leftExtreme;
//		rightMovementExtreme = a_rightExtreme;
//	}
//
//	void Move(float a_timeStep)
//	{
//		if (IsKeyDown(moveLeftKey))
//		{
//			x -= a_timeStep * speed;
//			if (x < (leftMovementExtreme + width / 2))
//			{
//				x = (leftMovementExtreme + width / 2);
//			}
//		}
//		if (IsKeyDown(moveRightKey))
//		{
//			x+= a_timeStep * speed;
//			if (x >(rightMovementExtreme - width / 2))
//			{
//				x = (rightMovementExtreme - width / 2);
//			}
//		}
//		MoveSprite(spriteID, x, y);
//	}
//
//	
//
//};

//struct Alien
//{
//	unsigned int spriteID;
//
//	Alien()
//	{
//		setMovementExtremes(0, screenWidth);
//		SetSize(playerCannonWidth, playerCannonHeight);
//		SetPosition(playerCannonXPos, playerCannonYPos);
//	}
//
//	float width;
//	float height;
//	void SetSize(float a_width, float a_height)
//	{
//		width = a_width;
//		height = a_height;
//	}
//
//	float x;
//	float y;
//	void SetPosition(float a_x, float a_y)
//	{
//		x = a_x;
//		y = a_y;
//	}
//
//	unsigned int leftMovementExtreme;
//	unsigned int rightMovementExtreme;
//
//	void setMovementExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme)
//	{
//		leftMovementExtreme = a_leftExtreme;
//		rightMovementExtreme = a_rightExtreme;
//	}
//
//	bool move(float a_deltaTime, int a_direction)
//	{
//		float move = 100.0f;
//		if (a_direction == LEFT)
//		{
//			//move left 
//			x -= a_deltaTime * AlienMoveSpeed;
//			//x -= move;
//			MoveSprite(spriteID, x, y);
//			if (x < leftMovementExtreme + width/2)
//			{
//				x = leftMovementExtreme + width/2;
//				MoveSprite(spriteID, x, y);
//				return true;
//			}
//		}
//		if (a_direction == RIGHT)
//		{
//			//move right
//			x += a_deltaTime * AlienMoveSpeed;
//			//x += move;
//			MoveSprite(spriteID, x, y);
//			if (x > rightMovementExtreme - width/2)
//			{
//				x = rightMovementExtreme - width/2;
//				MoveSprite(spriteID, x, y);
//				return true;
//			}
//		}
//		if (a_direction == DOWN)
//		{
//			//move towards planet
//			y -= height;
//			//y -= move;
//			MoveSprite(spriteID, x, y);
//			if (y < 0 + playerCannonHeight/2)
//			{
//				y = 0 + playerCannonHeight/2;
//				MoveSprite(spriteID, x, y);
//			}
//			return false;
//		}
//		return false;
//		
//	}
//};

Player player;

GAMESTATES mCurrentState = MAIN_MENU;

//unsigned int mAlienShips[COLS * ROWS];
Enemy mAlienShips[COLS * ROWS];
ALIEN_DIRECTION alienMoveDirection = RIGHT;


int main(int argcx, char* argv[])
{
	Initialise(screenWidth, screenHeight, false, "Space Invaders Clone");
	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));
	AddFont(invadersFont);

	player.SetSize(playerCannonWidth, playerCannonHeight);
	player.SetPosition(playerCannonXPos, playerCannonYPos);
	player.SetMovementKeys('A', 'S');
	player.SetMovementExtremes(0, screenWidth);
	player.SetSpriteID(CreateSprite("./images/cannon.png", player.GetWidth(), player.GetHeight(), true));
	MoveSprite(player.GetSpriteID(), player.GetX(), player.GetY());

	//create marquee sprite
	unsigned int arcadeMarquee = CreateSprite("./images/Space-Invaders-Marquee.png", screenWidth, screenHeight, false);

	//load enemies array
	LoadEnemies();
	DrawEnemies();

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
	/*for (int i = 0, totalCount = ROWS * COLS; i < totalCount; ++i)
	{
	mAlienShips[i] = CreateSprite("./images/invaders/invaders_1_00.png", playerCannonWidth, playerCannonHeight, true);
	}
	*/
	//		setMovementExtremes(0, screenWidth);
	//		SetSize(playerCannonWidth, playerCannonHeight);
	//		SetPosition(playerCannonXPos, playerCannonYPos);


	for (int i = 0, totalCount = ROWS * COLS; i < totalCount; ++i)
	{
		Enemy enemy = Enemy();
		enemy.SetSpriteID(CreateSprite("./images/invaders/invaders_1_00.png", enemy.GetWidth(), enemy.GetHeight(), true));
		enemy.setMovementExtremes(0, screenWidth);
		enemy.SetSize(playerCannonWidth, playerCannonHeight);
		enemy.SetPosition(playerCannonXPos, playerCannonYPos);
		enemy.SetSpeed(AlienMoveSpeed);
		mAlienShips[i] = enemy;
	}
}

void MoveEnemies(float a_timeDelta)
{
	bool moveDown = false;


	for (int i = 0, count = ROWS * COLS; i < count; ++i)
	{
		if (mAlienShips[i].move(a_timeDelta, alienMoveDirection))
		{
			alienMoveDirection = SwapDirection(alienMoveDirection);
			moveDown = true;
		}
		DrawSprite(mAlienShips[i].GetSpriteID());
	}

	if (moveDown)
	{
		for (int i = 0, count = ROWS * COLS; i < count; ++i)
		{
			mAlienShips[i].move(a_timeDelta, DOWN);
			DrawSprite(mAlienShips[i].GetSpriteID());
		}
		moveDown = false;
	}

}

ALIEN_DIRECTION SwapDirection(const ALIEN_DIRECTION a_direction)
{
	ALIEN_DIRECTION result;
	if (a_direction == LEFT)
	{
		return RIGHT;
	}
	else
	{
		return LEFT;
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
			Enemy enemy = mAlienShips[index];

			enemy.SetPosition(xPos, yPos);
			MoveSprite(enemy.GetSpriteID(), enemy.GetX(), enemy.GetY());
			DrawSprite(enemy.GetSpriteID());
			xPos += enemy.GetWidth() + alienXPadding;
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
	float timeDelta = GetDeltaTime();

	DrawUI();
	if (IsKeyDown(256)) //esc key code
	{
		mCurrentState = MAIN_MENU;
	}
	player.Move(timeDelta);
	DrawSprite(player.GetSpriteID());

	MoveEnemies(timeDelta);
}

