#include "../h/InputManagerMac.h"

#ifdef BLETRIS_SDL

#include "SDL.h"

InputManagerMac::InputManagerMac() :
	InputManager()
{
	m_aKeyCodeLookup.insert(std::make_pair(static_cast<int>(SDL_SCANCODE_UP), KeyCode::Up));
	m_aKeyCodeLookup.insert(std::make_pair(static_cast<int>(SDL_SCANCODE_DOWN), KeyCode::Down));
	m_aKeyCodeLookup.insert(std::make_pair(static_cast<int>(SDL_SCANCODE_LEFT), KeyCode::Left));
	m_aKeyCodeLookup.insert(std::make_pair(static_cast<int>(SDL_SCANCODE_RIGHT), KeyCode::Right));
	m_aKeyCodeLookup.insert(std::make_pair(static_cast<int>(SDL_SCANCODE_SPACE), KeyCode::Space));
	m_aKeyCodeLookup.insert(std::make_pair(static_cast<int>(SDL_SCANCODE_ESCAPE), KeyCode::Esc));
}

InputManagerMac::~InputManagerMac()
{
}

void InputManagerMac::Update()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	for (std::map<int, KeyCode>::iterator it = m_aKeyCodeLookup.begin(); it != m_aKeyCodeLookup.end(); it++)
	{
		SDL_Scancode scancode = static_cast<SDL_Scancode>(it->first);
		KeyCode keyCode = it->second;

		bool keyIsDown = currentKeyStates[scancode];
		SetKeyDown(keyCode, keyIsDown);
	}
}

#endif
