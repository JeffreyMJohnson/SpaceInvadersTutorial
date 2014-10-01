#pragma once
#ifndef _ENTITY_H_
class Entity
{
public:
	Entity();

	void SetSize(float a_width, float a_height);
	void SetPosition(float a_x, float a_y);

	virtual void Update(float a_delta) = 0;
	virtual void Draw() = 0;

	void SetSpriteId(unsigned int a_spriteID);
	unsigned int GetSpriteID();

	void SetWidth(float a_width);
	float GetWidth();

	void SetHeight(float a_height);
	float GetHeight();

	void SetX(float a_x);
	float GetX();

	void SetY(float a_y);
	float GetY();

	~Entity();

protected:
	unsigned int spriteID;
	float width;
	float height;
	float x;
	float y;
};
#endif // !_ENTITY_H_
