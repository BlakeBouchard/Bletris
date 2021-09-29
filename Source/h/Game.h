#pragma once

#include "Board.h"
#include "GameWindow.h"

#include <memory>

class Game
{
public:

	Game();
	~Game();

	bool DidGameRequestExit() const;

	HRESULT Initialize();
	void Update();

private:

	const int NumRows = 15;
	const int NumCols = 10;

	Game(const Game&) = delete; // There should only ever be one Game
	Game& operator=(const Game&) = delete; // There should only ever be one Game

	std::shared_ptr<Board> m_pBoard;
	std::shared_ptr<GameWindow> m_pGameWindow;

	bool m_bRequestedExit = false;

	void RequestExit();
};
