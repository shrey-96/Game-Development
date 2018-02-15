/************************************************************************************
*	Class:		GameLevel															*
*	Author:		Shreyansh Tiwari													*
*	Date:		14th February, 2018													*
*	Purpose:	The main purpose of this class is to initialise and hold			*
*				the level for the class, which is then used by other classes		*
*				such as GameController.												*
*************************************************************************************/

#pragma once

#include "Graphics.h"
#include "SpriteSheet.h"

class GameLevel
{
protected:
	static Graphics* gfx;

public:

	// initialise level
	static void Init(Graphics* graphics)
	{
		gfx = graphics;
	}

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};