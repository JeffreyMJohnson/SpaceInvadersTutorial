#pragma once

#ifndef _PLAYER_H_
#define  _PLAYER_H_
#include "AIE.h"


class Player
{
public:
	Player();


	//convenience functions
	void SetSize(float a_width, float a_height);
	void SetPosition(float a_x, float a_y);
	void SetMovementKeys(unsigned int a_moveLeft, unsigned int a_moveRight);
	void SetMovementExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme);
	void Move(float a_timeStep);


	//standard setters/getters
	void SetSpriteID(unsigned int a_ID);
	unsigned int GetSpriteID();

	void SetWidth(float a_width);
	float GetWidth();

	void SetHeight(float a_height);
	float GetHeight();

	void SetSpeed(float a_speed);
	float GetSpeed();

	void SetX(float a_x);
	float GetX();

	void SetY(float a_y);
	float GetY();

	void SetMoveLeftKey(unsigned int a_moveKey);
	unsigned int GetLeftMoveKey();

	void SetMoveRightgKey(unsigned int a_moveKey);
	unsigned int GetMoveRightKey();

	void SetLeftMovementExtreme(unsigned int a_movementExtreme);
	unsigned int GetLeftMovementExtreme();

	void SetRightMovementExtreme(unsigned int a_movementExtreme);
	unsigned int GetRightMovementExtreme();

	~Player();
	
private:
	unsigned int spriteID;
	float width;
	float height;
	float speed = 500.0f;
	float x;
	float y;
unsigned int moveLeftKey;
	unsigned int moveRightKey;
unsigned int leftMovementExtreme;
	unsigned int rightMovementExtreme;

};


#endif // _PLAYER_H_