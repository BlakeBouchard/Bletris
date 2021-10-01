#include "../h/Enums.h"
#include "../h/Game.h"

Game::Game() :
	m_pBoard(std::make_shared<Board>(NumCols, NumRows)),
	m_pGameWindow(std::make_shared<GameWindow>(NumCols, NumRows)),
	m_pInputManager(std::make_shared<InputManager>())
{
}

Game::~Game()
{
}

HRESULT Game::Initialize()
{
	return SUCCEEDED(m_pGameWindow->Initialize());
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
