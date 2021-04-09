/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 3/28/2021
-----------------------------------------------------------------*/
#include "Camera.h"
#include "TransformMatrix.h"

CS230::Camera::Camera(math::rect2 movableRange) : movableRange(movableRange), extent({{0,0}, {0,0}}), position({0,0})
{
}

void CS230::Camera::SetPosition(math::vec2 newPosition)
{
	position = newPosition;
}

const math::vec2& CS230::Camera::GetPosition() const
{
	return position;
}

void CS230::Camera::SetExtent(math::irect2 newExtent)
{
	extent = newExtent;
}

void CS230::Camera::Update(const math::vec2& followObjPos)
{
	if(followObjPos.x - position.x > movableRange.top_right.x)
	{
		position.x = followObjPos.x - movableRange.top_right.x;
	} else if(followObjPos.x - position.x < movableRange.bottom_left.x)
	{
		position.x = followObjPos.x - movableRange.bottom_left.x;
	}
	
	if (followObjPos.y - position.y > movableRange.top_right.y)
	{
		position.y = followObjPos.y - movableRange.top_right.y;
	}
	else if (followObjPos.y - position.y < movableRange.bottom_left.y)
	{
		position.y = followObjPos.y - movableRange.bottom_left.y;
	}
	
	if(position.x > extent.top_right.x)
	{
		position.x = extent.top_right.x;
	} else if(position.x < extent.bottom_left.x)
	{
		position.x = extent.bottom_left.x;
	}
	
	if (position.y > extent.top_right.y)
	{
		position.y = extent.top_right.y;
	}
	else if (position.y < extent.bottom_left.y)
	{
		position.y = extent.bottom_left.y;
	}
}

math::TransformMatrix CS230::Camera::GetMatrix()
{
	return math::TranslateMatrix(-position);
}

