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

void Enemy::Draw()
{
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}

void Enemy::SetSpeed(float a_speedX)
{
	speed = a_speedX;
}

float Enemy::GetSpeed()
{
	return speed;
}

void Enemy::SetDirection(int a_direction)
{
	direction = a_direction;
}

int Enemy::GetDirection()
{
	return direction;
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
