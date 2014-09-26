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

//move the enemy 
void Enemy::Move(float a_deltaTime)
{
	CheckCollisions();

	x += speedX * a_deltaTime;
	//y += speedY * a_deltaTime;

	MoveSprite(spriteID, x, y);

	//float move = 100.0f;
	//if (a_direction == LEFT)
	//{
	//	//move left 
	//	x -= a_deltaTime * speedX;
	//	//x -= move;
	//	MoveSprite(spriteID, x, y);
	//	if (x < leftMovementExtreme + width / 2)
	//	{
	//		x = leftMovementExtreme + width / 2;
	//		MoveSprite(spriteID, x, y);
	//		return true;
	//	}
	//}
	//if (a_direction == RIGHT)
	//{
	//	//move right
	//	x += a_deltaTime * speed;
	//	//x += move;
	//	MoveSprite(spriteID, x, y);
	//	if (x > rightMovementExtreme - width / 2)
	//	{
	//		x = rightMovementExtreme - width / 2;
	//		MoveSprite(spriteID, x, y);
	//		return true;
	//	}
	//}
	//if (a_direction == DOWN)
	//{
	//	//move towards planet
	//	y -= height;
	//	//y -= move;
	//	MoveSprite(spriteID, x, y);
	//	if (y < 0 + height / 2)
	//	{
	//		y = 0 + height / 2;
	//		MoveSprite(spriteID, x, y);
	//	}
	//	return false;
	//}
	//return false;
}

//draw the enemy
void Enemy::Draw()
{
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
	}/*
	else
	{
		speedY = 0.0f;
	}*/

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

//void Enemy::SetSpeedY(float a_speed)
//{
//	speedY = a_speed;
//}
//
//float Enemy::GetSpeedY()
//{
//	return speedY;
//}

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
