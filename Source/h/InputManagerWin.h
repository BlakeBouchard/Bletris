#pragma once

#ifdef BLETRIS_WINDOWS

#include "InputManager.h"

#include <windows.h>

#include <map>
#include <memory>

class InputManagerWin : public InputManager
{
public:
	InputManagerWin();
	~InputManagerWin();

	bool IsKeyDown(KeyCode key);
	void Update();

private:
	// Unique Object
	InputManagerWin(const InputManagerWin &rhs) = delete;			   
	InputManagerWin &operator=(const InputManagerWin &rhs) = delete; 

	KeyCode GetKeyCodeFromParam(WPARAM param);
	void SetKeyDown(KeyCode key, bool keyIsDown);

	std::map<KeyCode, bool> m_aKeysDown;
	std::map<WPARAM, KeyCode> m_aKeyCodeLookup;
};

#endif
