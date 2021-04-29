/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Rect.h
Project: CS230
Author: Daehyeon Kim
Creation date: 3/28/2021
-----------------------------------------------------------------*/
#pragma once
#include "Vec2.h"

namespace math
{
	struct rect2
	{
		math::vec2 bottom_left{ 0, 0 };
		math::vec2 top_right{ 0, 0 };
		constexpr vec2 Size() const noexcept { return { top_right.x - bottom_left.x, std::abs(top_right.y - bottom_left.y) }; }
	};

	struct irect2
	{
		math::ivec2 bottom_left{ 0, 0 };
		math::ivec2 top_right{ 0, 0 };
		constexpr ivec2 Size() const noexcept { return { top_right.x - bottom_left.x, std::abs(top_right.y - bottom_left.y) }; }
	};
}
