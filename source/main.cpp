#include "AIE.h"
#include "Player.h"
#include "Enemy.h"
#include "stdlib.h"
#include <iostream>
#include <vector>

using namespace std;

//magic numbers
const int screenWidth = 672;
const int screenHeight = 780;

const float lineYPos = 45.0f;

//enemy magic numbers
const int NUM_ENEMYS = 24;

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


void PlayerLogic(Player*, float a_delta);
void EnemyLogic(Enemy* enemy, bool& lowerAliens);


//Load array with Alien sprite ID
void EnemiesLoad();

//main menu game state code
void MenuUpdate(unsigned int arcadeMarquee);

//Draw UI for game state on screen
void GameplayUIDraw();

//GameState code
void GameplayUpdate();

bool CheckCollision(float x1, float y1, float x2, float y2, float distance);

Player* player;
int score = 0;
int direction = 1;

unsigned int  mBulletTextureID;



vector<Entity*>gameObjects;

int mEnemiesDirection = 1;
int activeEnemiesCount = NUM_ENEMYS;

GAMESTATES mCurrentState = MAIN_MENU;


int main(int argcx, char* argv[])
{
	//flag to quit game gracefully
	bool quitGame = false;

	

	//init framework and window
	Initialise(screenWidth, screenHeight, false, "Space Invaders Clone");
	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));
	AddFont(invadersFont);

	//init bullet sprite id
	mBulletTextureID = CreateSprite("./images/player_shot.png", 3, 20, true);

	//init player
	 player = new Player();
	player->SetSize(64.0f, 32.0f);
	player->SetMovementKeys('A', 'D');
	player->SetMovementExtremes(0, screenWidth);
	player->SetSpriteId(CreateSprite("./images/cannon.png", player->GetWidth(), player->GetHeight(), true));
	player->SetX(screenWidth * .5f);
	player->SetY(100.0f);
	player->SetSpeed((float)screenWidth);

	//add player to dynamic array
	gameObjects.push_back(player);

	//create marquee sprite
	unsigned int arcadeMarquee = CreateSprite("./images/Space-Invaders-Marquee.png", screenWidth, screenHeight, false);

	//load enemies array
	EnemiesLoad();

	MoveSprite(arcadeMarquee, 0, screenHeight);

	//DEBUG:
	mCurrentState = GAMEPLAY;

	//game loop
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

/*
Initialize enemy's in array and calculate/set initial position on screen in grid across top
*/
void EnemiesLoad()
{
	//first enemy's position
	float enemyX = screenWidth * 0.2f;
	float enemyY = screenHeight *0.9f;

	for (int i = 0; i < NUM_ENEMYS; i++)
	{
		//BUG??
		Enemy* enemy = new Enemy();
		
		enemy->SetSpriteId(CreateSprite("./images/invaders/invaders_1_00.png",player->GetWidth(), player->GetHeight(), true));

		if (enemyX > screenWidth * 0.8f)
		{
			enemyX = screenWidth * 0.2f;
			enemyY -= 0.04f * screenHeight;
		}

		enemy->SetX(enemyX);
		enemy->SetY(enemyY);

		enemyX += 0.12f * screenWidth;

		gameObjects.push_back(enemy);

		
	}
}

