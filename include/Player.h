#pragma once

#ifndef _PLAYER_H_
#define  _PLAYER_H_
#include "AIE.h"
#include "Bullet.h"
#include "Entity.h"
#include <iostream>

struct Score
{
	int value;
	std::string value_s;

	char* ToString()
	{
		char buff[6];
		sprintf(buff, "%010d", value);
		return buff;
	}
};

const int MAX_BULLETS = 20;

class Player : public Entity
{
public:

	Bullet bullets[MAX_BULLETS];

	Player();


	//convenience functions
	/*void SetSize(float a_width, float a_height);
	void SetPosition(float a_x, float a_y);*/
	void SetMovementKeys(unsigned int a_moveLeft, unsigned int a_moveRight);
	void SetMovementExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme);

	//Must implement these methods before can instantiate class
	virtual void Update(float a_delta);
	virtual void Draw();


	/*
	Get inactive bullet from bullets array (if any) and initialize with player's current position.
	*/
	void Shoot(unsigned int a_textureID, float _a_delta);

	/*
	Returns reference to first Bullet object in bullets array that is not active. If all are active
	returns the first bullet in the array.
	*/
	Bullet& GetInactiveBullet();

	/*
	Add a score of the given param to the player's score. 
	param:
	a_score - int to add to player's score.
	*/
	//void AddScore(int a_score);



	//standard setters/getters
	
	void SetSpeed(float a_speed);
	float GetSpeed();

	void SetMoveLeftKey(unsigned int a_moveKey);
	unsigned int GetLeftMoveKey();

	void SetMoveRightgKey(unsigned int a_moveKey);
	unsigned int GetMoveRightKey();

	void SetShootKey(unsigned int a_shootKey);
	unsigned int GetShootKey();

	void SetLeftMovementExtreme(unsigned int a_movementExtreme);
	unsigned int GetLeftMovementExtreme();

	void SetRightMovementExtreme(unsigned int a_movementExtreme);
	unsigned int GetRightMovementExtreme();
	
	//int GetScore();
	//char* GetScoreAsString();

	~Player();

	unsigned int shootKey;

private:
	float speed;

	unsigned int moveLeftKey;
	unsigned int moveRightKey;
	
	unsigned int leftMovementExtreme;
	unsigned int rightMovementExtreme;

	float currentReloadBulletTime;
	float maxBulletReloadTime;
	

};


#endif // _PLAYER_H_