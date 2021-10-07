#pragma once

#include "Enums.h"

class InputManager
{
public:
	InputManager() {};
	virtual ~InputManager() {};

	virtual bool IsKeyDown(KeyCode key) = 0;
	virtual void Update() = 0;
};
