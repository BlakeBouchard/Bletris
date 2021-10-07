#pragma once

#include "Enums.h"

#include <vector>

class GameWindow
{
public:
	virtual ~GameWindow() {};

	// Register the window class and call methods for instantiating drawing resources
	virtual bool Initialize() = 0;

	virtual bool DidWindowRequestExit() = 0;

	// Process and dispatch messages
	virtual void Update(const std::vector<Colour>& boardSquares) = 0;
};
