#include "Enemy.h"


Enemy::Enemy()
{
	isActive = true;
}

void Enemy::Update(float a_delta)
{
	if (isActive)
	{
		x += speed * direction * a_delta;
	}
}

void Enemy::setMovementExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme)
{
	leftMovementExtreme = a_leftExtreme;
	rightMovementExtreme = a_rightExtreme;
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
	if (isActive)
	{
		MoveSprite(spriteID, x, y);
		DrawSprite(spriteID);
	}

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
		speed *= -1;
		y -= height / 2;
		MoveSprite(spriteID, x, y);
	}
}


// SETTERS / GETTERS

void Enemy::SetDirection(int a_direction)
{
	direction = a_direction;
}

int Enemy::GetDirection()
{
	return direction;
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

void Enemy::SetScoreValue(int a_scoreValue)
{
	scoreValue = a_scoreValue;
}

int Enemy::GetScoreValue()
{
	return scoreValue;
}

void Enemy::SetIsActive(bool a_isActive)
{
	isActive = a_isActive;
}

bool Enemy::GetIsActive()
{
	return isActive;
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
