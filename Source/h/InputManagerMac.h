#pragma once

#include "InputManager.h"

class InputManagerMac : public InputManager
{
public:
	InputManagerMac();
	~InputManagerMac();

	bool IsKeyDown(KeyCode key);
	void Update();
};
