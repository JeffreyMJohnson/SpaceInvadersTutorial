#pragma once
#include "AIE.h"

#ifndef _ENEMY_H_
#define _ENEMY_H_
enum ALIEN_DIRECTION
{
	LEFT,
	RIGHT,
	DOWN
};

class Enemy
{
public:
	Enemy();

	//helper functions
	void setMovementExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme);
	void SetSize(float a_width, float a_height);
	void SetPosition(float a_x, float a_y);

	bool move(float a_deltaTime, int a_direction);

	//setters/getters
	void SetSpriteID(unsigned int a_spriteID);
	unsigned int GetSpriteID();

	void SetWidth(float a_width);
	float GetWidth();

	void SetHeight(float a_height);
	float GetHeight();

	void SetX(float a_x);
	float GetX();

	void SetY(float a_y);
	float GetY();

	void SetSpeed(float a_speed);
	float GetSpeed();

	void SetLeftMoveExtreme(unsigned int a_leftExtreme);
	unsigned int GetLeftMoveExtreme();

	void SetRightMoveExtreme(unsigned int a_leftExtreme);
	unsigned int GetRightMoveExtreme();



	~Enemy();

private:
	unsigned int spriteID;
	float width;
	float height;
	float x;
	float y;
	float speed;
	unsigned int leftMovementExtreme;
	unsigned int rightMovementExtreme;
};
#endif // !_ENEMY_H_


