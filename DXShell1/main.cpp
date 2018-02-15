/*********************************************************************************
*	File:		main.cpp														 *
*	Author:		Shreyansh Tiwari												 *
*	Date:		14th February, 2018												 *
*	Purpose:	This file invokes sets the attribute of main window, and it		 *
*				invokes other classes such as gamecontroller for rendering		 *
*				graphics for rendertarget, and level1 for game logic.			 *
*				This file consist of infinite loop that keeps the game running	 *
*				until interrupted.												 *
**********************************************************************************/

#include <Windows.h>
#include "Graphics.h"
#include "Level1.h"
#include "GameController.h"

Graphics* graphics;

LRESULT CALLBACK WindowProc(
	HWND hwnd,		// window handler
	UINT uMsg,		// message sent by gameloop
	WPARAM wParam,
	LPARAM lParam )
{
	if (uMsg == WM_DESTROY) { PostQuitMessage(0); return 0; }
	
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPWSTR cmd,
	int nCmdShow
)
{
	// define attributes for our main window
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));	// clear the struct before using it
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = "MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW; 

	// register our window
	RegisterClassEx(&windowclass);


	// define resolution of main window
	RECT rect = { 0, 0, 1024, 768 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPED, false, WS_EX_OVERLAPPEDWINDOW);

	// create window using values in struct above of 1024x768 resolution
	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "DirectXShell1", WS_OVERLAPPEDWINDOW, 100, 100, 
		rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);
	if (!windowhandle) return -1;

	// instantiate graphics class
	graphics = new Graphics();
	if (!graphics->Init(windowhandle))
	{
		delete graphics;
		return -1;
	}

	// initialise graphics and display window
	GameLevel::Init(graphics);
	ShowWindow(windowhandle, nCmdShow);
	GameController::LoadInitialLevel(new Level1());

#pragma region GameLoop
	

	// run infinite game loop here
	MSG message;
	message.message = WM_NULL; 
	while (message.message != WM_QUIT)
	{
		// check if any pending message, send if any
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			DispatchMessage(&message);
		else
		{
			// update game attributes
			GameController::Update();

			// draw the assets to the screen
			graphics->BeginDraw();
			GameController::Render();
			graphics->EndDraw();

		}
	}

	// once loop is stopped, delete the graphics and free memory
#pragma endregion
	delete graphics;
	return 0;
}