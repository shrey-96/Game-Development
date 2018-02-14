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
		what++;
		y = 0;
		ChangePosition = true;
		
	}
}

void Level1::Render()
{
	if (ChangePosition)
	{
		for (int k = 0; k < 10; k++)
		{
			srand(time(NULL));
			rand1 = rand() % 94 + 1;

			srand(time(NULL));
			rand2 = rand() % 95 + 2;

			srand(time(NULL));
			rand3 = rand() % 96 + 1;
		}

		
		ChangePosition = false;
	}

	gfx->ClearScreen(0.0f, 0.0f, 0.5f);
	
	sprites->Draw(0, 0);
	gfx->InitializeArray();
	gfx->DrawGrid();
	ArrayofPoints = gfx->GridArray();
		
	
	//  ArrayofPoints[rand1][0], ArrayofPoints[rand1][1]
	//	ArrayofPoints[rand2][0], ArrayofPoints[rand2][1]
	//	ArrayofPoints[rand3][0], ArrayofPoints[rand3][1]
	planet1->Draw(ArrayofPoints[what][0], ArrayofPoints[what][1]);
	planet2->Draw(ArrayofPoints[rand2][0], ArrayofPoints[rand2][1]);
	planet3->Draw(ArrayofPoints[rand3][0], ArrayofPoints[rand3][1]);
	
	gfx->DrawTriangle(512, y);
	DeleteArray();
	
}

void Level1::DeleteArray()
{
	for (int i = 0; i < 100; i++)
	{
		delete[] ArrayofPoints[i];
	}

delete[] ArrayofPoints;
}



// back up
//ySpeed = 10.0f;
//y += ySpeed;
//if (y > 600)
//{
//	y = 50; //keep the ball from dropping below the screen
//			//ySpeed = -30.0f; //What does this do?
//}