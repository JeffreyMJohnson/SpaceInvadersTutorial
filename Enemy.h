#pragma once
#include "AIE.h"
#include "Entity.h"

#ifndef _ENEMY_H_
#define _ENEMY_H_

class Enemy : public Entity
{
public:
	Enemy();

	virtual void Update(float a_delta);
	virtual void Draw();

	void SetSpeed(float a_speedX);
	float GetSpeed();

	void SetDirection(int a_direction);
	int GetDirection();

	void SetIsActive(bool a_isActive);
	bool GetIsActive();
	
	~Enemy();

private:
	bool isActive;
	float speed;
	int direction;
	
};
#endif // !_ENEMY_H_


