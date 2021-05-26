/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.h
Project: CS230
Author: Daehyeon Kim
Creation date: 3/17/2021
-----------------------------------------------------------------*/
#pragma once
#include "GameObjectTypes.h"
#include "..\Engine\Input.h"
#include "../Engine/GameObject.h"
namespace math { struct vec2; }
class Ship : public CS230::GameObject {
public:
    Ship(math::vec2 startPos);
    void Update(double dt) override;
    void Draw(math::TransformMatrix cameraMatrix) override;
    GameObjectType GetObjectType() override { return GameObjectType::Ship; }
    std::string GetObjectTypeName() override { return "Ship"; }
    bool CanCollideWith(GameObjectType) override;
    bool IsDead() { return isDead; }
    void ResolveCollision(CS230::GameObject* objectB) override;
private:
    CS230::Sprite flameSpriteL;
    CS230::Sprite flameSpriteR;
    bool wasAccel;
    bool isDead;
    CS230::InputKey rotateCounterKey;
    CS230::InputKey rotateClockKey;
    CS230::InputKey accelerateKey;
    CS230::InputKey shootingKey;

    static constexpr math::vec2 accel{ 0, 400 };
    static constexpr double drag = 1.0f;
};

