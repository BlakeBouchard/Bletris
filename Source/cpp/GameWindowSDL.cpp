#include "../h/GameWindowSDL.h"

#ifdef BLETRIS_SDL

GameWindowSDL::GameWindowSDL(int numCols, int numRows) :
	GameWindow(),
	m_iNumCols(numCols),
	m_iNumRows(numRows)
{
}

GameWindowSDL::~GameWindowSDL()
{
	// Destroy window
	SDL_DestroyWindow(m_pWindow);

	delete m_pEventHandler;

	// Quit SDL subsystems
	SDL_Quit();
}

// Register the window class and call methods for instantiating drawing resources
bool GameWindowSDL::Initialize()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		// Create window
		m_pWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, g_iScreenWidth, g_iScreenHeight, SDL_WINDOW_SHOWN);
		m_pEventHandler = new SDL_Event();

		if (m_pWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			// Get window surface
			m_pScreenSurface = SDL_GetWindowSurface(m_pWindow);
		}
	}

	return true;
}

bool GameWindowSDL::DidWindowRequestExit()
{
	return m_bRequestedExit;
}

// Process and dispatch messages
void GameWindowSDL::Update(const std::vector<Colour> &boardSquares)
{
	// Handle events on queue
	while (SDL_PollEvent(m_pEventHandler) != 0)
	{
		// User requests quit
		if (m_pEventHandler->type == SDL_QUIT)
		{
			RequestExit();
		}
	}

	// Fill the surface white
	SDL_FillRect(m_pScreenSurface, NULL, SDL_MapRGB(m_pScreenSurface->format, 0xFF, 0xFF, 0xFF));

	// Update the surface
	SDL_UpdateWindowSurface(m_pWindow);
}

void GameWindowSDL::RequestExit()
{
	m_bRequestedExit = true;
}

#endif
