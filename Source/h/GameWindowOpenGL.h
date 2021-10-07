#pragma once

#include "GameWindow.h"

class GameWindowOpenGL : public GameWindow
{
public:
    GameWindowOpenGL(int numCols, int numRows);
    ~GameWindowOpenGL();

	// Register the window class and call methods for instantiating drawing resources
	bool Initialize();

	bool DidWindowRequestExit();

	// Process and dispatch messages
	void Update(const std::vector<Colour>& boardSquares);

private:
    GameWindowOpenGL() = delete;

    int m_iNumCols;
    int m_iNumRows;
};
