#include "Graphics.h"


Graphic::Graphic() {
	factory = NULL;
	renderTarget = NULL;
}

Graphic::~Graphic() {
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();
}

bool Graphic::Init(HWND windowHandle) {
	HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&factory);

	if (result != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);

	factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget);

	if (result != S_OK) return false;

	return true; 

}

void Graphic::ClearScreen(float r, float g, float b) {

	renderTarget->Clear(D2D1::ColorF(r, g, b));
}
void Graphic::DrawCircle(float x, float y, float radius, float r, float g, float b, float a) {

	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &brush);

	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);

	brush->Release();
}
