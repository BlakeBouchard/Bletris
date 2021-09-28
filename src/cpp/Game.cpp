#include "../h/Game.h"

#include <memory>

Game::Game() :
	mBoard(std::make_shared<Board>(NumRows, NumCols))
{
}

Game::~Game()
{
}

void Game::RequestExit()
{
	bRequestedExit = true;
}

bool Game::DidGameRequestExit() const
{
	return bRequestedExit;
}

void Game::Update()
{
	// if (DirectInput.GetKeyboardDown(KeyCode.Escape) OR SOMETHING
	// {
	// 	RequestExit();
	// }
}
