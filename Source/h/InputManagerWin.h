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

	void Update();

private:
	// Unique Object
	InputManagerWin(const InputManagerWin &rhs) = delete;			   
	InputManagerWin &operator=(const InputManagerWin &rhs) = delete; 

	KeyCode GetKeyCodeFromParam(WPARAM param);
	std::map<WPARAM, KeyCode> m_aKeyCodeLookup;
};

#endif
