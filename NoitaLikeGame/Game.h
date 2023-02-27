#pragma once
#include "Engine.h"
#include "World.h"
#include "Input.h"

class Game : public Engine
{
public:
	Game() = default;
	~Game();

private:
	//Engine override
	void Ready() override;
	void Update(double delta) override;
	void Render() override;

	//Game
	World* world;
	Vector2 player_position;

	//Drawing Pixels
	void DrawBrush(const Pixel& pixel, int brush_size);
	std::vector<Pixel> brush_type{ Rock(), Sand(), Water()};
	int brush_type_counter = 0;

	float angle = 0;
};

