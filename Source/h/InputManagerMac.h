#pragma once

#include "InputManager.h"

class InputManagerMac : public InputManager
{
public:
	InputManagerMac();
	~InputManagerMac();

	void Update();

private:
	std::map<int, KeyCode> m_aKeyCodeLookup;
};
