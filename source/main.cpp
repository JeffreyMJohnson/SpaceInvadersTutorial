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


using namespace std;

enum GAMESTATES
{
	MAIN_MENU,
	GAMEPLAY,
	END
};

//Input handling during gameplay state
void GameplayHandleInput();

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

Enemy mEnemies[COLS * ROWS];

GAMESTATES mCurrentState = MAIN_MENU;


int main(int argcx, char* argv[])
{
	//flag to quit game gracefully
	bool quitGame = false;

	Initialise(screenWidth, screenHeight, false, "Space Invaders Clone");
	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));
	AddFont(invadersFont);

	player.SetSize(playerCannonWidth, playerCannonHeight);
	player.SetPosition(playerCannonXPos, playerCannonYPos);
	player.SetMovementKeys('A', 'S');
	player.SetMovementExtremes(playerCannonWidth/2, screenWidth - (playerCannonWidth/2));
	player.SetSpriteID(CreateSprite("./images/cannon.png", player.GetWidth(), player.GetHeight(), true));
	MoveSprite(player.GetSpriteID(), player.GetX(), player.GetY());

	//create marquee sprite
	unsigned int arcadeMarquee = CreateSprite("./images/Space-Invaders-Marquee.png", screenWidth, screenHeight, false);

	//load enemies array
	EnemiesLoad();

	EnemiesInitialDraw();

	MoveSprite(arcadeMarquee, 0, screenHeight);

	//DEBUG::
	mCurrentState = GAMEPLAY;

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
		mEnemies[i].setMovementExtremes(playerCannonWidth/2, screenWidth - (playerCannonWidth/2));
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

	//bool moveDown = false;


	//for (int i = 0, count = ROWS * COLS; i < count; ++i)
	//{
	//	if (mAlienShips[i].move(a_timeDelta, alienMoveDirection))
	//	{
	//		alienMoveDirection = SwapDirection(alienMoveDirection);
	//		moveDown = true;
	//	}
	//	DrawSprite(mAlienShips[i].GetSpriteID());
	//}

	//if (moveDown)
	//{
	//	for (int i = 0, count = ROWS * COLS; i < count; ++i)
	//	{
	//		mAlienShips[i].move(a_timeDelta, DOWN);
	//		DrawSprite(mAlienShips[i].GetSpriteID());
	//	}
	//	moveDown = false;
	//}

}

//ALIEN_DIRECTION SwapDirection(const ALIEN_DIRECTION a_direction)
//{
//	ALIEN_DIRECTION result;
//	if (a_direction == LEFT)
//	{
//		return RIGHT;
//	}
//	else
//	{
//		return LEFT;
//	}
//}

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
	else if (IsKeyDown(256)) //code for 'esc' key
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
	if (IsKeyDown(256)) //esc key code
	{
		mCurrentState = MAIN_MENU;
	}

	player.Move(timeDelta);
	//DrawSprite(player.GetSpriteID());

	EnemiesMove(timeDelta);

}

//Input handling during gameplay state
void GameplayHandleInput()
{
	
}

