#pragma once
#ifndef _GAME_STATE_H_
#include "BaseState.h"
#include "AIE.h"
#include "StateMachine.h"
#include "Player.h";
#include "Enemy.h"
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

	void AddScore(int a_score);

	std::vector<Entity*> gameObjects;
	Enemy enemies[NUM_ENEMYS];

	unsigned int bulletTexture;
	int score;
	int direction;
	int activeEnemiesCount = NUM_ENEMYS;
};
#endif // !_GAME_STATE_H_


