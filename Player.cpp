#include "Player.h"

Player::Player()
{
	width = 64;
	height = 32;
	//start position
	x = 50.0f;
	y = 600.0f;

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

void Player::SetMovementExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme)
{
	leftMovementExtreme = a_leftExtreme;
	rightMovementExtreme = a_rightExtreme;
}


/*
Move the player using formula speedX * a_timeStep param with speed being controlled by user input.
params:
a_timeStep - a time delta since last frame
*/
void Player::Move(float a_timeStep)
{
	/*if (IsKeyDown(moveLeftKey))
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
	}*/
	HandleUI();
	x += speed * a_timeStep;
	HandleCollisions();
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}



//Setters / getters

void Player::SetSpriteID(unsigned int a_ID)
{
	spriteID = a_ID;
}

unsigned int Player::GetSpriteID()
{
	return spriteID;
}

void Player::SetWidth(float a_width)
{
	width = a_width;
}

float Player::GetWidth()
{
	return width;
}


void Player::SetHeight(float a_height)
{
	height = a_height;
}

float Player::GetHeight()
{
	return height;
}

void Player::SetSpeed(float a_speed)
{
	speed = a_speed;
}

float Player::GetSpeed()
{
	return speed;
}

void Player::SetX(float a_x)
{
	x = a_x;
}

float Player::GetX()
{
	return x;
}

void Player::SetY(float a_y)
{
	y = a_y;
}

float Player::GetY()
{
	return y;
}

void Player::SetMoveLeftKey(unsigned int a_moveKey)
{
	moveLeftKey = a_moveKey;
}

unsigned int Player::GetLeftMoveKey()
{
	return moveLeftKey;
}

void Player::SetMoveRightgKey(unsigned int a_moveKey)
{
	moveRightKey = a_moveKey;
}

unsigned int Player::GetMoveRightKey()
{
	return moveRightKey;
}

void Player::SetLeftMovementExtreme(unsigned int a_movementExtreme)
{
	leftMovementExtreme = a_movementExtreme;
}

unsigned int Player::GetLeftMovementExtreme()
{
	return leftMovementExtreme;
}

void Player::SetRightMovementExtreme(unsigned int a_movementExtreme)
{
	rightMovementExtreme = a_movementExtreme;
}

unsigned int Player::GetRightMovementExtreme()
{
	return rightMovementExtreme;
}

Player::~Player()
{
}

/*
Set the speed according to user input from left/right move keys
*/
void Player::HandleUI()
{
	if (IsKeyDown(moveLeftKey))
	{
		speed = SPEED_X * -1;
	}
	else if (IsKeyDown(moveRightKey))
	{
		speed = SPEED_X;
	}
	else
	{
		speed = 0;
	}
}

/*
Handle collisions with the right extreme (wall) and left extreme (wall) by stopping player
from going further than max.
*/
void Player::HandleCollisions()
{
	if (x < leftMovementExtreme)
	{
		x = leftMovementExtreme;
	}
	if (x > rightMovementExtreme)
	{
		x = rightMovementExtreme;
	}
}