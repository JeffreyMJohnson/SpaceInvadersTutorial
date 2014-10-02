#include "Bullet.h"


Bullet::Bullet()
{
	x = 0,
		y = 0;
	velocityX = 0;
	velocityY = 0;
	textureId = 0;
	isActive = false;
}

void Bullet::Update(float a_delta)
{
	x += velocityX * a_delta;
	y += velocityY * a_delta;

	if (y > 1000)
	{
		isActive = false;
	}
}

void Bullet::Draw()
{
	MoveSprite(textureId, x, y);
	DrawSprite(textureId);
	
}

void Bullet::InitializeBullet(float a_x, float a_y, float a_velocityX, float a_velocity_y, unsigned int a_textureId)
{
	x = a_x;
	y = a_y;
	velocityX = a_velocityX;
	velocityY = a_velocity_y;
	textureId = a_textureId;

	isActive = true;
}

Bullet::~Bullet()
{
}