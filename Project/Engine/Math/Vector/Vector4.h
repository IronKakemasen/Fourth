#pragma once


///CPU⇔GPUデータ間のやり取りで使う
///データアライメント揃えるの汚いしバグの温床なんで
///operatorはAIに出力してもらいました
#pragma once

#include <array>
#include <cstddef>
#include <type_traits>

template<typename T>
struct Vector4
{
    T x{};
    T y{};
    T z{};
    T w{};

    constexpr Vector4() = default;

    constexpr Vector4(T x_, T y_, T z_, T w_)
        : x(x_), y(y_), z(z_), w(w_)
    {
    }

    constexpr Vector4(const std::array<T, 4>& entries)
        : x(entries[0]), y(entries[1]), z(entries[2]), w(entries[3])
    {
    }

    constexpr T& operator[](std::size_t index)
    {
        return (&x)[index];
    }

    constexpr const T& operator[](std::size_t index) const
    {
        return (&x)[index];
    }

    constexpr Vector4 operator+() const
    {
        return *this;
    }

    constexpr Vector4 operator-() const
    {
        return Vector4(-x, -y, -z, -w);
    }

    constexpr Vector4& operator+=(const Vector4& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }

    constexpr Vector4& operator-=(const Vector4& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
    }

    template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator*(U scalar) const
        -> Vector4<std::common_type_t<T, U>>
    {
        using R = std::common_type_t<T, U>;
        return Vector4<R>(
            static_cast<R>(x) * static_cast<R>(scalar),
            static_cast<R>(y) * static_cast<R>(scalar),
            static_cast<R>(z) * static_cast<R>(scalar),
            static_cast<R>(w) * static_cast<R>(scalar)
        );
    }

    template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr auto operator/(U scalar) const
        -> Vector4<std::common_type_t<T, U>>
    {
        using R = std::common_type_t<T, U>;
        return Vector4<R>(
            static_cast<R>(x) / static_cast<R>(scalar),
            static_cast<R>(y) / static_cast<R>(scalar),
            static_cast<R>(z) / static_cast<R>(scalar),
            static_cast<R>(w) / static_cast<R>(scalar)
        );
    }

    template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr Vector4& operator*=(U scalar)
    {
        x = static_cast<T>(x * scalar);
        y = static_cast<T>(y * scalar);
        z = static_cast<T>(z * scalar);
        w = static_cast<T>(w * scalar);
        return *this;
    }

    template<typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
    constexpr Vector4& operator/=(U scalar)
    {
        x = static_cast<T>(x / scalar);
        y = static_cast<T>(y / scalar);
        z = static_cast<T>(z / scalar);
        w = static_cast<T>(w / scalar);
        return *this;
    }

    constexpr bool operator==(const Vector4& rhs) const
    {
        return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
    }

    constexpr bool operator!=(const Vector4& rhs) const
    {
        return !(*this == rhs);
    }
};

template<typename T>
constexpr Vector4<T> operator+(Vector4<T> lhs, const Vector4<T>& rhs)
{
    lhs += rhs;
    return lhs;
}

template<typename T>
constexpr Vector4<T> operator-(Vector4<T> lhs, const Vector4<T>& rhs)
{
    lhs -= rhs;
    return lhs;
}

template<typename U, typename T, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
constexpr auto operator*(U scalar, const Vector4<T>& vector)
-> Vector4<std::common_type_t<T, U>>
{
    return vector * scalar;
}
