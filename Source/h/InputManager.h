#pragma once
class InputManager
{
private:

	InputManager();
	~InputManager();
	InputManager(const InputManager& rhs) = delete; // Only ever going to have one of these
	InputManager& operator=(const InputManager& rhs) = delete; // Only ever going to have one of these
};

