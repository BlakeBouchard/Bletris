#include "../h/Enums.h"
#include "../h/Game.h"

#ifdef BLETRIS_SDL
#include "../h/GameWindowSDL.h"
#else
#include "../h/GameWindowD2D.h"
#endif

#ifdef BLETRIS_WINDOWS
#include "../h/InputManagerWin.h"
#else
#include "../h/InputManagerMac.h"
#endif

Game::Game() :
	m_pBoard(std::make_shared<Board>(NumCols, NumRows)),
	// Now we need to instantiate the GameWindow based on what we're building for
	// We might be building SDL for Windows, hence why we don't assume that Windows is always going to be Direct2D
#ifdef BLETRIS_SDL
	m_pGameWindow(std::make_shared<GameWindowSDL>(NumCols, NumRows)),
#else
	m_pGameWindow(std::make_shared<GameWindowD2D>(NumCols, NumRows)),
#endif
#ifdef BLETRIS_WINDOWS
	m_pInputManager(std::make_shared<InputManagerWin>())
#else
	m_pInputManager(std::make_shared<InputManagerMac>())
#endif
{
}

Game::~Game()
{
}

bool Game::Initialize()
{
	return m_pGameWindow->Initialize();
}

void Game::Update()
{
	m_pInputManager->Update();

	// Update the Game Window by passing in the current Board state
	m_pGameWindow->Update(m_pBoard->GetBoardSquares());

	if (m_pInputManager->IsKeyDown(KeyCode::Esc))
	{
		RequestExit();
	}

	if (m_pGameWindow->DidWindowRequestExit())
	{
		RequestExit();
	}
}

void Game::RequestExit()
{
	m_bRequestedExit = true;
}

bool Game::DidGameRequestExit() const
{
	return m_bRequestedExit;
}
