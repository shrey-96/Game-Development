#include "Graphics.h"

/***********************************************************************************
The intent of the Graphics class is to handle our DirectX calls, and to be largely responsible 
for managing the rendertarget.
******************************************************************************************/


//Constructor for Graphics class
Graphics::Graphics()
{
	factory = NULL;
	rendertarget = NULL;
	brush = NULL;
}

//Destructor for Graphics class
//Note that all COM objects we instantiate should be 'released' here 
//Look for comments on COM usage in the corresponding header file.

Graphics::~Graphics()
{
	if (factory) factory->Release();
	if (rendertarget) rendertarget->Release();
	if (brush) brush->Release();
}

//Provide some comments for each of the methods below.
//Be sure you get a sense of what is happening, and resolve any issues you have understanding these
// methods, their parameters, returns and so on.
bool Graphics::Init(HWND windowHandle)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect); //set the rect's right and bottom properties = the client window's size

	res = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&rendertarget);

	hr = res;
	if (res != S_OK) return false;
	
	res = rendertarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
	if (res != S_OK) return false;
	return true;
}

void Graphics::ClearScreen(float r, float g, float b) 
{
	rendertarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	rendertarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);	
}

void Graphics::DrawGrid()
{
	D2D1_SIZE_F rtSize = rendertarget->GetSize();

	// Draw a grid background.
	float width = rtSize.width;
	float height = rtSize.height;
	float gridheight = height / 10;
	float gridwidth = width / 10;

	//int count = 0;
	float x = 0;
	float y = 0;
	for (int count = 0; count < 10; count++)
	{
		
		
	
		rendertarget->DrawLine(
			D2D1::Point2F((float)x, 0.0f),
			D2D1::Point2F((float)x, rtSize.height),
			brush,
			0.5f
		);

		for (int i = 0; i < 10; i++)
		{		
			array3d[count][i][0] = x;
			array3d[count][i][1] = y;
			y += gridheight;
		}
		x += gridwidth;

		y = 0;				
	}

	y = 0;
	for (int count = 0; count < 10; count++)
	{
		y += gridheight;

		rendertarget->DrawLine(
			D2D1::Point2F(0.0f, y),
			D2D1::Point2F(rtSize.width, y),
			brush,
			0.5f
		);	
	}	
}

void Graphics::DrawTriangle(float fc, float sc)
{
	ID2D1GeometrySink *pSink = NULL;
	ID2D1PathGeometry *trigeo = NULL;

	hr = factory->CreatePathGeometry(&trigeo);
	hr = trigeo->Open(&pSink);

	pSink->SetFillMode(D2D1_FILL_MODE_WINDING);

	pSink->BeginFigure(
		D2D1::Point2F(fc, sc),
		D2D1_FIGURE_BEGIN_FILLED
	);
	D2D1_POINT_2F points[2] = {
		D2D1::Point2F(fc - 30, sc - 50),
		D2D1::Point2F(fc + 30, sc - 50)
	};

	pSink->AddLines(points, ARRAYSIZE(points));
	pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

	hr = pSink->Close();

	pSink->Release();

	brush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGreen, 1.f));
	rendertarget->FillGeometry(trigeo, brush);

	brush->SetColor(D2D1::ColorF(D2D1::ColorF::Green, 1.f));
	rendertarget->DrawGeometry(trigeo, brush, 1.f);
}

void Graphics::Initialize3dArray()
{
	int row = 10;
	int col = 10;
	int atr = 2;

	array3d = new float**[row];

	for (int i = 0; i < row; i++)
	{
		array3d[i] = new float*[col];

		for (int k = 0; k < col; k++)
		{
			array3d[i][k] = new float[atr];
		}
	}
}

float*** Graphics::Get3DArray()
{
	return array3d;
}

void Graphics::DeleteArray3D()
{
	int row = 10;
	int col = 10;
	int atr = 2;

	for (int i = 0; i < row; i++)
	{

		for (int k = 0; k < col; k++)
		{
			delete[] array3d[i][k];
		}

		delete[] array3d[i];
	}
	delete[] array3d;
}

