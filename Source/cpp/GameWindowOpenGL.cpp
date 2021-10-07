#include "../h/GameWindowOpenGL.h"

GameWindowOpenGL::GameWindowOpenGL(int numCols, int numRows) :
    m_iNumCols(numCols),
    m_iNumRows(numRows)
{
}

GameWindowOpenGL::~GameWindowOpenGL()
{
}

// Register the window class and call methods for instantiating drawing resources
bool GameWindowOpenGL::Initialize()
{
    return true;
}

bool GameWindowOpenGL::DidWindowRequestExit()
{
    return false;
}

// Process and dispatch messages
void GameWindowOpenGL::Update(const std::vector<Colour>& boardSquares)
{
}
