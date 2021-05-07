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
	if(followObjPos.x - position.x > movableRange.Right())
	{
		position.x = followObjPos.x - movableRange.Right();
	} else if(followObjPos.x - position.x < movableRange.Left())
	{
		position.x = followObjPos.x - movableRange.Left();
	}
	if (followObjPos.y - position.y > movableRange.Top())
	{
		position.y = followObjPos.y - movableRange.Top();
	}
	else if (followObjPos.y - position.y < movableRange.Bottom())
	{
		position.y = followObjPos.y - movableRange.Bottom();
	}
	if(position.x > extent.Right())
	{
		position.x = extent.Right();
	} else if(position.x < extent.Left())
	{
		position.x = extent.Left();
	}
	if (position.y > extent.Top())
	{
		position.y = extent.Top();
	}
	else if (position.y < extent.Bottom())
	{
		position.y = extent.Bottom();
	}
}

math::TransformMatrix CS230::Camera::GetMatrix()
{
	return math::TranslateMatrix(-position); 
}

