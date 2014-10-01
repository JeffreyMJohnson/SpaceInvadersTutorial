#include "Enemy.h"


Enemy::Enemy()
{
	isActive = true;
}

//Helper functions

void Enemy::setMovementExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme)
{
	leftMovementExtreme = a_leftExtreme;
	rightMovementExtreme = a_rightExtreme;
}

void Enemy::SetSize(float a_width, float a_height)
{
	width = a_width;
	height = a_height;
}

void Enemy::SetPosition(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}

//move the enemy 
void Enemy::Move(float a_speed, int a_direction, float a_delta)
{
	//changed like lecture example
	x += a_speed * a_direction * a_delta;


}

//draw the enemy
void Enemy::Draw()
{
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}

/*
check all collisions and apply effects:
IsCollidedLeftWall - flip speedX and add a speed to speedY else speedY = 0
IsCollideRighttWall - flip speedX and add a speed to speedY else speedY = 0
params:
a_speedY: Speed to set speedY variable to make enemy move along Y axis. Should
be negative so enemy moves 'down'.
*/
void Enemy::CheckCollisions()
{
	if (IsCollidedLeftWall() || IsCollidedRightWall())
	{
		speedX *= -1;
		y -= height / 2;
		MoveSprite(spriteID, x, y);
	}
}


// SETTERS / GETTERS

void Enemy::SetSpriteID(unsigned int a_spriteID)
{
	spriteID = a_spriteID;
}

unsigned int Enemy::GetSpriteID()
{
	return spriteID;
}

void Enemy::SetWidth(float a_width)
{
	width = a_width;
}

float Enemy::GetWidth()
{
	return width;
}

void Enemy::SetHeight(float a_height)
{
	height = a_height;
}

float Enemy::GetHeight()
{
	return height;
}

void Enemy::SetX(float a_x)
{
	x = a_x;
}

float Enemy::GetX()
{
	return x;
}

void Enemy::SetY(float a_y)
{
	y = a_y;
}

float Enemy::GetY()
{
	return y;
}

void Enemy::SetSpeedX(float a_speed)
{
	speedX = a_speed;
}

float Enemy::GetSpeedX()
{
	return speedX;
}

void Enemy::SetLeftMoveExtreme(unsigned int a_leftExtreme)
{
	leftMovementExtreme = a_leftExtreme;
}

unsigned int Enemy::GetLeftMoveExtreme()
{
	return leftMovementExtreme;
}

void Enemy::SetRightMoveExtreme(unsigned int a_righttExtreme)
{
	rightMovementExtreme = a_righttExtreme;
}

unsigned int Enemy::GetRightMoveExtreme()
{
	return rightMovementExtreme;
}

void Enemy::SetScoreValue(int a_scoreValue)
{
	scoreValue = a_scoreValue;
}

int Enemy::GetScoreValue()
{
	return scoreValue;
}

Enemy::~Enemy()
{
}


//PRIVATE FUNCTIONS

/*
check if collided with right extreme (wall) and return true, otherwise return false
*/
bool Enemy::IsCollidedRightWall()
{
	if (x >= rightMovementExtreme)
	{
		x = rightMovementExtreme;
		return true;
	}
	return false;
}

/*
check if collided with left extreme (wall) and return true, otherwise return false
*/
bool Enemy::IsCollidedLeftWall()
{
	if (x <= leftMovementExtreme)
	{
		x = leftMovementExtreme;
		return true;
	}
	return false;
}
