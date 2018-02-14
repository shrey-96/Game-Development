#include "GameController.h"
#include "Graphics.h"
#include "Level1.h"

void Level1::Load() 
{
	y = 0.0f;
	y = ySpeed = 0.0f;
	sprites = new SpriteSheet(L"test.bmp", gfx); //This is where we can specify our file system object!
	planet1 = new SpriteSheet(L"Planet1.bmp", gfx);
	planet2 = new SpriteSheet(L"Planet2.bmp", gfx);
	planet3 = new SpriteSheet(L"Planet3.bmp", gfx);
}


void Level1::Unload()
{
	delete sprites;
}


void Level1::Update()
{
	ySpeed = 6;
	y += ySpeed;
	if (y > 700)
	{
		y = 0;
	}
}

void Level1::Render()
{
	
	gfx->ClearScreen(0.0f, 0.0f, 0.5f);
	
	sprites->Draw(0, 0);
	gfx->DrawGrid();
	planet1->Draw(10, 30);
	planet2->Draw(200, 400);
	planet3->Draw(700, 200);
	
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