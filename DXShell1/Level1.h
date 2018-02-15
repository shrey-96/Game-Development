/******************************************************************************************************
*	Class:		Level1																				  *
*	Author:		Shreyansh Tiwari																	  *
*	Date:		14th February, 2018																	  *
*	Purpose:	The pupose of this file is to manipulate the coordinates of spaceship (triangle)	  *
*				inorder to move it from top of screen to the bottom. This also invokes SpriteSheet	  *
*				class to create the bitmaps and draws them onto screen. This file is also responsible *
*				for deciding random position of the planets.										  *
*******************************************************************************************************/

#pragma once
#include "GameLevel.h"
#include <cstdlib>
#include <ctime>
#include <time.h>


class Level1 : public GameLevel
{
	float y;				// y coordinate of spaceship
	float ySpeed;			// speed of spaceship
	float *** Array3D;		// Array that stores coordinates of grid

	SpriteSheet* sprites;
	SpriteSheet* planet1;
	SpriteSheet* planet2;
	SpriteSheet* planet3;

	// indexes of all planet position that will be passed to Array3D
	int fx1, fy1;
	int fx2, fy2;
	int fx3, fy3;
	bool ChangePosition;


public:
	void Load() override;
	void Unload() override;
	void Update() override;
	void Render() override;

	int GetRand(int range);

};
