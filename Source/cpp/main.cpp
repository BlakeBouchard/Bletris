#ifndef UNICODE
#define UNICODE
#endif

#include "../h/Game.h"

#include <windows.h>

#include <iostream>
#include <stdexcept>

#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "user32.lib")

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// Use HeapSetInformation to specify that the process should
	// terminate if the heap manager detects an error in any heap used
	// by the process.
	// The return value is ignored, because we want to continue running in the
	// unlikely event that HeapSetInformation fails.
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			Game game;

			HRESULT hr = game.Initialize();

			if (!SUCCEEDED(hr))
			{
				std::cerr << "GameWindow failed to initialize with code " << hr << "\n";
				std::abort();
			}

			try
			{
				while (!game.DidGameRequestExit())
				{
					game.Update();
				}
			}
#ifdef DEBUG
			catch (const std::exception& ex)
			{
				// It's extremely dangerous to print aribtrary exception text on a customer build
				std::cerr << ex.what();
			}
#else
			catch (const std::exception&) {}
#endif
		}
		CoUninitialize();
	}

	return 0;
}
