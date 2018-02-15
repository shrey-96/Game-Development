/************************************************************************************
*	Class:		Graphics															*
*	Author:		Shreyansh Tiwari													*
*	Date:		14th February, 2018													*
*	Purpose:	The main purpose of this class is to manage rendertarget, create 	*
*				triangle, clear screen, draw invisible grid, store it in three		*
*				dimensional float array for other classes to access it.				*
*************************************************************************************/

#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <d2d1.h>


class Graphics
{
	ID2D1Factory* factory; 
	ID2D1HwndRenderTarget* rendertarget; 
	ID2D1SolidColorBrush* brush;
	HRESULT hr;
	float*** array3d = 0;
	
public:
	Graphics();

	~Graphics();

	bool Init(HWND windowHandle);

	// accessor for render target
	ID2D1RenderTarget* GetRenderTarget()
	{
		return rendertarget;
	}

	// begin draw
	void BeginDraw() { rendertarget->BeginDraw(); }

	// end draw
	void EndDraw() { rendertarget->EndDraw(); }

	// clear output window screen
	void ClearScreen(float r, float g, float b);
	
	void DrawTriangle(float fc, float sc);
	void DrawGrid();

	// Manage 3d array with all our grid locations
	void Initialize3dArray();
	void DeleteArray3D();
	float*** Get3DArray();
};
