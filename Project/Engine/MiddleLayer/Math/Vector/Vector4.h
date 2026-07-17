#pragma once


///CPU⇔GPUデータ間のやり取りで使う
///データアライメント揃えるの汚いしバグの温床なんで
template<typename T>
struct Vector4
{
	T x{};
	T y{};
	T z{};
	T w{};

	Vector4(std::array<T,4> entries) : x(entries[0]), y(entries[1]), z(entries[2]), w(entries[3]) {}
	Vector4(T x_, T y_, T z_, T w_) : x(x_), y(y_), z(z_), w(w_) {}
	Vector4() {}

};

