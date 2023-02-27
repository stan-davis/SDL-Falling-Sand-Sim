#include "Game.h"
#include <iostream>

Game::~Game()
{
	delete world;
}

void Game::Ready()
{
	world = new World();
}

void Game::Update(double delta)
{
	if (GetInput()->IsKeyPressed(SDL_SCANCODE_UP))
		brush_type_counter = (brush_type_counter + 1) % brush_type.size();

	if (GetInput()->IsKeyPressed(SDL_SCANCODE_DOWN))
		brush_type_counter = (brush_type_counter + (brush_type.size() - 1)) % brush_type.size();

	if (GetInput()->IsMouseButtonHeld(Input::BUTTON_LEFT)) DrawBrush(brush_type[brush_type_counter], 2);
	if (GetInput()->IsMouseButtonHeld(Input::BUTTON_RIGHT)) DrawBrush(Pixel(), 2);

	world->Update(delta);
}

void Game::Render()
{
	world->Draw(GetGraphics());
}

void Game::DrawBrush(const Pixel& pixel, int brush_size)
{
	for (int x = GetInput()->GetMousePosition().x - brush_size; x <= GetInput()->GetMousePosition().x + brush_size; x++)
		for (int y = GetInput()->GetMousePosition().y - brush_size; y <= GetInput()->GetMousePosition().y + brush_size; y++)
			world->SetPixel(pixel, x, y);
}
