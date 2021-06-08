/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Bullet.h
Project: CS230
Author: Kevin Wright
Creation date: 2/21/2021
-----------------------------------------------------------------*/

#pragma once
#include "GameObjectTypes.h"
#include "../Engine/GameObject.h"

class Bullet : public CS230::GameObject {
public:
    Bullet(math::vec2 pos, double rotation, math::vec2 scale, math::vec2 velocity, int ad);
    void Update(double dt) override;
    std::string GetObjectTypeName() override { return "Bullet"; }
    GameObjectType GetObjectType() override { return GameObjectType::Bullet; }
    void ResolveCollision(GameObject* objectB) override;
private:
    GameObject* floor;
    int ad;
};
