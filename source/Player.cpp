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

	//AddScore(0);

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




//Setters / getters

void Player::SetSpeed(float a_speed)
{
	speed = a_speed;
}

float Player::GetSpeed()
{
	return speed;
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

//int Player::GetScore()
//{
//	return score;
//}
//
//char * Player::GetScoreAsString()
//{
//	return scoreAsString;
//}

Player::~Player()
{
}