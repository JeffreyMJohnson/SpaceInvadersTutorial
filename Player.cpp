#include "Player.h"

Player::Player()
{
	width = 64;
	height = 32;
	//start position
	x = 50.0f;
	y = 600.0f;

	currentReloadBulletTime = 0.0f;
	maxBulletReloadTime = .25f;

	AddScore(0);

}

//void Player::SetSize(float a_width, float a_height)
//{
//	width = a_width;
//	height = a_height;
//}
//
//void Player::SetPosition(float a_x, float a_y)
//{
//	x = a_x;
//	y = a_y;
//}

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

void Player::Update(float a_delta)
{
	if (IsKeyDown(moveLeftKey))
	{
		x -= a_delta * speed;
		if (x < (leftMovementExtreme + width * 0.5f))
		{
			x = (leftMovementExtreme + width * 0.5f);
		}
	}

	if (IsKeyDown(moveRightKey))
	{
		x += a_delta * speed;
		if (x >(rightMovementExtreme - width * 0.5f))
		{
			x = (rightMovementExtreme - width * 0.5f);
		}
	}

}

void Player::Draw()
{
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}

/*
Move the player using formula speedX * a_timeStep param with speed being controlled by user input.
params:
a_timeStep - a time delta since last frame
*/
//void Player::Move(float a_timeStep)
//{
//	HandleUI();
//	x += speed * a_timeStep;
//	HandleCollisions();
//	MoveSprite(spriteID, x, y);
//	DrawSprite(spriteID);
//}

/*
Get inactive bullet from bullets array (if any) and initialize with player's current position.
*/
void Player::Shoot(unsigned int a_textureID, float _a_delta)
{
	if (IsKeyDown(shootKey) && currentReloadBulletTime >= maxBulletReloadTime)
	{
		GetInactiveBullet().InitializeBullet(x, y, 0, 500, a_textureID);
		currentReloadBulletTime = 0.0f;
	}
	currentReloadBulletTime += _a_delta;
	
}

/*
Returns reference to first Bullet object in bullets array that is not active. If all are active
returns the first bullet in the array.
*/
Bullet& Player::GetInactiveBullet()
{
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (!bullets[i].isActive)
		{
			return bullets[i];
		}
	}

	return bullets[0];
}

/*
Add a score of the given param to the player's score.
param:
a_score - int to add to player's score.
*/
void Player::AddScore(int a_score)
{
	score += a_score;
	char buff[6];
	sprintf(buff, "%05d", score);
	strcpy(scoreAsString, buff);
}


//Setters / getters

//void Player::SetSpriteID(unsigned int a_ID)
//{
//	spriteID = a_ID;
//}
//
//unsigned int Player::GetSpriteID()
//{
//	return spriteID;
//}
//
//void Player::SetWidth(float a_width)
//{
//	width = a_width;
//}
//
//float Player::GetWidth()
//{
//	return width;
//}
//
//
//void Player::SetHeight(float a_height)
//{
//	height = a_height;
//}
//
//float Player::GetHeight()
//{
//	return height;
//}

void Player::SetSpeed(float a_speed)
{
	speed = a_speed;
}

float Player::GetSpeed()
{
	return speed;
}

//void Player::SetX(float a_x)
//{
//	x = a_x;
//}
//
//float Player::GetX()
//{
//	return x;
//}
//
//void Player::SetY(float a_y)
//{
//	y = a_y;
//}
//
//float Player::GetY()
//{
//	return y;
//}

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

void Player::SetShootKey(unsigned int a_shootKey)
{
	shootKey = a_shootKey;
}

unsigned int Player::GetShootKey()
{
	return shootKey;
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

int Player::GetScore()
{
	return score;
}

char * Player::GetScoreAsString()
{
	return scoreAsString;
}

Player::~Player()
{
}

/*
Set the speed according to user input from left/right move keys
*/
//void Player::HandleUI()
//{
//	if (IsKeyDown(moveLeftKey))
//	{
//		speed = SPEED_X * -1;
//	}
//	else if (IsKeyDown(moveRightKey))
//	{
//		speed = SPEED_X;
//	}
//	else
//	{
//		speed = 0;
//	}
//}

/*
Handle collisions with the right extreme (wall) and left extreme (wall) by stopping player
from going further than max.
*/
//void Player::HandleCollisions()
//{
//	if (x < leftMovementExtreme)
//	{
//		x = leftMovementExtreme;
//	}
//	if (x > rightMovementExtreme)
//	{
//		x = rightMovementExtreme;
//	}
//}