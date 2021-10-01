#pragma once

/*--------------------------------------------------------------------
GameWindow: Source code heavily based on "Creating a Simple Direct2D Application"
https://docs.microsoft.com/en-us/windows/win32/direct2d/direct2d-quickstart
--------------------------------------------------------------------*/

#include "Enums.h"

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files:
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#include <map>
#include <vector>

#pragma comment(lib, "d2d1")

template <class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}

#ifndef Assert
#if defined(DEBUG) || defined(_DEBUG)
#define Assert(b)                                   \
	do                                              \
	{                                               \
		if (!(b))                                   \
		{                                           \
			OutputDebugStringA("Assert: " #b "\n"); \
		}                                           \
	} while (0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

class GameWindow
{
public:
	GameWindow() = delete;
	GameWindow(int numCols, int numRows);
	~GameWindow();

	// Register the window class and call methods for instantiating drawing resources
	HRESULT Initialize();

	bool DidWindowRequestExit();

	// Process and dispatch messages
	void Update(const std::vector<Colour> &boardSquares);

private:
	// No assigning, no duplicating
	GameWindow(const GameWindow &rhs) = delete;
	GameWindow &operator=(const GameWindow &rhs) = delete;

	const unsigned short m_iNumRows;
	const unsigned short m_iNumCols;

	HWND m_hwnd;
	ID2D1Factory *m_pDirect2dFactory;
	ID2D1HwndRenderTarget *m_pRenderTarget;

	struct Brush
	{
		D2D1::ColorF drawColour;
		ID2D1SolidColorBrush *pBrush;

		Brush(D2D1::ColorF colour) : drawColour(colour), pBrush(nullptr) {}
	};

	// Brushes
	std::map<Colour, Brush> m_aBrushes;

	bool m_bWindowRequestedExit = false;

	// Initialize device-independent resources.
	HRESULT CreateDeviceIndependentResources();

	// Initialize device-dependent resources.
	HRESULT CreateDeviceResources();

	// Release device-dependent resource.
	void DiscardDeviceResources();

	// Draw content.
	HRESULT OnRender();

	// Resize the render target.
	void OnResize(
		UINT width,
		UINT height);

	// The windows procedure.
	static LRESULT CALLBACK WndProc(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam);

	ID2D1SolidColorBrush *GetBrush(Colour colour);

	void DrawSquare(unsigned short xPos, unsigned short yPos, Colour colour);

	void RequestExit();
};
