#pragma once

#include "Enums.h"

#include <map>

class InputManager
{
public:
	InputManager();
	virtual ~InputManager();

	bool IsKeyDown(KeyCode key);
	
	virtual void Update() = 0;

private:
	std::map<KeyCode, bool> m_aKeysDown;

protected:
	void SetKeyDown(KeyCode key, bool keyIsDown);
};
