#include "Tile.h"

Tile::Tile(Vector2 position, b2BodyType type, b2World& world)
{
	b2BodyDef def;
	def.type = type;
	def.position.Set(transform.GetOrigin().x, transform.GetOrigin().y);

	b2PolygonShape box;
	box.SetAsBox(1, 1);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1;
	fixture.friction = 0.3f;

	body = world.CreateBody(&def);
	body->CreateFixture(&fixture);

	transform.Translate(position);
}

void Tile::Update()
{
	/*Update Physics*/
	transform.Translate({ body->GetPosition().x, body->GetPosition().y });
	transform.Rotate(body->GetAngle());
}
