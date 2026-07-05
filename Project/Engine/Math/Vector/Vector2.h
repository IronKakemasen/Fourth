#pragma once

struct Vector2
{
	float x = 0.0f;
	float y = 0.0f;

	Vector2(float entries[2]) : x(entries[0]), y(entries[1]) {}
	Vector2(float u_, float v_) : x(u_), y(v_) {}
	Vector2() {};
	float GetMagnitutde();
	Vector2 GetNormalized();
	float GetCos(Vector2 other_);
	float GetDot(Vector2 other_);

};

