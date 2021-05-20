/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vec2.inl
Author: Daehyeon Kim
Creation date: 03.15.2021
-----------------------------------------------------------------*/

namespace math
{
	[[nodiscard]] constexpr vec2 operator+(const vec2 left, const vec2 right) noexcept
	{
		const double returnX = left.x + right.x;
		const double returnY = left.y + right.y;
		return vec2{ returnX, returnY };
	}

	constexpr vec2& vec2::operator+=(const vec2 right) noexcept
	{
		*this = *this + right;
		return *this;
	}

	[[nodiscard]] constexpr vec2 operator-(const vec2 left, const vec2 right) noexcept
	{
		const double returnX = left.x - right.x;
		const double returnY = left.y - right.y;
		return vec2{ returnX, returnY };
	}

	constexpr vec2& vec2::operator-=(const vec2 right) noexcept
	{
		*this = *this - right;
		return *this;
	}

	[[nodiscard]] constexpr vec2 operator-(const vec2 left) noexcept
	{
		const double returnX = -left.x;
		const double returnY = -left.y;
		return vec2(returnX, returnY);
	}

	[[nodiscard]] constexpr vec2 operator*(const vec2 left, const double right) noexcept
	{
		const double returnX = left.x * right;
		const double returnY = left.y * right;
		return vec2(returnX, returnY);
	}

	[[nodiscard]] constexpr vec2 operator*(const double left, const vec2 right) noexcept
	{
		const double returnX = left * right.x;
		const double returnY = left * right.y;
		return vec2(returnX, returnY);
	}

	[[nodiscard]] constexpr vec2 operator*(const vec2 left, const vec2 right) noexcept
	{
		const double returnX = left.x * right.x;
		const double returnY = left.y * right.y;
		return vec2(returnX, returnY);
	}
	
	constexpr vec2& vec2::operator*=(const double input) noexcept
	{
		*this = *this * input;
		return *this;
	}

	[[nodiscard]] constexpr vec2 operator/(const vec2 left, const double right) noexcept
	{
		const double returnX = left.x / right;
		const double returnY = left.y / right;
		return vec2(returnX, returnY);
	}

	constexpr vec2& vec2::operator/=(const double input) noexcept
	{
		*this = *this / input;
		return *this;
	}

	[[nodiscard]] constexpr bool operator==(const vec2 left, const vec2 right) noexcept
	{
		return is_equal(left.x, right.x) && is_equal(left.y, right.y);
	}

	[[nodiscard]] constexpr bool operator!=(const vec2 left, const vec2 right) noexcept
	{
		return !is_equal(left.x, right.x) || !is_equal(left.y, right.y);
	}

	[[nodiscard]] constexpr double vec2::LengthSquared() const noexcept
	{
		const double returnX = this->x * this->x;
		const double returnY = this->y * this->y;
		return 	returnX + returnY;
	}

	[[nodiscard]] constexpr vec2 vec2::Normalize() const noexcept
	{
		return vec2(*this / sqrt(LengthSquared()));
	}

	[[nodiscard]] constexpr ivec2 operator+(const ivec2 left, const ivec2 right) noexcept
	{
		const int returnX = left.x + right.x;
		const int returnY = left.y + right.y;
		return ivec2{ returnX, returnY };
	}

	constexpr ivec2& ivec2::operator+=(const ivec2 right) noexcept
	{
		*this = *this + right;
		return *this;
	}

	[[nodiscard]] constexpr ivec2 operator-(const ivec2 left, const ivec2 right) noexcept
	{
		const int returnX = left.x - right.x;
		const int returnY = left.y - right.y;
		return ivec2{ returnX, returnY };
	}

	constexpr ivec2& ivec2::operator-=(const ivec2 right) noexcept
	{
		*this = *this - right;
		return *this;
	}

	[[nodiscard]] constexpr ivec2 operator-(const ivec2 right) noexcept
	{
		const int returnX = -right.x;
		const int returnY = -right.y;
		return ivec2(returnX, returnY);
	}

	[[nodiscard]] constexpr ivec2 operator*(const ivec2 left, const int right) noexcept
	{
		const int returnX = left.x * right;
		const int returnY = left.y * right;
		return ivec2(returnX, returnY);
	}

	[[nodiscard]] constexpr ivec2 operator*(const int left, const ivec2 right) noexcept
	{
		const int returnX = left * right.x;
		const int returnY = left * right.y;
		return ivec2(returnX, returnY);
	}

	[[nodiscard]] constexpr vec2 operator*(const ivec2 left, const double right) noexcept
	{
		const double returnX = left.x * right;
		const double returnY = left.y * right;
		return vec2(returnX, returnY);
	}

	[[nodiscard]] constexpr vec2 operator*(const double left, const ivec2 right) noexcept
	{
		const double returnX = left * right.x;
		const double returnY = left * right.y;
		return vec2(returnX, returnY);
	}

	constexpr ivec2& ivec2::operator*=(const int input) noexcept
	{
		*this = *this * input;
		return *this;
	}

	[[nodiscard]] constexpr ivec2 operator/(const ivec2 left, const int right) noexcept
	{
		const int returnX = left.x / right;
		const int returnY = left.y / right;
		return ivec2(returnX, returnY);
	}

	[[nodiscard]] constexpr vec2 operator/(const ivec2 left, const double right) noexcept
	{
		const double returnX = left.x / right;
		const double returnY = left.y / right;
		return vec2(returnX, returnY);
	}

	constexpr ivec2& ivec2::operator/=(const int input) noexcept
	{
		*this = *this / input;
		return *this;
	}

	[[nodiscard]] constexpr bool operator==(const ivec2 left, const ivec2 right) noexcept
	{
		return is_equal(left.x, right.x) && is_equal(left.y, right.y);
	}

	[[nodiscard]] constexpr bool operator!=(const ivec2 left, const ivec2 right) noexcept
	{
		return !is_equal(left.x, right.x) || !is_equal(left.y, right.y);
	}

	[[nodiscard]] constexpr ivec2::operator vec2()  noexcept
	{
		vec2 returnVec = vec2(static_cast<double>(this->x), static_cast<double>(this->y));
		return returnVec;
	}
}
