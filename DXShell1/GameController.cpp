
#include "GameController.h"


GameLevel* GameController::currentLevel;
bool GameController::Loading;

/**********************************************************
	Method:		Init()
	Type:		Initialiser
	Purpose:	Initialises data members of current class.
***********************************************************/
void GameController::Init()
{
	Loading = true;
	currentLevel = 0;
}

/**********************************************************************
	Method:		LoadInitialLevel
	Parameter:	Gamelevel* lev:		pointer to current game level
	Purpose:	It takes the currnet gamelevel as reference and loads
				game for that level.
***********************************************************************/
void GameController::LoadInitialLevel(GameLevel* lev)
{
	Loading = true;
	currentLevel = lev;
	currentLevel->Load();
	Loading = false;
}

/**********************************************************************
	Method:		SwitchLevel
	Parameter:	Gamelevel* lev:		pointer to new game level
	Purpose:	It takes the new game level as parameter and switches
				current context of game to that level.
***********************************************************************/
void GameController::SwitchLevel(GameLevel* lev)
{
	Loading = true;

	// unload current level first
	currentLevel->Unload();

	// load new level
	lev->Load();

	// delete previous level before redefining variable
	delete currentLevel;
	currentLevel = lev;
	Loading = false;
}


/**************************************************************************
	Method:		Render
	Parameter:	void
	Purpose:	This method renders the current game level on to screen.
***************************************************************************/
void GameController::Render()
{
	if (Loading) 
		return;
	currentLevel->Render();
}

/***********************************************************
Method:		Update
Parameter:	void
Purpose:	This method updates the data of game level.
***********************************************************/
void GameController::Update()
{
	if (Loading) 
		return; 
	currentLevel->Update();
}