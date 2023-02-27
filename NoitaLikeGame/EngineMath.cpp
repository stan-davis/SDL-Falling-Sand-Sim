#include "EngineMath.h"

//Vector2i
Vector2i Vector2i::operator+(const Vector2i& v) const
{
	return Vector2i( x + v.x, y + v.y );
}

Vector2i Vector2i::operator-(const Vector2i& v) const
{
	return Vector2i(x - v.x, y - v.y );
}

Vector2i Vector2i::operator*(const Vector2i& v) const
{
	return Vector2i(x * v.x, y * v.y );
}

void Vector2i::operator+=(const Vector2i& v)
{
	x += v.x;
	y += v.y;
}

void Vector2i::operator-=(const Vector2i& v)
{
	x -= v.x;
	y -= v.y;
}

void Vector2i::operator*=(const Vector2i& v)
{
	x *= v.x;
	y *= v.y;
}

bool Vector2i::operator==(const Vector2i& v) const
{
	return v.x == x && v.y == y;
}

bool Vector2i::operator!=(const Vector2i& v) const
{
	return v.x != x || v.y != y;
}

float Vector2i::Length()
{
	return sqrtf((x * x) + (y * y));
}

//Vector2
float Vector2::Length()
{
	return sqrtf((x * x) + (y * y));
}

Vector2 Vector2::operator+(const Vector2& v) const
{
	return Vector2(x + v.x, y + v.y );
}

Vector2 Vector2::operator-(const Vector2& v) const
{
	return Vector2(x - v.x, y - v.y );
}

Vector2 Vector2::operator*(const Vector2& v) const
{
	return Vector2(x * v.x, y * v.y );
}

Vector2 Vector2::operator/(const Vector2& v) const
{
	return Vector2(x / v.x, y / v.y );
}

void Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
}

void Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
}

void Vector2::operator*=(const Vector2& v)
{
	x *= v.x;
	y *= v.y;
}

void Vector2::operator/=(const Vector2& v)
{
	x /= v.x;
	y /= v.y;
}

bool Vector2::operator==(const Vector2& v) const
{
	return v.x == x && v.y == y;
}

bool Vector2::operator!=(const Vector2& v) const
{
	return v.x != x || v.y != y;
}

//Transform
Transform::Transform()
{
	Identity();
}

Transform::Transform(Vector2 x, Vector2 y, Vector2 origin)
{
	columns[0] = x;
	columns[1] = y;
	columns[2] = origin;
}

void Transform::Forward(Vector2 in, Vector2& out)
{
	out.x = in.x * columns[0].x + in.y * columns[1].x + columns[2].x;
	out.y = in.x * columns[0].y + in.y * columns[1].y + columns[2].y;
}

Transform Transform::Identity()
{
	columns[0].x = 1.0;
	columns[1].y = 1.0;

	return *this;
}

Transform Transform::Translate(Vector2 offset)
{
	columns[2] += offset;
	return *this;
}

Transform Transform::Rotate(float angle)
{
	float cr = cosf(angle);
	float sr = sinf(angle);

	columns[0].x = cr;
	columns[0].y = sr;
	columns[1].x = -sr;
	columns[1].y = cr;

	return *this;
}

Transform Transform::Scale(Vector2 scale)
{
	columns[0] *= scale;
	columns[1] *= scale;
	columns[2] *= scale;

	return *this;
}
