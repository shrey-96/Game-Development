#include "GameController.h"
#include "Graphics.h"
#include "Level1.h"

void Level1::Load() 
{
	y = 0.0f;
	y = ySpeed = 0.0f;
	sprites = new SpriteSheet(L"test.bmp", gfx); //This is where we can specify our file system object!
}


void Level1::Unload()
{
	delete sprites;
}


void Level1::Update()
{
	ySpeed = 6.0f;
	y += ySpeed;
	if (y > 700)
	{
		y = 0;
	}
}

void Level1::Render()
{
	
	gfx->ClearScreen(0.0f, 0.0f, 0.5f);
	sprites->Draw();
	gfx->DrawTriangle(512, y);	
	
}



// back up
//ySpeed = 10.0f;
//y += ySpeed;
//if (y > 600)
//{
//	y = 50; //keep the ball from dropping below the screen
//			//ySpeed = -30.0f; //What does this do?
//}