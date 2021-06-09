/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Bomb.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/21/2021
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "Bomb.h"

#include "GameParticles.h"
#include "Gravity.h"
#include "Level3Object.h"
#include "../Engine/Collision.h"
#include "../Engine/GameObjectManager.h"

Bomb::Bomb(math::vec2 pos, double rotation, math::vec2 scale, math::vec2 velocity, int ad) : GameObject(pos, 0, scale), attackDamage(ad), floor(nullptr)
{
    SetVelocity(math::RotateMatrix(rotation) * velocity);
    AddGOComponent(new CS230::Sprite("assets/LEVEL3/bomb.spt", this));
    for (GameObject* obj : Engine::GetGSComponent<CS230::GameObjectManager>()->Objects())
    {
    	if(obj->GetObjectType() == GameObjectType::Floor)
    	{
            floor = obj;
    	}
    }

}

void Bomb::Update(double dt) {
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

void Bomb::ResolveCollision(GameObject*) {
	for (GameObject* obj : Engine::GetGSComponent<CS230::GameObjectManager>()->Objects())
	{
		if (GetGOComponent<CS230::CircleCollision>()->DoesCollideWith(obj->GetPosition()) == true)
		{
            Level3Object* affectObj = dynamic_cast<Level3Object*>(obj);
			if(affectObj != nullptr)
			{
                affectObj->UpdateHP(-attackDamage);
			}
		}
	}
    Engine::GetGameStateManager().GetGSComponent<BombBoomEmitter>()->Emit(1, GetPosition(), { 0, 0 }, { 0,0 }, 0);
	Destroy();
}