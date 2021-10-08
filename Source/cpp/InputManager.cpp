#include "../h/InputManager.h"

#include <iostream>
#include <stdexcept>

InputManager::InputManager() :
	m_aKeysDown()
{
	m_aKeysDown.insert(std::make_pair(KeyCode::Up, false));
	m_aKeysDown.insert(std::make_pair(KeyCode::Down, false));
	m_aKeysDown.insert(std::make_pair(KeyCode::Left, false));
	m_aKeysDown.insert(std::make_pair(KeyCode::Right, false));
	m_aKeysDown.insert(std::make_pair(KeyCode::Space, false));
	m_aKeysDown.insert(std::make_pair(KeyCode::Esc, false));
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
	catch (const std::out_of_range &)
	{
		std::cerr << "Tried to get KeyCode but it did not exist in KeysDown table!\n";
		return false;
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
