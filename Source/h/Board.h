#pragma once

#include "Enums.h"

#include <memory>
#include <vector>

class Board
{
public:
	Board(int numCols, int numRows);
	Board(const Board &rhs);
	Board &operator=(const Board &rhs);
	~Board();

	const std::vector<Colour> &GetBoardSquares();

private:
	Board() = delete; // Don't allow this to be constructed without taking rows and cols parameters

	int m_iNumCols;
	int m_iNumRows;

	std::vector<Colour> m_aSquares;
};
