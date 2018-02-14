#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <d2d1.h>

class Graphics
{
	//Below, these are all COM interfaces we're using to create D2D resources.
	//We release them as part of the ~Graphics deconstructor... or bad things can happen
	ID2D1Factory* factory; //The factory allows us to create many other types of D2D resources
	ID2D1HwndRenderTarget* rendertarget; //this is typically an area in our GPU memory.. like a back buffer 
	ID2D1SolidColorBrush* brush; //Note this COM interface! Remember to release it!
	HRESULT hr;
	float*** array3d = 0;
	
public:
	Graphics();

	~Graphics();

	bool Init(HWND windowHandle);

	ID2D1RenderTarget* GetRenderTarget()
	{
		return rendertarget;
	}

	
	void BeginDraw() { rendertarget->BeginDraw(); }
	void EndDraw() { rendertarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float c, float y, float radius, float r, float g, float b, float a);
	
	void DrawTriangle(float fc, float sc);
	void DrawGrid();

	void Initialize3dArray();
	void DeleteArray3D();
	float*** Get3DArray();
	// Hrmmm... r, g, b, a? Where do we know these from?
};
