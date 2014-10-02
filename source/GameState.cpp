#include "GameState.h"


extern const int screenWidth;
extern const int screenHeight;

extern const char* invadersFont;
extern const char* player1ScoreText;
extern const char* player2ScoreText;
extern const char* highScoreText;
extern const char* insertCoinsText;
extern const char* creditText;

extern std::string scoreAsString;
extern char* player2Score;
extern char* highScore;
extern char* playerLives;
extern char* credit;

extern const float lineYPos;


GameState::GameState()
{
	score = 0;
	direction = 1;
	bulletTexture = -1;
}


GameState::~GameState()
{
}

void GameState::Initialize()
{
	Player* player = new Player();

	player->SetSize(64.0f, 32.0f);
	player->SetMovementKeys('A', 'D');
	player->SetShootKey(32); //space key
	player->SetMovementExtremes(0, screenWidth);
	player->SetSpriteId(CreateSprite("./images/cannon.png", player->GetWidth(), player->GetHeight(), true));
	player->SetX(screenWidth * 0.5f);
	player->SetY(100.0f);
	player->SetSpeed(float(screenWidth));

	//add player to dynamic array
	gameObjects.push_back(player);

	MoveSprite(player->GetSpriteID(), player->GetX(), player->GetY());

	bulletTexture = CreateSprite("./images/player_shot.png", 3, 20, true);
	
	CreateEnemies();
}

void GameState::Destroy()
{
	for (auto object : gameObjects)
	{
		DestroySprite(object->GetSpriteID());
	}
	DestroySprite(bulletTexture);
}

void GameState::PlayerLogic(Player* a_player, float a_delta)
{
	a_player->Shoot(bulletTexture, a_delta);

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
					enemyShip->GetIsActive() &&
					a_player->bullets[i].isActive)
				{
					enemyShip->SetIsActive(false);
					a_player->bullets[i].isActive = false;
					//a_player->AddScore(1);
					AddScore(enemyShip->GetScoreValue());
					activeEnemiesCount--;
				}
			}
		}
	}
}

void GameState::EnemyLogic(Enemy* a_enemy, bool& lowerAliens)
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

	int speed = 750;
	a_enemy->SetDirection(direction);
	//check for zero before dividing damn it!
	if (activeEnemiesCount != 0)
		speed /= activeEnemiesCount;
	a_enemy->SetSpeed(speed);
}

void GameState::Update(float a_timestep, StateMachine* a_SMPointer)
{
	//escape key
	if (IsKeyDown(256))
	{
		BaseState* lastState = a_SMPointer->PopState();
		delete lastState;
		return;
	}

	//update enemies
	bool lowerAliens = false;

	for (auto object : gameObjects)
	{
		//determine the type at runtime
		if (dynamic_cast<Player*>(object) != 0)
		{
			//process player specific  logic
			PlayerLogic(dynamic_cast<Player*>(object), a_timestep);
		}

		if (dynamic_cast<Enemy*>(object) != 0)
		{
			//process enemy specific logic
			EnemyLogic(dynamic_cast<Enemy*>(object), lowerAliens);
		}

		//update and draw objects
		object->Update(a_timestep);
		object->Draw();
	}

	//with better logic this could be put in the main object update loop 
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

}

void GameState::Draw()
{
	for (auto object : gameObjects)
	{
		object->Draw();
	}

	DrawLine(0, lineYPos, screenWidth, lineYPos, SColour(0x00, 0xFF, 0x00, 0xFF));

	SetFont(invadersFont);
	DrawString(player1ScoreText, screenWidth * 0.025f, screenHeight - 2);
	DrawString(highScoreText, (screenWidth / 2) - 90, screenHeight - 2);
	DrawString(player2ScoreText, screenWidth - 150, screenHeight - 2);
	DrawString(scoreAsString.c_str(), 35, screenHeight - 30);
	DrawString(player2Score, screenWidth - 125, screenHeight - 30);
	DrawString(highScore, screenWidth / 2 - 60, screenHeight - 30);
	DrawString(playerLives, 40, lineYPos - 2);
	DrawString(creditText, screenWidth - 200, lineYPos - 2);
	DrawString(credit, screenWidth - 75, lineYPos - 2);

	
}
bool GameState::CheckCollision(float x1, float y1, float x2, float y2, float distance)
{
	float d = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	if (d < distance)
		return true;
	else
		return false;
}

void GameState::CreateEnemies()
{
	//first enemy's position
	float enemyX = screenWidth * 0.2f;
	float enemyY = screenHeight *0.9f;

	for (int i = 0; i < NUM_ENEMYS; i++)
	{
		Enemy* enemy = new Enemy();

		enemy->SetSpriteId(CreateSprite("./images/invaders/invaders_1_00.png", 64, 32, true));
		
		//check if need new line of enemy
		if (enemyX > screenWidth * 0.8f)
		{
			enemyX = screenWidth * 0.2f;
			enemyY -= 0.04f * screenHeight;
		}

		//initialize position
		enemy->SetPosition(enemyX, enemyY);

		//increment next enemy's x position
		enemyX += 0.12f * screenWidth;

		enemy->SetScoreValue(30);

		gameObjects.push_back(enemy);
	}
}

/*
Add a score of the given param to the player's score.
param:
a_score - int to add to player's score.
*/
void GameState::AddScore(int a_score)
{
	score += a_score;
	char buff[6];
	sprintf(buff, "%05d", score);
	//strcpy(scoreAsString, buff);
	scoreAsString = buff;
}

