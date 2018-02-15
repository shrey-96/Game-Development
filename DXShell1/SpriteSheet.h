/********************************************************************************************
*	File:		SpriteSheeet.cpp															*
*	Author:		Shreyansh Tiwari															*
*	Date:		14th February, 2018															*
*	Purpose:	This a header for SpriteSheet class, it contains all the method prototypes	*
*				private variables declaration												*
*********************************************************************************************/

#pragma once

#include <wincodec.h> // wic coder header
#include "Graphics.h" 

class SpriteSheet
{
	Graphics* gfx; //Reference to the Graphics class
	ID2D1Bitmap* bmp; //This will hold our loaded and converted Bitmap file

public:
	//Constructor
	SpriteSheet(wchar_t* filename, Graphics* gfx);

	//Destructor
	~SpriteSheet();

	//Draw bitmap to the render target
	void Draw(float x, float y, float swt, float sht, float wcentre, float hcentre);
};