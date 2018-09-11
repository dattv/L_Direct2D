
//#include "stdafx.h"
#include <Windows.h>
#include "Graphics.h"
//#include <d2d1_1.h>
//#include <d2d1_1helper.h>

//int WINAPI WinMain(
//	HINSTANCE hInstance,
//	HINSTANCE prevInstance,
//	LPSTR cmd,
//	int nCmdShow
//);

Graphic* graphic;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) {
		PostQuitMessage(0);
		return 0;
	}

	if (uMsg == WM_PAINT) {
		graphic->BeginDraw();

		graphic->ClearScreen(0.0f, 0.0f, 0.5f);
		for (int i = 0; i < 500; i++) {

			graphic->DrawCircle(rand() % 800, rand() % 600, rand() % 100,
				(rand() % 100) / 100.f,
				(rand() % 100) / 100.f,
				(rand() % 100) / 100.f,
				(rand() % 100) / 100.f);
		}

		graphic->EndDraw();
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{

	WNDCLASSEX windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = "MainWindow";
	windowClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowClass);

	RECT rect{ 0, 0, 800, 600 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	HWND windowHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,"MainWindow", "DirectX_tute", WS_OVERLAPPEDWINDOW, 100, 100, 
		rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

	if (!windowHandle) return -1;

	graphic = new Graphic();
	if (!graphic->Init(windowHandle)) {
		delete graphic;
		return -1;
	}
	ShowWindow(windowHandle, nCmdShow);

	MSG message;
	while (GetMessage(&message, NULL, 0, 0)) {
		DispatchMessage(&message);

	}
	delete graphic;

	return 0;
}
