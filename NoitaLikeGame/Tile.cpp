#include "Tile.h"

Tile::Tile(Vector2 position, b2BodyType type, b2Shape& shape, b2World& world)
{
	/*Create Rigidbody*/
	b2BodyDef body_def;
	body_def.type = type;
	body_def.position.Set(position.x, position.y);
	body_def.angle = 0;

	body = world.CreateBody(&body_def);

	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;
	fixture_def.density = 1;
	fixture_def.friction = 0.3f;
	
	body->CreateFixture(&fixture_def);
}