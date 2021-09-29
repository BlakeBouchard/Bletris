#include "../h/Board.h"
#include "../h/GameWindow.h"

Board::Board(int numRows, int numCols) : m_iNumRows(numRows),
										 m_iNumCols(numCols),
										 m_aSquares(numRows * numCols, 0)
{
}

Board::Board(const Board &rhs) : m_iNumRows(rhs.m_iNumRows),
								 m_iNumCols(rhs.m_iNumCols),
								 m_aSquares(rhs.m_aSquares)
{
}

Board &Board::operator=(const Board &rhs)
{
	// Not that I ever expect to do this, but for simplicity's sake, let's just do a deep copy
	m_iNumRows = rhs.m_iNumRows;
	m_iNumCols = rhs.m_iNumCols;
	m_aSquares = rhs.m_aSquares; // This should be doing a Deep Copy

	return *this;
}

Board::~Board()
{
}

const std::vector<int> &Board::GetBoardSquares()
{
	return m_aSquares;
}
