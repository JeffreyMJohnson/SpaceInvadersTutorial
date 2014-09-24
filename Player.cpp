#include "Player.h"
#include "AIE.h"


Player::Player()
{
}

void Player::SetSize(float a_width, float a_height)
{
	width = a_width;
	height = a_height;
}

void Player::SetPosition(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}

void Player::SetMovementKeys(unsigned int a_moveLeft, unsigned int a_moveRight)
{
	moveLeftKey = a_moveLeft;
	moveRightKey = a_moveRight;
}

void Player::setMovementExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme)
{
	leftMovementExtreme = a_leftExtreme;
	rightMovementExtreme = a_rightExtreme;
}

void Player::Move(float a_timeStep)
{
	if (IsKeyDown(moveLeftKey))
	{
		x -= a_timeStep * speed;
		if (x < (leftMovementExtreme + width / 2))
		{
			x = (leftMovementExtreme + width / 2);
		}
	}
	if (IsKeyDown(moveRightKey))
	{
		x += a_timeStep * speed;
		if (x >(rightMovementExtreme - width / 2))
		{
			x = (rightMovementExtreme - width / 2);
		}
	}
	MoveSprite(spriteID, x, y);
}

Player::~Player()
{
}
