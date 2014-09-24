#pragma once
class Player
{
public:
	Player();


	void SetSize(float a_width, float a_height);
	void SetPosition(float a_x, float a_y);
	void SetMovementKeys(unsigned int a_moveLeft, unsigned int a_moveRight);
	void setMovementExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme);
	void Move(float a_timeStep);


	//standard setters/getters
	void SetSpriteID(unsigned int a_ID);
	unsigned int GetSpriteID();

	void SetWidth(int a_width);
	int GetWidth();

	void SetHeight(int a_height);
	int GetHeight();

	void SetSpeed(float a_speed);
	float GetSpeed();

	void SetX(float a_x);
	float GetX();

	void SetY(float a_y);
	float GetY();

	void SetMoveLeftKey(unsigned int a_moveKey);
	unsigned int GetLeftMoveKey();

	void SetMoveRightgKey(unsigned int a_moveKey);
	unsigned int GetRightMoveKey();

	void SetLeftMovementExtreme(unsigned int a_movementExtreme);
	unsigned int GetLeftMovementExtreme();

	void SetRightMovementExtreme(unsigned int a_movementExtreme);
	unsigned int GetRightMovementExtreme();

	~Player();
	
private:
	unsigned int spriteID;
	float width;
	float height;
	float speed = 500.0f;
	float x;
	float y;
unsigned int moveLeftKey;
	unsigned int moveRightKey;
unsigned int leftMovementExtreme;
	unsigned int rightMovementExtreme;

};

