/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Bullet.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/21/2021
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "Bullet.h"
#include "Gravity.h"
#include "Level3Object.h"
#include "../Engine/Collision.h"
#include "../Engine/GameObjectManager.h"

Bullet::Bullet(math::vec2 pos, double rotation, math::vec2 scale, math::vec2 velocity, int ad) : GameObject(pos, rotation, scale), ad(ad), floor(nullptr)
{
    SetVelocity(GetMatrix() * velocity);
    AddGOComponent(new CS230::Sprite("assets/prince/bomb.spt", this));
    for (GameObject* obj : Engine::GetGSComponent<CS230::GameObjectManager>()->Objects())
    {
    	if(obj->GetObjectType() == GameObjectType::Floor)
    	{
            floor = obj;
    	}
    }

}

void Bullet::Update(double dt) {
    UpdateVelocity({ 0, -Engine::GetGSComponent<Gravity>()->GetValue() * dt });
    GameObject::Update(dt);
    const double radius = GetGOComponent<CS230::CircleCollision>()->GetRadius();
    if (GetPosition().x > Engine::GetWindow().GetSize().x + radius) {
        Destroy();
        return;
    }
    else if (GetPosition().x < 0 - radius) {
        Destroy();
        return;
    }
	if(floor->GetGOComponent<CS230::RectCollision>()->DoesCollideWith(GetPosition()) == true)
	{
        ResolveCollision(nullptr);
	}
}

void Bullet::ResolveCollision(GameObject*) {
	for (GameObject* obj : Engine::GetGSComponent<CS230::GameObjectManager>()->Objects())
	{
		if (GetGOComponent<CS230::CircleCollision>()->DoesCollideWith(obj->GetPosition()) == true)
		{
            Level3Object* affectObj = dynamic_cast<Level3Object*>(obj);
			if(affectObj != nullptr)
			{
                affectObj->UpdateHP(-ad);
			}
		}
	}
	Destroy();
}