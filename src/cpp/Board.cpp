#include "../h/Board.h"

Board::Board(int numRows, int numCols) :
	m_iNumRows(numRows),
	m_iNumCols(numCols),
	m_paSquares(std::make_shared<std::vector<int>>(numRows* numCols, 0))
{
}

Board::Board(const Board& rhs) :
	m_iNumRows(rhs.m_iNumRows),
	m_iNumCols(rhs.m_iNumCols),
	m_paSquares(rhs.m_paSquares)
{
}

Board& Board::operator=(const Board& rhs)
{
	// Not that I ever expect to do this, but for simplicity's sake, let's just do a deep copy
	m_iNumRows = rhs.m_iNumRows;
	m_iNumCols = rhs.m_iNumCols;
	m_paSquares = rhs.m_paSquares; // This should be doing a Deep Copy

	return *this;
}

Board::~Board()
{
}

