// FunWithBitmaps.cpp : Defines the entry point for the application.
//
#include "Render.h"
#include <Windows.h>
#include <stdint.h>
#include <math.h>

#define global_variable static
global_variable BOOL running;
HWND windowHandle = 0;

typedef unsigned int uint32;

int DIBWidth;
int DIBHeight;
int DIBrowByteWidth;
uint32 * m_pBitmapBits;
HDC h_dibDC;
HBITMAP m_hDIBBitmap;
HBITMAP m_hOldDIBBitmap;
BITMAPINFO mybmi;
Render *renderer;
GameInput input;

void createDIB(HWND windowHandle) {
	HDC hdc = GetDC(windowHandle);

	RECT mainClientRect;
	GetClientRect(windowHandle, &mainClientRect);

	DIBWidth = mainClientRect.right;
	DIBHeight = mainClientRect.bottom;
	int bitCount = 32;
	DIBrowByteWidth = ((DIBWidth * (bitCount / 8) + 3) & -4);
	int totalBytes = DIBrowByteWidth * DIBHeight;

	////// This is the BITMAPINFO structure values for the Green Ball
	mybmi.bmiHeader.biSize = sizeof(mybmi);
	mybmi.bmiHeader.biWidth = DIBWidth;
	mybmi.bmiHeader.biHeight = -DIBHeight;
	mybmi.bmiHeader.biPlanes = 1;
	mybmi.bmiHeader.biBitCount = bitCount;
	mybmi.bmiHeader.biCompression = BI_RGB;
	mybmi.bmiHeader.biSizeImage = totalBytes;
	mybmi.bmiHeader.biXPelsPerMeter = 0;
	mybmi.bmiHeader.biYPelsPerMeter = 0;

	h_dibDC = CreateCompatibleDC(hdc);
	m_hDIBBitmap = CreateDIBSection(hdc, &mybmi, DIB_RGB_COLORS, (VOID **)&m_pBitmapBits, NULL, 0);
	m_hOldDIBBitmap = (HBITMAP)SelectObject(h_dibDC, m_hDIBBitmap);

	ReleaseDC(windowHandle, hdc);
}

LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;

	switch (message) {
		
		case WM_SIZE:
		{
			if(renderer) {
				//createDIB(windowHandle);
				//renderer->changeDrawBufferDimensions(m_pBitmapBits, DIBWidth, DIBHeight);

				//renderer->draw();
			}
		}
		break;
		
		case WM_DESTROY:
		{
			running = false;
			PostQuitMessage(0);
			return 0;
		}
		break;

		case WM_CLOSE: 
		{
			running = false;
			DestroyWindow(window);
			return 0;
		}	
		break;
		
		case WM_PAINT:
		{
			ValidateRect(windowHandle, 0);
		}

		case WM_KEYDOWN: 
		{
			switch(wParam) {
				case VK_SPACE:
				{
					input.spaceDown = true;
				}
				break;

				case VK_LEFT:
				{
					input.leftDown = true;
				}
				break;

				case VK_RIGHT:
				{
					input.rightDown = true;
				}
				break;
				
				case VK_UP:
				{
					input.upDown = true;
				}
				break;

				case VK_DOWN:
				{
					input.downDown = true;
				}
				break;

				// Quit the program by hitting escape
				case VK_ESCAPE:
				{
					PostQuitMessage(0);
				}
				break;
			}
		}
		break;

		case WM_KEYUP:
		{
			switch(wParam) {
				case VK_SPACE:
				{
					input.spaceDown = false;
				}
				break;

				case VK_LEFT:
				{
					input.leftDown = false;
				}
				break;

				case VK_RIGHT:
				{
					input.rightDown = false;
				}
				break;

				case VK_UP:
				{
					input.upDown = false;
				}
				break;

				case VK_DOWN:
				{
					input.downDown = false;
				}
				break;
			}
		}
		
		default:
		{
			result = DefWindowProc(window, message, wParam, lParam);
		}
		break;
	}
	
	return result;
}


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// Create the window class
	WNDCLASS windowClass = {};

	windowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = hInstance;
	windowClass.lpszClassName = L"Windows Program Class";

	if(RegisterClass(&windowClass)) {
		// Create the window
		windowHandle = CreateWindowEx(
								0,									// Extended style
								windowClass.lpszClassName,			// Class name
								L"My Windows Program",				// Window name
								WS_OVERLAPPEDWINDOW | WS_VISIBLE,	// Style of the window
								CW_USEDEFAULT,						// Initial X position
								CW_USEDEFAULT,						// Initial Y position
								CW_USEDEFAULT,						// Initial width
								CW_USEDEFAULT,						// Initial height 
								0,									// Handle to the window parent
								0,									// Handle to a menu
								hInstance,							// Handle to an instance
								0);									// Pointer to a CLIENTCTREATESTRUCT
		if(windowHandle) {
			createDIB(windowHandle);
			renderer = new Render(m_pBitmapBits, DIBWidth, DIBHeight);
			running = true;

			// Message loop
			while(running) {
				MSG message;
				while(PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
					if(message.message == WM_QUIT) {
						running = false;
					}
					TranslateMessage(&message);
					DispatchMessage(&message);
				}

				// Get cursor position and store it in input
				POINT cursorPoint;
				GetCursorPos(&cursorPoint);
				RECT clientRect;
				GetClientRect(windowHandle, &clientRect);
				ScreenToClient(windowHandle, &cursorPoint);
				input.cursorX = cursorPoint.x;
				input.cursorY = cursorPoint.y;

				if(renderer) {
					renderer->draw(input);
				}

				HDC hdc = GetDC(windowHandle);
				BitBlt(hdc, 0, 0, DIBWidth, DIBHeight, h_dibDC, 0, 0, SRCCOPY );
				//StretchDIBits(hdc, 0, 0, DIBWidth, DIBHeight, 0, 0, DIBWidth, DIBHeight, m_hDIBBitmap, &mybmi, DIB_RGB_COLORS, SRCCOPY);
				ReleaseDC(windowHandle, hdc);
			}
		} else {
			// Logging
		}
	} else {
		// Logging
	}

	return 0;
}
