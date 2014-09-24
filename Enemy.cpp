#include "Enemy.h"


Enemy::Enemy()
{
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

bool Enemy::move(float a_deltaTime, int a_direction)
{
	float move = 100.0f;
	if (a_direction == LEFT)
	{
		//move left 
		x -= a_deltaTime * speed;
		//x -= move;
		MoveSprite(spriteID, x, y);
		if (x < leftMovementExtreme + width / 2)
		{
			x = leftMovementExtreme + width / 2;
			MoveSprite(spriteID, x, y);
			return true;
		}
	}
	if (a_direction == RIGHT)
	{
		//move right
		x += a_deltaTime * speed;
		//x += move;
		MoveSprite(spriteID, x, y);
		if (x > rightMovementExtreme - width / 2)
		{
			x = rightMovementExtreme - width / 2;
			MoveSprite(spriteID, x, y);
			return true;
		}
	}
	if (a_direction == DOWN)
	{
		//move towards planet
		y -= height;
		//y -= move;
		MoveSprite(spriteID, x, y);
		if (y < 0 + height / 2)
		{
			y = 0 + height / 2;
			MoveSprite(spriteID, x, y);
		}
		return false;
	}
	return false;
}

//setters/getters
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

void Enemy::SetSpeed(float a_speed)
{
	speed = a_speed;
}

float Enemy::GetSpeed()
{
	return speed;
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

Enemy::~Enemy()
{
}
