/****************************************************************************************
*	Class:		GameController															*
*	Author:		Shreyansh Tiwari														*
*	Date:		14th February, 2018														*
*	Purpose:	The main purpose of this class is to render the screen with new			*
*				dataset/updated dataset. This invokes graphics class to get access		*
*				to rendertarget. This class also deals with the game level and 			*
*				change/switch of game level and makes sure loading is not interrupted	*
*				due to switch/update.													*
*****************************************************************************************/

#pragma once

#include "GameLevel.h"
#include "Graphics.h"

class GameController
{
	GameController() {}
	static GameLevel* currentLevel;
public:
	static bool Loading;
	static void Init();
	static void LoadInitialLevel(GameLevel* lev);
	static void SwitchLevel(GameLevel* lev);
	static void Render();
	static void Update();
};