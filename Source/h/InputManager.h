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
	InputManager(const InputManager& rhs) = delete; // Only ever going to have one of these
	InputManager& operator=(const InputManager& rhs) = delete; // Only ever going to have one of these

	KeyCode GetKeyCodeFromParam(WPARAM param);
	void SetKeyDown(KeyCode key, bool keyIsDown);

	std::map<KeyCode, bool> m_aKeysDown;
	std::map<WPARAM, KeyCode> m_aKeyCodeLookup;

public:
	bool IsKeyDown(KeyCode key);
	void Update();
};
