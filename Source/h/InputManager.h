#pragma once

#include "KeyCode.h"

#include <windows.h>

#include <map>
#include <memory>

class InputManager
{
public:
	InputManager();
	~InputManager();

private:
	// Unique Object
	InputManager(const InputManager &rhs) = delete;			   
	InputManager &operator=(const InputManager &rhs) = delete; 

	KeyCode GetKeyCodeFromParam(WPARAM param);
	void SetKeyDown(KeyCode key, bool keyIsDown);

	std::map<KeyCode, bool> m_aKeysDown;
	std::map<WPARAM, KeyCode> m_aKeyCodeLookup;

public:
	bool IsKeyDown(KeyCode key);
	void Update();
};
