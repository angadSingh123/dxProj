#include <Windows.h>
#include "Graphics.h"
#include <iostream>

#define LOCX 100
#define LOCY 100
#define WIDTH 500
#define HEIGHT 500

using namespace std;

Graphics* g;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {

	case WM_DESTROY:
		PostQuitMessage(0);
		std::cout << "ERROR\n";
		break;

	case WM_PAINT:
		
		g->BeginDraw();

		g->ClearScreen(0,255,255);

		g->Fill(0, 0, 0, 1);

		g->DrawCircle(100,100,50, 1.0f);

		g->Fill(0, 255, 0, 1);

		g->FillRect(50,50,100,100, 5.0f);

		g->EndDraw();

		break;


	default:
		DefWindowProc(hwnd, uMsg, wParam, lParam);		

	}	

	return 5000;

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

	WNDCLASSEX windowClass;
	// Zero the strucutre
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));

	//Initialise the window paramtres.
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.lpszClassName = "Window";
	windowClass.style = CS_HREDRAW | CS_VREDRAW;

	//Register the class the we just created.
	RegisterClassEx(&windowClass);

	//Make the client area the specified dimensions.
	RECT rect = { 0, 0, WIDTH, HEIGHT };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	//Create the window and get its handle (pointer)
	HWND windowHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "Window", "DirectX HHI",  WS_OVERLAPPEDWINDOW, LOCX, LOCY, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

	//Use this if WS_VISIBLE style not used earlier in the CreateWindow function
	ShowWindow(windowHandle, ncmdshow);

	//Create a graphics object
	g = new Graphics();

	if (!g->Init(windowHandle)) {
	
		delete g;
		return -1;
	
	}

	MSG message = {0};

	//Run a loop for getting window events
	while (GetMessage(&message, NULL, 0, 0)) {		

		DispatchMessage(&message);

	}

	return 10;

}




