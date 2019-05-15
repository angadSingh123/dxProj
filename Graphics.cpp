#include "Graphics.h"

Graphics::Graphics()
{
	factory = NULL;
	renderTarget = NULL;

}

Graphics::~Graphics()
{
	if (brush) brush->Release();
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();

}

bool Graphics::Init(HWND windowHandle) {

	//Create factory and see if all is valid.
	HRESULT hResult = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

	if (hResult != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);

	hResult = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget);

	if (hResult != S_OK) return false;

	Fill(0, 0, 0, 0);

	return true;

}

void Graphics::ClearScreen(float r, float g, float b) {


	renderTarget->Clear(D2D1::ColorF(r,g,b));

}

void Graphics::DrawCircle(float x, float y, float radius, float strokeWidth) {		
	
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, strokeWidth);	

}

void Graphics::FillRect(float x, float y, float w, float h, float strokeWieght)
{

	D2D1_RECT_F rect = D2D1::RectF(x,y,w,h);

	renderTarget->FillRectangle(&rect, brush);

}

void Graphics::Fill(float r, float g, float b, float a) {

	renderTarget->CreateSolidColorBrush(D2D1::ColorF(r,g,b,a), &brush);

}
