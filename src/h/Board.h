#pragma once

#include <memory>
#include <vector>

class Board
{
private:

	Board() = delete; // Don't allow this to be constructed without taking rows and cols parameters

	int mNumRows;
	int mNumCols;

	std::shared_ptr<std::vector<int>> mSquares;

public:

	Board(int numRows, int numCols);
	Board(const Board& rhs);
	Board& operator=(const Board& rhs);
	~Board();
};
