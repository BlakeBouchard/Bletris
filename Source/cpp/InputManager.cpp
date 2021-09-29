#include "../h/InputManager.h"

#include <iostream>
#include <stdexcept>

/*------------
	PUBLIC
------------*/

InputManager::InputManager() : m_aKeysDown(),
							   m_aKeyCodeLookup()
{
	m_aKeysDown.insert(std::make_pair(KeyCode::Up, false));
	m_aKeysDown.insert(std::make_pair(KeyCode::Down, false));
	m_aKeysDown.insert(std::make_pair(KeyCode::Left, false));
	m_aKeysDown.insert(std::make_pair(KeyCode::Right, false));
	m_aKeysDown.insert(std::make_pair(KeyCode::Space, false));
	m_aKeysDown.insert(std::make_pair(KeyCode::Esc, false));

	m_aKeyCodeLookup.insert(std::make_pair(VK_UP, KeyCode::Up));
	m_aKeyCodeLookup.insert(std::make_pair(VK_DOWN, KeyCode::Down));
	m_aKeyCodeLookup.insert(std::make_pair(VK_LEFT, KeyCode::Left));
	m_aKeyCodeLookup.insert(std::make_pair(VK_RIGHT, KeyCode::Right));
	m_aKeyCodeLookup.insert(std::make_pair(VK_SPACE, KeyCode::Space));
	m_aKeyCodeLookup.insert(std::make_pair(VK_ESCAPE, KeyCode::Esc));
}

InputManager::~InputManager()
{
}

bool InputManager::IsKeyDown(KeyCode key)
{
	try
	{
		return m_aKeysDown.at(key);
	}
	catch (const std::out_of_range&)
	{
		std::cerr << "Tried to get KeyCode " << key << " but it did not exist in KeysDown table!\n";
		return false;
	}
}

void InputManager::Update()
{
	/*---------------------------------------------------------------------------
	For each Virtual KeyCode in m_aKeyCodeLookup that we care about, we'll set
	the corresponding KeyCode in m_aKeysDown. This will accomplish the task of
	converting the Virtual KeyCodes into our own Enum.
	---------------------------------------------------------------------------*/
	for (std::map<WPARAM, KeyCode>::iterator it = m_aKeyCodeLookup.begin(); it != m_aKeyCodeLookup.end(); it++)
	{
		WPARAM virtualKeyCode = it->first;
		KeyCode keyCode = it->second;

		bool keyIsDown = GetKeyState(virtualKeyCode) & 0x8000;
		SetKeyDown(keyCode, keyIsDown);
	}
}

/*-------------
	PRIVATE
-------------*/

KeyCode InputManager::GetKeyCodeFromParam(WPARAM virtualKeyCode)
{
	try
	{
		return m_aKeyCodeLookup.at(virtualKeyCode);
	}
	catch (const std::out_of_range&)
	{
		std::cerr << "Tried to get Virtual Keycode " << virtualKeyCode << " but it did not exist in KeyCodeLookup table!\n";
		return KeyCode::None;
	}
}

void InputManager::SetKeyDown(KeyCode key, bool keyIsDown)
{
	if (key == KeyCode::None)
	{
		return;
	}

	m_aKeysDown[key] = keyIsDown;
}
