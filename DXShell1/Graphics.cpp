#include "Graphics.h"
/*******************************************************
	 Method:		Graphics()						   
	 Type:			Contructor						   
	 Purpose:		Initialise the private variables   
********************************************************/
Graphics::Graphics()
{
	factory = NULL;
	rendertarget = NULL;
	brush = NULL;
}

/*******************************************************
	 Method:		~Graphics()
	 Type:			Destructor
	 Purpose:		Release the private variables
********************************************************/
Graphics::~Graphics()
{
	if (factory) factory->Release();
	if (rendertarget) rendertarget->Release();
	if (brush) brush->Release();
}

/**********************************************************************************
	Method:		Init()
	Parameter:	HWND windowhandle - reference to our main window (output window)
	Return:		true or false based on success of initialisation 
	Purpose:	The purpose of this method is to initialise the main window, with 
				its resolution and color.
***********************************************************************************/
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

/****************************************************************
	Method:		ClearScreen()
	Parameters:	r - red ratio, g - green ratio, b - blue ratio	
	Purpose:	Clears the screen.
*****************************************************************/
void Graphics::ClearScreen(float r, float g, float b) 
{
	rendertarget->Clear(D2D1::ColorF(r, g, b));
}

/********************************************************************************
	Method:		DragGrid()
	Parameter:	void
	Return:		void
	Purpose:	This method gets the resolution (width and height), and divide 
				it by 10 to get the x and y coordinate of each grid (imaginary)
				It also stores all of them in the private 3d float array, 
				which has accessor to allow other classes to access it.
	Reference:	MSDN
*********************************************************************************/
void Graphics::DrawGrid()
{
	D2D1_SIZE_F rtSize = rendertarget->GetSize();

	// Draw a grid background.
	float gridheight = rtSize.height / 10;
	float gridwidth = rtSize.width / 10;

	//int count = 0;
	float x = 0;
	float y = 0;
	
	for (int count = 0; count < 10; count++)
	{
		// iterate through all possible combinations 
		// of grid coordinates and store them in 3d array
		for (int i = 0; i < 10; i++)
		{		
			array3d[count][i][0] = x;
			array3d[count][i][1] = y;

			// increment grid height to get next y coordinate
			y += gridheight;
		}

		// increment grid width to get next x coordinate
		x += gridwidth;

		// reset y
		y = 0;				
	}

	y = 0;	
}


/********************************************************************************
	Method:		DrawTriangle()
	Parameter:	float fc, float sc --> coordinates of vertex of triangle
	Return:		void
	Purpose:	This method gets the vertex coordinates as parameters and 
				draws the triangle filled with green color. Once the triangle
				is drawn, it releases all the pointer variables.
	Reference:	MSDN
*********************************************************************************/
void Graphics::DrawTriangle(float fc, float sc)
{
	ID2D1GeometrySink *pSink = NULL;
	ID2D1PathGeometry *trigeo = NULL;

	
	hr = factory->CreatePathGeometry(&trigeo);
	hr = trigeo->Open(&pSink);

	
	pSink->SetFillMode(D2D1_FILL_MODE_WINDING);

	// begin figure with vertex and join it to other coordinates later
	pSink->BeginFigure(
		D2D1::Point2F(fc, sc),
		D2D1_FIGURE_BEGIN_FILLED
	);

	// array of points that joins vertex
	D2D1_POINT_2F points[2] = {
		D2D1::Point2F(fc - 35, sc - 40),
		D2D1::Point2F(fc + 35, sc - 40)
	};

	// add lines to join the coordinates
	pSink->AddLines(points, ARRAYSIZE(points));

	pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

	// close the geometry now that it is done
	hr = pSink->Close();

	pSink->Release();

	// set color to fill the figure
	brush->SetColor(D2D1::ColorF(D2D1::ColorF::ForestGreen, 1.f));
	rendertarget->FillGeometry(trigeo, brush);

	brush->SetColor(D2D1::ColorF(D2D1::ColorF::Green, 1.f));
	rendertarget->DrawGeometry(trigeo, brush, 1.f);
}

/****************************************************************************************
	Method:		Initialize3dArray()
	Parameter:	void
	Return:		void
	Purpose:	This method initialises the 3d array that stores all grid coordinates
				with 10*10*2 values.
*****************************************************************************************/
void Graphics::Initialize3dArray()
{
	// 3d array of 10*10*2 
	int row = 10;
	int col = 10;
	int atr = 2;

	// initialise by 10
	array3d = new float**[row];

	for (int i = 0; i < row; i++)
	{
		// by 10 again 
		array3d[i] = new float*[col];

		for (int k = 0; k < col; k++)
		{
			// by 2 now
			array3d[i][k] = new float[atr];
		}
	}
}

/*******************************************************************************
	Method:		Get3DArray
	Type:		Accessor
	Parameter:	void
	Return:		array3d - pointer to private 3d float array
	Purpose:	Since this method is an accessor, it returns the pointer to
				array3d - which is private variable that stores all the points
				of grid.
*********************************************************************************/
float*** Graphics::Get3DArray()
{
	return array3d;
}


/*********************************************************************************
	Method:		DeleteArray3D
	Parameter:	void
	Return:		void
	Purpose:	This method deletes and frees up the memory occupied by array3d
				private data member.
**********************************************************************************/
void Graphics::DeleteArray3D()
{
	int row = 10;
	int col = 10;
	int atr = 2;

	for (int i = 0; i < row; i++)
	{
		// delete each column
		for (int k = 0; k < col; k++)
		{
			delete[] array3d[i][k];
		}
		// delete entire row
		delete[] array3d[i];
	}

	// delete entire array
	delete[] array3d;
}






// backup grid draw
//for (int count = 0; count < 10; count++)
//{
//	y += gridheight;
//
//	rendertarget->DrawLine(
//		D2D1::Point2F(0.0f, y),
//		D2D1::Point2F(rtSize.width, y),
//		brush,
//		0.5f
//	);
//}

//
//rendertarget->DrawLine(
//	D2D1::Point2F((float)x, 0.0f),
//	D2D1::Point2F((float)x, rtSize.height),
//	brush,
//	0.5f
//);