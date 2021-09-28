#include "../h/Board.h"

Board::Board(int numRows, int numCols) :
	mNumRows(numRows),
	mNumCols(numCols),
	mSquares(std::make_shared<std::vector<int>>(numRows* numCols, 0))
{
}

Board::Board(const Board& rhs) :
	mNumRows(rhs.mNumRows),
	mNumCols(rhs.mNumCols),
	mSquares(rhs.mSquares)
{
}

Board& Board::operator=(const Board& rhs)
{
	// Not that I ever expect to do this, but for simplicity's sake, let's just do a deep copy
	mNumRows = rhs.mNumRows;
	mNumCols = rhs.mNumCols;
	mSquares = rhs.mSquares; // This should be doing a Deep Copy

	return *this;
}

Board::~Board()
{
}

