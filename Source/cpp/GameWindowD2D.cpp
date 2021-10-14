#ifdef BLETRIS_WINDOWS

#include "../h/GameWindowD2D.h"

#include <iostream>
#include <stdexcept>

GameWindowD2D::GameWindowD2D(int numCols, int numRows) :
	GameWindow(),
	m_iNumCols(numCols),
	m_iNumRows(numRows),
	m_hwnd(NULL),
	m_pDirect2dFactory(NULL),
	m_pRenderTarget(NULL),
	m_aBrushes{
		{Colour::Blue, Brush(D2D1::ColorF::CornflowerBlue)},
		{Colour::Red, Brush(D2D1::ColorF::DarkRed)},
		{Colour::Gray, Brush(D2D1::ColorF::SlateGray)}}
{
}

GameWindowD2D::~GameWindowD2D()
{
	SafeRelease(&m_pDirect2dFactory);
	SafeRelease(&m_pRenderTarget);

	for (std::map<Colour, Brush>::iterator it = m_aBrushes.begin(); it != m_aBrushes.end(); it++)
	{
		SafeRelease(&it->second.pBrush);
	}
}

bool GameWindowD2D::DidWindowRequestExit()
{
	return m_bWindowRequestedExit;
}

void GameWindowD2D::Update(const std::vector<Colour>& boardSquares)
{
	MSG msg;

	if (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	else
	{
		RequestExit();
	}
}

bool GameWindowD2D::Initialize()
{
	HRESULT hr;

	// Initialize device-indpendent resources, such
	// as the Direct2D factory.
	hr = CreateDeviceIndependentResources();

	if (SUCCEEDED(hr))
	{
		// Register the window class.
		WNDCLASSEX wcex = {sizeof(WNDCLASSEX)};
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = GameWindowD2D::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(LONG_PTR);
		wcex.hInstance = HINST_THISCOMPONENT;
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
		wcex.lpszClassName = L"D2DGameWindow";

		RegisterClassEx(&wcex);

		// Create the window.
		m_hwnd = CreateWindow(
			L"D2DGameWindow",
			L"Direct2D Game Window",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			g_iScreenWidth,
			g_iScreenHeight,
			NULL,
			NULL,
			HINST_THISCOMPONENT,
			this);

		hr = m_hwnd ? S_OK : E_FAIL;
		if (SUCCEEDED(hr))
		{
			ShowWindow(m_hwnd, SW_SHOWNORMAL);
			UpdateWindow(m_hwnd);
		}
	}

	return SUCCEEDED(hr);
}

HRESULT GameWindowD2D::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;

	// Create a Direct2D factory.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

	return hr;
}

HRESULT GameWindowD2D::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	if (!m_pRenderTarget)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top);

		// Create a Direct2D render target.
		hr = m_pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&m_pRenderTarget);

		// Create brushes for each colour we're going to need
		for (std::map<Colour, Brush>::iterator it = m_aBrushes.begin(); SUCCEEDED(hr) && it != m_aBrushes.end(); it++)
		{
			// We don't actually care about the Key in the KeyValue pair here
			// We only want to set up the brush with the D2D1::ColorF value set in the object stored in the Value
			hr = m_pRenderTarget->CreateSolidColorBrush(it->second.drawColour, &it->second.pBrush);
		}
	}

	return hr;
}

void GameWindowD2D::DiscardDeviceResources()
{
	SafeRelease(&m_pRenderTarget);

	for (std::map<Colour, Brush>::iterator it = m_aBrushes.begin(); it != m_aBrushes.end(); it++)
	{
		SafeRelease(&it->second.pBrush);
	}
}

LRESULT CALLBACK GameWindowD2D::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		GameWindowD2D* pGameWindow = (GameWindowD2D*)pcs->lpCreateParams;

		::SetWindowLongPtrW(
			hwnd,
			GWLP_USERDATA,
			reinterpret_cast<LONG_PTR>(pGameWindow));

		result = 1;
	}
	else
	{
		GameWindowD2D* pGameWindow = reinterpret_cast<GameWindowD2D*>(static_cast<LONG_PTR>(
			::GetWindowLongPtrW(
				hwnd,
				GWLP_USERDATA)));

		bool wasHandled = false;

		if (pGameWindow)
		{
			switch (message)
			{
			case WM_SIZE:
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				pGameWindow->OnResize(width, height);
			}
				result = 0;
				wasHandled = true;
				break;

			case WM_DISPLAYCHANGE:
			{
				InvalidateRect(hwnd, NULL, FALSE);
			}
				result = 0;
				wasHandled = true;
				break;

			case WM_PAINT:
			{
				pGameWindow->OnRender();
				ValidateRect(hwnd, NULL);
			}
				result = 0;
				wasHandled = true;
				break;

			case WM_DESTROY:
			{
				PostQuitMessage(0);
			}
				result = 1;
				wasHandled = true;
				break;
			}
		}

		if (!wasHandled)
		{
			result = DefWindowProc(hwnd, message, wParam, lParam);
		}
	}

	return result;
}

HRESULT GameWindowD2D::OnRender()
{
	HRESULT hr = S_OK;

	hr = CreateDeviceResources();

	if (SUCCEEDED(hr))
	{
		m_pRenderTarget->BeginDraw();

		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

		// Draw each Square
		DrawSquare(0, 0, Colour::Blue);

		hr = m_pRenderTarget->EndDraw();
	}

	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		DiscardDeviceResources();
	}

	return hr;
}

void GameWindowD2D::OnResize(UINT width, UINT height)
{
	if (m_pRenderTarget)
	{
		// Note: This method can fail, but it's okay to ignore the
		// error here, because the error will be returned again
		// the next time EndDraw is called.
		m_pRenderTarget->Resize(D2D1::SizeU(width, height));
	}
}

ID2D1SolidColorBrush* GameWindowD2D::GetBrush(Colour colour)
{
	try
	{
		return m_aBrushes.at(colour).pBrush;
	}
	catch (const std::out_of_range &)
	{
		std::cerr << "Tried to get Brush but it did not exist in Brushes table!\n";
		return nullptr;
	}
}

void GameWindowD2D::DrawSquare(unsigned short xPos, unsigned short yPos, Colour colour)
{
	D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

	D2D1_RECT_F rectangle = D2D1::RectF(
		rtSize.width / 2 - 50.0f,
		rtSize.height / 2 - 50.0f,
		rtSize.width / 2 + 50.0f,
		rtSize.height / 2 + 50.0f);

	m_pRenderTarget->FillRectangle(&rectangle, GetBrush(colour));
}

void GameWindowD2D::RequestExit()
{
	m_bWindowRequestedExit = true;
}

#endif
