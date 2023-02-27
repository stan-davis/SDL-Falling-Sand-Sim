#include "Input.h"
#include <cstring>

Input::Input()
{
    keyboard_state = SDL_GetKeyboardState(&key_length);
    prev_key_state = new Uint8[key_length];
    memcpy(prev_key_state, keyboard_state, key_length);
}

Input::~Input()
{
    delete[] prev_key_state;
    prev_key_state = NULL;
}

void Input::PollState()
{
    mouse_state = SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
}

void Input::UpdatePreviousInput()
{
    memcpy(prev_key_state, keyboard_state, key_length);
    prev_mouse_state = mouse_state;
}

bool Input::IsKeyPressed(SDL_Scancode scancode)
{
    return !prev_key_state[scancode] && keyboard_state[scancode];
}

bool Input::IsKeyHeld(SDL_Scancode scancode)
{
    return keyboard_state[scancode];
}

bool Input::IsKeyReleased(SDL_Scancode scancode)
{
    return prev_key_state[scancode] && !keyboard_state[scancode];
}

bool Input::IsMouseButtonPressed(MouseButton button)
{
    Uint32 mask = GetButtonMask(button);
    return !(prev_mouse_state & mask) && (mouse_state & mask);
}

bool Input::IsMouseButtonHeld(MouseButton button)
{
    return (mouse_state & GetButtonMask(button));
}

bool Input::IsMouseButtonReleased(MouseButton button)
{
    Uint32 mask = GetButtonMask(button);
    return (prev_mouse_state & mask) && !(mouse_state & mask);
}

Uint32 Input::GetButtonMask(MouseButton button)
{
    Uint32 mask = 0;

    switch (button)
    {
    case BUTTON_LEFT:
        mask = SDL_BUTTON_LMASK;
        break;
    case BUTTON_RIGHT:
        mask = SDL_BUTTON_RMASK;
        break;
    case BUTTON_MIDDLE:
        mask = SDL_BUTTON_MMASK;
        break;
    case BUTTON_WHEEL_DOWN:
        mask = SDL_BUTTON_X1MASK;
        break;
    case BUTTON_WHEEL_UP:
        mask = SDL_BUTTON_X2MASK;
        break;
    }

    return mask;
}

Vector2i Input::GetMousePosition()
{
    return { mouse_position.x, mouse_position.y };
}