///*
//Call Move() on each sprite
//*/
//void EnemiesMove(float a_speed, int a_direction, float a_timeDelta)
//{
//	for (int i = 0; i < NUM_ENEMYS; i++)
//	{
//		mEnemies[i].SetDirection(a_direction);
//		mEnemies[i].SetSpeed(a_speed / activeEnemiesCount);
//		mEnemies[i].Update(a_timeDelta);
//		mEnemies[i].Draw();
//	}
//
//}

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

	player->Update(timeDelta);
	player->Draw();

	player->Shoot(mBulletTextureID, timeDelta);
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (player->bullets[i].isActive)
		{
			player->bullets[i].Update(timeDelta);
			player->bullets[i].Draw();
		}
	}

	bool lowerAliens = false;

	for (auto object : gameObjects)
	{
		//determine type
		if (dynamic_cast<Player*>(object) != 0)
		{
			PlayerLogic(dynamic_cast<Player*>(object), timeDelta);
		}

		if (dynamic_cast<Enemy*>(object) != 0)
		{
			EnemyLogic(dynamic_cast<Enemy*>(object), lowerAliens);
		}

		object->Update(timeDelta);
		object->Draw();
	}

	//with better logic this could be put in main object update loop
	if (lowerAliens)
	{
		for (auto object : gameObjects)
		{
			if (dynamic_cast<Enemy*>(object) != 0)
			{
				Enemy* enemy = dynamic_cast<Enemy*>(object);

				enemy->SetY(enemy->GetY() - (0.05f * screenHeight));
			}
		}
	}


	//for (int i = 0; i < NUM_ENEMYS; i++)
	//{
	//	//check for right wall collision
	//	if (mEnemies[i].GetIsActive() && mEnemies[i].GetX() > screenWidth * 0.9f)
	//	{
	//		mEnemies[i].SetX(screenWidth * 0.9f);
	//		mEnemiesDirection = -1;
	//		lowerAliens = true;
	//		break;
	//	}//check for right wall collision
	//	else if (mEnemies[i].GetIsActive() && mEnemies[i].GetX() < screenWidth * 0.1f)
	//	{
	//		mEnemies[i].SetX(screenWidth * 0.1f);
	//		mEnemiesDirection = 1;
	//		lowerAliens = true;
	//		break;
	//	}
	//}

	//if (lowerAliens)
	//{
	//	for (int i = 0; i < NUM_ENEMYS; i++)
	//	{
	//		mEnemies[i].SetY(mEnemies[i].GetY() - (screenHeight * 0.05f));
	//	}
	//}

	//float speed = 1000.0f;

	////move enemies to new position
	//EnemiesMove(speed / activeEnemiesCount, mEnemiesDirection, timeDelta);
	////EnemiesDraw();


	//
	////collision check for bullets and enemies
	//for (int i = 0; i < MAX_BULLETS; i++)
	//{
	//	for (int j = 0; j < NUM_ENEMYS; j++)
	//	{
	//		if (CheckCollision(player.bullets[i].x, player.bullets[i].y, mEnemies[j].GetX(), mEnemies[j].GetY(), 30.0f) &&
	//			mEnemies[j].GetIsActive() && player.bullets[i].isActive)
	//		{
	//			mEnemies[j].SetIsActive(false);
	//			player.bullets[i].isActive = false;
	//			activeEnemiesCount--;
	//		}
	//	}
	//}


	//DEBUG: THIS IS FOR DEBUG, REMOVE FOR RELEASE
	if (IsKeyDown(256)) //esc key code
	{
		mCurrentState = MAIN_MENU;
	}
}

//void EnemiesDraw()
//{
//	for (int i = 0; i < NUM_ENEMYS; i++)
//	{
//		if (mEnemies[i].GetIsActive())
//		{
//			mEnemies[i].Draw();
//		}
//	}
//}

bool CheckCollision(float x1, float y1, float x2, float y2, float distance)
{
	float d = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

	if (d < distance)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void PlayerLogic(Player* a_player, float a_delta)
{
	a_player->Shoot(mBulletTextureID, a_delta);

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		a_player->bullets[i].Update(a_delta);
		a_player->bullets[i].Draw();
	}

	for (auto enemy : gameObjects)
	{
		if (dynamic_cast<Enemy*>(enemy) != 0)
		{
			Enemy* enemyShip = dynamic_cast<Enemy*>(enemy);
			for (int i = 0; i < MAX_BULLETS; i++)
			{
				if (CheckCollision(a_player->bullets[i].x, a_player->bullets[i].y, enemyShip->GetX(), enemyShip->GetY(), 30.0f) &&
					enemyShip->GetIsActive()  &&
					a_player->bullets[i].isActive)
				{
					enemyShip->SetIsActive(false);
					a_player->bullets[i].isActive = false;
					score++;
					activeEnemiesCount--;
				}
			}
		}
	}
}

void EnemyLogic(Enemy* a_enemy, bool& lowerAliens)
{
	if (a_enemy->GetX() > screenWidth * 0.9f && !lowerAliens)
	{
		direction = -1;
		lowerAliens = true;
		//break;
	}
	else if (a_enemy->GetX() < screenWidth * 0.1f && !lowerAliens)
	{
		direction = 1;
		lowerAliens = true;
		//break;
	}

	int speed = 10;
	a_enemy->SetDirection(direction);
	a_enemy->SetSpeed(speed / activeEnemiesCount);
}