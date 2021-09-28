#ifndef UNICODE
#define UNICODE
#endif

#include "../h/Game.h"
#include "../h/GameWindow.h"

#include <windows.h>
#include <iostream>

#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "user32.lib")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
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
			GameWindow gameWindow;

			if (!SUCCEEDED(gameWindow.Initialize()))
			{
				std::cout << "GameWindow failed to initialize!\n";
				std::abort();
			}

			try
			{
				while (!game.DidGameRequestExit() && !gameWindow.DidWindowRequestExit())
				{
					game.Update();
					gameWindow.Update();
				}
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what();
			}
		}
		CoUninitialize();
	}

	return 0;
}