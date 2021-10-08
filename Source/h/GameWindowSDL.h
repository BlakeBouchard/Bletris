#pragma once

#ifdef BLETRIS_SDL

#include "GameWindow.h"

#include <SDL.h>
#include <stdio.h>

class GameWindowSDL : public GameWindow
{
public:
	GameWindowSDL(int numCols, int numRows);
	~GameWindowSDL();

	// Register the window class and call methods for instantiating drawing resources
	bool Initialize();

	bool DidWindowRequestExit();

	// Process and dispatch messages
	void Update(const std::vector<Colour> &boardSquares);

private:
	GameWindowSDL() = delete;
	// Unique Object
	GameWindowSDL(const GameWindowSDL &rhs) = delete;
	GameWindowSDL &operator=(const GameWindowSDL &rhs) = delete;

	void RequestExit();

	// Screen dimension constants
	const int g_iScreenWidth = 640;
	const int g_iScreenHeight = 480;

	// The window we'll be rendering to
	SDL_Window* m_pWindow = NULL;

	// The surface contained by the window
	SDL_Surface* m_pScreenSurface = NULL;

	SDL_Event* m_pEventHandler = NULL;

	int m_iNumCols;
	int m_iNumRows;

	bool m_bRequestedExit = false;
};

#endif
