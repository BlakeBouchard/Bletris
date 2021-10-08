#ifndef UNICODE
#define UNICODE
#endif

#ifdef BLETRIS_WINDOWS
#include <windows.h>
#endif

#include "../h/Game.h"

#include <iostream>
#include <stdexcept>

void StartGame()
{
	Game game;

	bool initialized = game.Initialize();

	if (!initialized)
	{
		std::cerr << "GameWindow failed to initialize\n";
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
	// It's extremely dangerous to print aribtrary exception text on a customer build
	catch (const std::exception& ex)
	{
		std::cerr << ex.what();
	}
#else
	catch (const std::exception&) {}
#endif
}

#ifdef BLETRIS_WINDOWS

// Entry point for Windows build
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
		StartGame();
		
		// StartGame should loop until it's time to exit
		CoUninitialize();
	}

	return 0;
}

#else

// Entry point for non-Windows build
int main(int argc, char* argv[])
{
	StartGame();

	return 0;
}

#endif
