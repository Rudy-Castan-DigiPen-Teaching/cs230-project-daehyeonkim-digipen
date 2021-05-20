/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vec2.h
Author: Daehyeon Kim
Creation date: 03.15.2021
-----------------------------------------------------------------*/
#pragma once
#include <limits>
#include <algorithm>
namespace math
{
	[[nodiscard]] constexpr double abs(double d) noexcept { return (d < 0.0) ? -d : d; }

	[[nodiscard]] constexpr bool is_equal(double d1, double d2) noexcept
	{
		return abs(d1 - d2) <= std::numeric_limits<double>::epsilon() * abs(d1 + d2);
	}

	[[nodiscard]] constexpr bool is_equal(int i1, int i2) noexcept { return i1 == i2; }

	struct [[nodiscard]] vec2
	{
		double x = 0;
		double y = 0;
		[[nodiscard]] constexpr vec2() noexcept = default;
		[[nodiscard]] constexpr vec2(const double inputX, const double inputY) noexcept : vec2()
		{
			x = inputX, y = inputY;
		}
		constexpr vec2& operator+=(vec2) noexcept;
		constexpr vec2& operator-=(vec2) noexcept;
		constexpr vec2& operator*=(double) noexcept;
		constexpr vec2& operator/=(double) noexcept;
		[[nodiscard]] constexpr double LengthSquared() const noexcept;
		[[nodiscard]] constexpr vec2 Normalize() const noexcept;
	};


	struct [[nodiscard]] ivec2
	{
		int x = 0;
		int y = 0;
		[[nodiscard]] constexpr ivec2() noexcept = default;
		[[nodiscard]] constexpr ivec2(const int inputX, const int inputY) noexcept : ivec2()
		{
			x = inputX;
			y = inputY;
		}
		constexpr ivec2& operator+=(ivec2) noexcept;
		constexpr ivec2& operator-=(ivec2) noexcept;
		constexpr ivec2& operator*=(int) noexcept;
		constexpr ivec2& operator/=(int) noexcept;
		[[nodiscard]] constexpr operator vec2()  noexcept;
	};
}

#include "Vec2.inl"
