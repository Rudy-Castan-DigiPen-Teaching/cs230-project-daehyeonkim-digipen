/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Floor.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/19/2021
-----------------------------------------------------------------*/

#include "..\Engine\Collision.h"
#include "..\Engine\Rect.h"
#include "GameObjectTypes.h"
#include "Floor.h"

Floor::Floor(math::irect2 rect) : GameObject(static_cast<math::vec2>(rect.point1)) {
    AddGOComponent(new CS230::RectCollision({ math::ivec2{ 0, 0 }, rect.Size() }, this));
}