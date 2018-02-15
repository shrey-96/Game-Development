/******************************************************************************************************
*	File:		Level1.cpp																			  *
*	Author:		Shreyansh Tiwari																	  *
*	Date:		14th February, 2018																	  *
*	Purpose:	The pupose of this file is to manipulate the coordinates of spaceship (triangle)	  *
*				inorder to move it from top of screen to the bottom. This also invokes SpriteSheet	  *
*				class to create the bitmaps and draws them onto screen. This file is also responsible *
*				for deciding random position of the planets.										  *
*******************************************************************************************************/

#include "GameController.h"
#include "Graphics.h"
#include "Level1.h"

/****************************************************************************************
	Method:		Load()																	
	Returns:	void																	
	Parameters:	void																	
	Purpose:	The purpose of this method is to invoke the SpriteSheet 				
				class, passing file names all images and pointer to graphics class.		
****************************************************************************************/
void Level1::Load()
{
	y = 0.0f;
	y = ySpeed = 0.0f;
	sprites = new SpriteSheet(L"test.bmp", gfx); //This is where we can specify our file system object!
	planet1 = new SpriteSheet(L"Planet1.bmp", gfx);
	planet2 = new SpriteSheet(L"Planet2.bmp", gfx);
	planet3 = new SpriteSheet(L"Planet3.bmp", gfx);
	fx1 = fy1 = 2;
	fx2 = fy2 = 6;
	fx3 = fy3 = 8;
	ChangePosition = false;

	srand((unsigned int)time(NULL));
}

/************************************************************************************
	Method:		Unload()															
	Returns:	void																
	Parameters:	void																
	Purpose:	The purpose of this method is to delete all initialised classes		
				and hence free up memory.											
*************************************************************************************/
void Level1::Unload()
{
	delete sprites;
	delete planet1;
	delete planet2;
	delete planet3;
}

/***********************************************************************************
	Method:		Update()														   
	Returns:	void															   
	Parameters:	void															   
	Purpose:	The purpose of this method is to update y coordinate of triangle   
				and hence move it from top to the bottom of the screen.			   
************************************************************************************/
void Level1::Update()
{
	ySpeed = 4;
	y += ySpeed;
	if (y > 700)
	{
		y = 0;	
		ChangePosition = true;		
	}
}

/************************************************************************************
	Method:		Update()															
	Returns:	void																
	Parameters:	void																
	Purpose:	The purpose of this method is to generate random indexes to make	
				planet spawn at random positions, and to draw the bitmaps on screen	
				using Graphics class SpriteSheet object								
*************************************************************************************/
void Level1::Render()
{
	// if triangle is back to the top and starting new journey,
	//	get new positions for planet
	if (ChangePosition)
	{	
		// new random position for Planet1
		fx1 = GetRand(10);
		fy1 = GetRand(10);

		// New random position for Planet2
		while (true)
		{
			fx2 = GetRand(10);
			fy2 = GetRand(10);

			// make sure it doesn't overlap with position of first planet
			if (fx2 == fx1 && fy2 == fy1)
				continue;
			else
				break;
		}

		// New random position for Planet3
		while (true)
		{
			fx3 = GetRand(10);
			fy3 = GetRand(10);

			// make sure doesn't overlap with other planet's position
			if ((fx3 == fx1 && fy3 == fy1) || (fx3 == fx2 && fy3 == fy2))
				continue;
			else
				break;
		}

		ChangePosition = false;
	}

	// clear screen
	gfx->ClearScreen(0.0f, 0.0f, 0.5f);
	sprites->Draw(0, 0, 0, 0, 0, 0);		// background

	// initialise array, populate with Grid positions
	gfx->Initialize3dArray();
	gfx->DrawGrid();
	Array3D = gfx->Get3DArray();
	
	
	// draw all the planets
	planet1->Draw(Array3D[fx1][fy1][0], Array3D[fx1][fy1][1], 25, 35, 16, 6);
	planet2->Draw(Array3D[fx2][fy2][0], Array3D[fx2][fy2][1], 25, 35, 16, 6);
	planet3->Draw(Array3D[fx3][fy3][0], Array3D[fx3][fy3][1], 10, 14, 10, 10);
	
	// draw spaceship
	gfx->DrawTriangle(Array3D[5][0][0] + 50, y);

	// delete position array
	gfx->DeleteArray3D();
	
}

/***********************************************************************************
	Method:		GetRand()														  
	Returns:	int - random number															  
	Parameters:	int range - upper range of random number (highest number)															  
	Purpose:	This method takes range as parameter and returns the random number
				between 0 to that range.
************************************************************************************/
int Level1::GetRand(int range)
{
	int randnum = 0;
	randnum = rand() % range;
	return randnum;
}