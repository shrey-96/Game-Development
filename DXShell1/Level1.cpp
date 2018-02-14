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
	fx1 = fy1 = 2;
	fx2 = fy2 = 6;
	fx3 = fy3 = 8;
	ChangePosition = false;

	srand((unsigned int)time(NULL));
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
		ChangePosition = true;		
	}
}

void Level1::Render()
{
	if (ChangePosition)
	{	
		fx1 = GetRand(10);
		fy1 = GetRand(10);

		while (true)
		{
			fx2 = GetRand(10);
			fy2 = GetRand(10);

			if (fx2 == fx1 && fy2 == fy1)
				continue;
			else
				break;
		}

		while (true)
		{
			fx3 = GetRand(10);
			fy3 = GetRand(10);

			if ((fx3 == fx1 && fy3 == fy1) || (fx3 == fx2 && fy3 == fy2))
				continue;
			else
				break;
		}

		ChangePosition = false;
	}

	gfx->ClearScreen(0.0f, 0.0f, 0.5f);
	
	sprites->Draw(0, 0, 0, 0, 0, 0);
	gfx->Initialize3dArray();
	gfx->DrawGrid();
	Array3D = gfx->Get3DArray();
	
	
	planet1->Draw(Array3D[fx1][fy1][0], Array3D[fx1][fy1][1], 25, 35, 16, 6);
	planet2->Draw(Array3D[fx2][fy2][0], Array3D[fx2][fy2][1], 25, 35, 16, 6);
	planet3->Draw(Array3D[fx3][fy3][0], Array3D[fx3][fy3][1], 10, 14, 10, 10);
	
	gfx->DrawTriangle(512, y);
	gfx->DeleteArray3D();
	
}

int Level1::GetRand(int range)
{
	int randnum = 0;
	randnum = rand() % range;
	return randnum;
}