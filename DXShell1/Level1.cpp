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
	f1 = 0;
	f2 = 0;
	ChangePosition = false;
}


void Level1::Unload()
{
	delete sprites;
}


void Level1::Update()
{
	ySpeed = 20;
	y += ySpeed;
	if (y > 700)
	{
		y = 0;	
		
		ChangePosition = true;		
	}
}

void Level1::Render()
{
	if (ChangePosition)
	{	
		f2++;
		if (f2 == 10)
		{
			f1++;
			f2 = 0;
		}
		
		ChangePosition = false;
	}

	gfx->ClearScreen(0.0f, 0.0f, 0.5f);
	
	sprites->Draw(0, 0);
	gfx->Initialize3dArray();
	gfx->DrawGrid();
	Array3D = gfx->Get3DArray();
	
	
	planet1->Draw(Array3D[f1][f2][0], Array3D[f1][f2][1]);
	//planet2->Draw(100, 100);
	//planet3->Draw(200, 400);
	
	gfx->DrawTriangle(512, y);
	gfx->DeleteArray3D();
	
}