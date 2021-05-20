/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Laser.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 5/20/2021
-----------------------------------------------------------------*/
#include "Laser.h"

#include "../Engine/Engine.h"

Laser::Laser(math::vec2 pos, double rotation, math::vec2 scale, math::vec2 laserVelocity) : GameObject(pos,rotation,scale)
{
	AddGOComponent(new CS230::Sprite("assets/Laser.spt", this));
	SetVelocity(math::RotateMatrix(GetRotation()) * laserVelocity);
}

void Laser::Update(double dt)
{
	GameObject::Update(dt);
	const double x_limit = Engine::GetWindow().GetSize().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0;
	const double y_limit = Engine::GetWindow().GetSize().y + GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0;
	if (GetPosition().x > x_limit || GetPosition().x < -GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2 || GetPosition().y > y_limit || GetPosition().y < -GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2)
	{
		destroyed = true;
	}
}

bool Laser::CanCollideWith(GameObjectType objectBType)
{
	if(objectBType == GameObjectType::Meteor)
	{
		return true;
	}
	return false;
}

void Laser::ResolveCollision(GameObject* objectB)
{
	switch (objectB->GetObjectType())
	{
	case GameObjectType::Meteor:
		objectB->ResolveCollision(this);
		destroyed = true;
		break;
	}
}
