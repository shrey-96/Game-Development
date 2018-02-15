#include "SpriteSheet.h"

/***********************************************************************************
*	Class:		SpriteSheet														   *
*	Author:		Shreyansh Tiwari												   *
*	Reference:	Sample code by Russell Foubert									   *
*	Purpose:	The purpose of this class is to create wic components, decode the  *
*				the resource image file and encode it again into bitmap.		   *
*				This file is passed filename and pointer to render target as 	   *
*				parameter.														   *
************************************************************************************/


SpriteSheet::SpriteSheet(wchar_t* filename, Graphics* gfx)
{
	this->gfx = gfx; 
	bmp = NULL; 
	HRESULT hr;

	// creating a WIC factory
	IWICImagingFactory *wicFactory = NULL;
	
	hr = CoCreateInstance(
		CLSID_WICImagingFactory, 
		NULL, 
		CLSCTX_INPROC_SERVER, 
		IID_IWICImagingFactory, 
		(LPVOID*)&wicFactory); 

	// creating a decoder to read into bitmap file
	IWICBitmapDecoder *wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename, 
		NULL, 
		GENERIC_READ, 
		WICDecodeMetadataCacheOnLoad, 
		&wicDecoder); 

	// Read a 'frame'
	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	// Create a WIC Converter
	IWICFormatConverter *wicConverter = NULL;
	
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	// Configure the Converter
	hr = wicConverter->Initialize(
		wicFrame, 
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, 
		NULL,
		0.0, 
		WICBitmapPaletteTypeCustom
		);


	//Create the D2D Bitmap! Finally!
	gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter, 
		NULL, 
		&bmp 
	);
	
	// memory cleanup
	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();
}

// Destructor that releases bitmap once use is finished
SpriteSheet::~SpriteSheet()
{
	if (bmp) bmp->Release();
}


/*******************************************************************************************
	Method:			Draw()
	Parameters:		float x - top left x coordinate of bitmap
					float y - top left y coordinate of bitmap
					float swt - width to be reduced (to fit into grid)
					float sht - height to be reducde (to fit into grid)
					float wcentre - length to be pushed to get into centre
					float hcentre - height to be pushed to get into centre
	Returns:		void
	Purpose:		The purpose of this method is to draw bitmap onto screen for user to be 
					able to see it.
********************************************************************************************/
void SpriteSheet::Draw(float x, float y, float swt, float sht, float wcentre, float hcentre)
{
	gfx->GetRenderTarget()->DrawBitmap(
		bmp, 
		D2D1::RectF(x + wcentre, y + hcentre,
			bmp->GetSize().width + x - swt, bmp->GetSize().height + y - sht), 
		0.8f, //Opacity
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,	
		D2D1::RectF(0, 0, bmp->GetSize().width, bmp->GetSize().height) //Source Rect
		);
}

