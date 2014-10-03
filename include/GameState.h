#pragma once
#ifndef _GAME_STATE_H_
#include "BaseState.h"
#include "AIE.h"
#include "StateMachine.h"
#include "Player.h";
#include "Enemy.h"
#include "Highscores.h"
#include "LeaderboardState.h"
#include <vector>
#include <string>

const int NUM_ENEMYS = 24;

class GameState : public BaseState
{
public:
	GameState();
	~GameState();

	void Initialize();
	void Update(float a_timeStep, StateMachine* a_SMPointer);
	void Draw();
	void Destroy();

private:
	void CreateEnemies();
	void MoveEnemies(float a_speed, int a_direction, float a_delta);
	void DrawEnemies();

	void PlayerLogic(Player* a_player, float a_delta);
	void EnemyLogic(Enemy* a_enemy, bool& lowerAliens);

	bool CheckCollision(float x1, float y1, float x2, float y2, float distance);

	std::vector<Entity*> gameObjects;
	Enemy enemies[NUM_ENEMYS];

	unsigned int bulletTexture;
	int score;
	int highScore;
	int direction;
	int activeEnemiesCount = NUM_ENEMYS;

	char p1Score_s[20];
	char highScore_s[20];

	bool gameOver;
	float gameOverTimer;
};
#endif // !_GAME_STATE_H_


