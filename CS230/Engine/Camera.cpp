/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#include "Engine.h"
#include "TransformMatrix.h"
#include "Camera.h"

CS230::Camera::Camera(math::rect2 movableRange) : movableRange(movableRange), position({ 0,0 }) {}

void CS230::Camera::SetPosition(math::vec2 newPosition) {
	position = newPosition;
}

const math::vec2 &CS230::Camera::GetPosition() const {
	return position;
}

void CS230::Camera::SetExtent(math::irect2 newExtent) {
	extent = newExtent;
}

void CS230::Camera::Update(const math::vec2& followObjPos) {
	if (followObjPos.x > movableRange.Right() + position.x) {
		position.x = followObjPos.x - movableRange.Right();
	}
	if (followObjPos.x - position.x < movableRange.Left()) {
		position.x = followObjPos.x - movableRange.Left();
	}

	if (position.x < extent.Left()) {
		position.x = extent.Left();
	}
	if (position.x > extent.Right()) {
		position.x = extent.Right();
	}
	if (position.y < extent.Bottom()) {
		position.y = extent.Bottom();
	}
	if (position.y > extent.Top()) {
		position.y = extent.Top();
	}
}

math::TransformMatrix CS230::Camera::GetMatrix() {
	return math::TranslateMatrix(-position);
}