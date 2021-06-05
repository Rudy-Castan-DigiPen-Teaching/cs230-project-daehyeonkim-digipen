/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Laser.h
Project: CS230
Author: Kevin Wright
Creation date: 2/21/2021
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "Laser.h"

Laser::Laser(math::vec2 pos, double rotation, math::vec2 scale, math::vec2 velocity) : GameObject(pos, rotation, scale) {
    SetVelocity(velocity);
    AddGOComponent(new CS230::Sprite("assets/Laser.spt", this));
}

void Laser::Update(double dt) {
    GameObject::Update(dt);

    if (GetPosition().y > Engine::GetWindow().GetSize().y + GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0) {
        Destroy();
        return;
    } else if (GetPosition().y < 0 - GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0) {
        Destroy();
        return;
    }
    if (GetPosition().x > Engine::GetWindow().GetSize().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0) {
        Destroy();
        return;
    } else if (GetPosition().x < 0 - GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0) {
        Destroy();
        return;
    }
}

bool Laser::CanCollideWith(GameObjectType objectBType) {
    if (objectBType == GameObjectType::Meteor || objectBType == GameObjectType::EnemyShip) {
        return true;
    } else {
        return false;
    }
}

void Laser::ResolveCollision(GameObject* objectB) {
    Destroy();
    objectB->ResolveCollision(this);
}