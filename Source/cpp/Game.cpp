#include "../h/Enums.h"
#include "../h/Game.h"

#ifdef BLETRIS_WINDOWS
#include "../h/GameWindowD2D.h"
#include "../h/InputManagerWin.h"
#else
#include "../h/GameWindowOpenGL.h"
#include "../h/InputManagerMac.h"
#endif

Game::Game() :
	m_pBoard(std::make_shared<Board>(NumCols, NumRows)),
#ifdef BLETRIS_WINDOWS
	m_pGameWindow(std::make_shared<GameWindowD2D>(NumCols, NumRows)),
	m_pInputManager(std::make_shared<InputManagerWin>())
#else
	m_pGameWindow(std::make_shared<GameWindowOpenGL>(NumCols, NumRows)),
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
