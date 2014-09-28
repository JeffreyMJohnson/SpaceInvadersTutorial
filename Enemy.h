#pragma once
#include "AIE.h"

#ifndef _ENEMY_H_
#define _ENEMY_H_

class Enemy
{
public:
	bool isActive;

	Enemy();

	//helper functions for convenience 
	void setMovementExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme);
	void SetSize(float a_width, float a_height);
	void SetPosition(float a_x, float a_y);


	//move enemy 
	void Move(float a_speed, int a_direction, float a_delta);

	//draw the enemy
	void Draw();

	

	
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

	void SetSpeedX(float a_speedX);
	float GetSpeedX();

	void SetSpeedY(float a_speedY);
	float GetSpeedY();

	void SetLeftMoveExtreme(unsigned int a_leftExtreme);
	unsigned int GetLeftMoveExtreme();

	void SetRightMoveExtreme(unsigned int a_leftExtreme);
	unsigned int GetRightMoveExtreme();



	~Enemy();

private:
	//const float MAX_SPEED_Y = 100.0f;
	unsigned int spriteID;
	float width;
	float height;
	float x;
	float y;
	float speedX;
	//float speedY;
	unsigned int leftMovementExtreme;
	unsigned int rightMovementExtreme;

	

	/*
	check all collisions and apply effects:
	IsCollidedLeftWall - flip speedX and add a speed to speedY else speedY = 0
	IsCollideRighttWall - flip speedX and add a speed to speedY else speedY = 0
	params:
	a_speedY: Speed to set speedY variable to make enemy move along Y axis. Should
	be negative so enemy moves 'down'.
	*/
	void CheckCollisions();

	/*
	check if collided with right extreme (wall) and return true, otherwise return false
	*/
	bool IsCollidedRightWall();

	/*
	check if collided with left extreme (wall) and return true, otherwise return false
	*/
	bool IsCollidedLeftWall();
};
#endif // !_ENEMY_H_


