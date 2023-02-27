#pragma once
#include <cmath>
#include <functional>

struct Vector2i
{
	Vector2i() = default;
	Vector2i(int _x, int _y) : x(_x), y(_y) {};

	Vector2i operator+(const Vector2i& v) const;
	Vector2i operator-(const Vector2i& v) const;
	Vector2i operator*(const Vector2i& v) const;
	void operator+=(const Vector2i& v);
	void operator-=(const Vector2i& v);
	void operator*=(const Vector2i& v);
	bool operator==(const Vector2i& v) const;
	bool operator!=(const Vector2i& v) const;

	float Length();

	int x = 0;
	int y = 0;
};

template<>
class std::hash<Vector2i>
{
public:
	size_t operator()(const Vector2i& key) const
	{
		return (key.x * 73856093) ^ (key.y * 83492791);
	}
};

struct Vector2
{
	Vector2() = default;
	Vector2(float _x, float _y) : x(_x), y(_y) {};

	Vector2 operator+(const Vector2& v) const;
	Vector2 operator-(const Vector2& v) const;
	Vector2 operator*(const Vector2& v) const;
	Vector2 operator/(const Vector2& v) const;
	void operator+=(const Vector2& v);
	void operator-=(const Vector2& v);
	void operator*=(const Vector2& v);
	void operator/=(const Vector2& v);
	bool operator==(const Vector2& v) const;
	bool operator!=(const Vector2& v) const;

	float Length();

	float x = 0;
	float y = 0;
};

struct Transform
{
	Transform();
	Transform(Vector2 x, Vector2 y, Vector2 origin);

	Vector2 GetOrigin() { return columns[2]; }

	void Forward(Vector2 in, Vector2& out);
	Transform Identity();
	Transform Translate(Vector2 offset);
	Transform Rotate(float angle); //angle (radians)
	Transform Scale(Vector2 scale);

	Vector2 columns[3];
};