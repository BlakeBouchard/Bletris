#pragma once

#include "Board.h"
#include "GameWindow.h"
#include "InputManager.h"

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
	// Unique Object
	Game(const Game &) = delete;
	Game &operator=(const Game &) = delete;

	const int NumCols = 10;
	const int NumRows = 15;

	std::shared_ptr<Board> m_pBoard;
	std::shared_ptr<GameWindow> m_pGameWindow;
	std::shared_ptr<InputManager> m_pInputManager;

	bool m_bRequestedExit = false;

	void RequestExit();
};
