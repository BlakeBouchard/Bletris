#ifndef UNICODE
#define UNICODE
#endif

#include "../h/Game.h"

#include <windows.h>

#include <iostream>

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

			if (!SUCCEEDED(game.Initialize()))
			{
				std::cout << "GameWindow failed to initialize!\n";
				std::abort();
			}

			try
			{
				while (!game.DidGameRequestExit())
				{
					game.Update();
				}
			}
			catch (const std::exception &ex)
			{
				std::cout << ex.what();
			}
		}
		CoUninitialize();
	}

	return 0;
}
