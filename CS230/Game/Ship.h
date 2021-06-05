/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.h
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Input.h"
#include "..\Engine\Sprite.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Ship : public CS230::GameObject {
public:
	Ship(math::vec2 startPos);
	void Update(double dt);
	void Draw(math::TransformMatrix displayMatrix);

	GameObjectType GetObjectType() override { return GameObjectType::Ship; }
	std::string GetObjectTypeName() override { return "Ship"; }
	bool CanCollideWith(GameObjectType objectBType) override;
	void ResolveCollision(CS230::GameObject* objectB) override;

	bool IsDead() { return isDead; }
private:
	CS230::Sprite flameLeft;
	CS230::Sprite flameRight;

	bool isAccelerating;
	bool isDead;
	static constexpr double accel = 400;
	static constexpr double drag = 1;
	static constexpr double rotationRate = 2.0;

	CS230::InputKey fireLazerKey;
	CS230::InputKey rotateCounterKey;
	CS230::InputKey rotateClockKey;
	CS230::InputKey accelerateKey;
};