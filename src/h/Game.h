#pragma once

#include <memory>

#include "Board.h"

class Game
{
public:

	Game();
	~Game();

	bool DidGameRequestExit() const;

	void Update();

private:

	const int NumRows = 15;
	const int NumCols = 10;

	Game(const Game&) = delete; // There should only ever be one Game
	Game& operator=(const Game&) = delete; // There should only ever be one Game

	std::shared_ptr<Board> mBoard;

	bool bRequestedExit = false;

	void RequestExit();
};
