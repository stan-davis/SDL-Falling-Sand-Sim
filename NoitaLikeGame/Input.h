#pragma once
#include "SDL.h"
#include "EngineMath.h"

class Input
{
public:
	Input();
	~Input();

	enum MouseButton {BUTTON_LEFT, BUTTON_RIGHT, BUTTON_MIDDLE, BUTTON_WHEEL_UP, BUTTON_WHEEL_DOWN};

	//Update
	void PollState();
	void UpdatePreviousInput();

	//Input polling
	bool IsKeyPressed(SDL_Scancode scancode);
	bool IsKeyHeld(SDL_Scancode scancode);
	bool IsKeyReleased(SDL_Scancode scancode);

	bool IsMouseButtonPressed(MouseButton button);
	bool IsMouseButtonHeld(MouseButton button);
	bool IsMouseButtonReleased(MouseButton button);

	Vector2i GetMousePosition();
private:
	Uint32 GetButtonMask(MouseButton button);

	//Keyboard
	const Uint8* keyboard_state;
	Uint8* prev_key_state;
	int key_length;

	//Mouse
	Uint32 mouse_state;
	Uint32 prev_mouse_state;
	Vector2i mouse_position = Vector2i(0,0);
};

