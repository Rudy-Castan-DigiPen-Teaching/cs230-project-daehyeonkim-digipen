/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 5/03/2021
-----------------------------------------------------------------*/
#include "Collision.h"
#include "TransformMatrix.h"
#include "GameObject.h"
#include <doodle/drawing.hpp>


void CS230::RectCollision::Draw(math::TransformMatrix cameraMatrix) {
    doodle::no_fill();
    doodle::set_outline_width(2);
    doodle::set_outline_color(doodle::HexColor(0xFFFFFFFF));
    doodle::push_settings();
    math::rect2 displayRect = GetWorldCoorRect();
    doodle::apply_matrix(cameraMatrix[0][0], cameraMatrix[1][0], cameraMatrix[0][1], cameraMatrix[1][1], cameraMatrix[0][2], cameraMatrix[1][2]);
    doodle::draw_rectangle(displayRect.Left(), displayRect.Bottom(), displayRect.Size().x, displayRect.Size().y);
    doodle::pop_settings();
}

void CS230::CircleCollision::Draw(math::TransformMatrix cameraMatrix) {
    doodle::no_fill();
    doodle::set_outline_width(2);
    doodle::set_outline_color(doodle::HexColor(0xFFFFFFFF));
    doodle::push_settings();
    doodle::apply_matrix(cameraMatrix[0][0], cameraMatrix[1][0], cameraMatrix[0][1], cameraMatrix[1][1], cameraMatrix[0][2], cameraMatrix[1][2]);
    doodle::draw_ellipse(objectPtr->GetPosition().x, objectPtr->GetPosition().y, GetRadius() * 2);
    doodle::pop_settings();
}


math::rect2 CS230::RectCollision::GetWorldCoorRect()
{
    math::rect2 collisionRect = math::rect2(rect);
    const math::TransformMatrix objectMatrix = objectPtr->GetMatrix();
    collisionRect.point1 = objectMatrix * collisionRect.point1;
    collisionRect.point2 = objectMatrix * collisionRect.point2;
    return collisionRect;
}

bool CS230::RectCollision::DoesCollideWith(GameObject* objectB)
{
    if(GetWorldCoorRect().Left() <= objectB->GetGOComponent<RectCollision>()->GetWorldCoorRect().Right() && GetWorldCoorRect().Right() >= objectB->GetGOComponent<RectCollision>()->GetWorldCoorRect().Left() &&
        GetWorldCoorRect().Bottom() <= objectB->GetGOComponent<RectCollision>()->GetWorldCoorRect().Top() && GetWorldCoorRect().Top() >= objectB->GetGOComponent<RectCollision>()->GetWorldCoorRect().Bottom())
    {
        return true;
    }
    return false;
}

double CS230::CircleCollision::GetRadius()
{
    return radius * objectPtr->GetScale().x;
}

bool CS230::CircleCollision::DoesCollideWith(GameObject* objectB)
{
    const double xDistance = objectPtr->GetPosition().x - objectB->GetPosition().x;
    const double yDistance = objectPtr->GetPosition().y - objectB->GetPosition().y;
    const double totalRadius = objectPtr->GetGOComponent<CircleCollision>()->GetRadius() + objectB->GetGOComponent<CircleCollision>()->GetRadius();
	if(xDistance*xDistance + yDistance*yDistance <= totalRadius*totalRadius)
	{
        return true;
	}
    return false;
}
