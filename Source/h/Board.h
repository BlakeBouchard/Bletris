#pragma once

#include <memory>
#include <vector>

class Board
{
public:
	Board(int numRows, int numCols);
	Board(const Board &rhs);
	Board &operator=(const Board &rhs);
	~Board();

	const std::vector<int> &GetBoardSquares();

private:
	Board() = delete; // Don't allow this to be constructed without taking rows and cols parameters

	int m_iNumRows;
	int m_iNumCols;

	std::vector<int> m_aSquares;
};
