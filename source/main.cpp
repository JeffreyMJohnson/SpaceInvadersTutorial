#include "AIE.h"

const int screenWidth = 672;
const int screenHeight = 780;
const int playerCannonWidth = 64;
const int playerCannonHeight = 32;
const float playerCannonYPos = 40.0f;

int main(int argcx, char* argv[])
{
	Initialise(screenWidth, screenHeight, false, "Space Invaders Clone");

	unsigned int playerCannon = CreateSprite("./images/cannon.png", playerCannonWidth, playerCannonHeight, true);

	MoveSprite(playerCannon, screenWidth *0.5f, playerCannonYPos);

	do
	{
		ClearScreen();
		DrawSprite(playerCannon);
	} while (!FrameworkUpdate());
	
	Shutdown();

	return 0;
}