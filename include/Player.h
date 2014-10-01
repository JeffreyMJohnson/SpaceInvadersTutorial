#pragma once

#ifndef _PLAYER_H_
#define  _PLAYER_H_
#include "Bullet.h"
#include "Entity.h"


const int MAX_BULLETS = 20;

class Player : public Entity
{
public:
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

	void SetSpeed(float a_speed);
	float GetSpeed();

	Bullet bullets[MAX_BULLETS];

	Player();
	~Player();

	unsigned int shootKey;

private:
	unsigned int moveLeftKey;
	unsigned int moveRightKey;
	float speed;
	unsigned int leftMovementExtreme;
	unsigned int rightMovementExtreme;
	float currentReloadBulletTime;
	float maxBulletReloadTime;

};


#endif // _PLAYER_H_