/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ball.h
Project: CS230
Author: Kevin Wright
Creation date: 2/14/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Ball : public CS230::GameObject {
public:
	Ball(math::vec2 startPos);
	GameObjectType GetObjectType() override { return GameObjectType::Ball; }
	std::string GetObjectTypeName() override { return "Ball"; }

	bool CanCollideWith(GameObjectType objectBType) override;
	void ResolveCollision(GameObject* objectB) override;
private:
	class State_Bounce : public State {
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "bounce"; }
	};
	class State_Land : public State {
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "land"; }
	};
	State_Bounce stateBounce;
	State_Land stateLand;

	static constexpr double bounceVelocity = 700;
};