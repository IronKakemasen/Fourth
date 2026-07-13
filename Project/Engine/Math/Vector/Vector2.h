#pragma once

struct Vector2
{
	float x{};
	float y{};

	Vector2(std::array<float,2> entries_) : x(entries_[0]), y(entries_[1]) {}
	Vector2(float x_, float y_) : x(x_), y(y_) {}
	Vector2() {};
	float GetMagnitutde();
	Vector2 GetNormalized();
	float GetCos(Vector2 other_);
	float GetDot(Vector2 other_);

};

