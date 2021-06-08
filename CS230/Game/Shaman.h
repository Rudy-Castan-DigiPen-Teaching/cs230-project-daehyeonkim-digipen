/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Shaman.h
Project: CS230
Author: Daehyeon Kim
Creation date: 06/08/2021
-----------------------------------------------------------------*/
#pragma once
#include "Level3Object.h"
#include "GameObjectTypes.h"

class Shaman final : public Level3Object
{
private:
	Level3Object* AttackWho;
	int ad;
	math::vec2 speed;
	double attackTimer;
	double attackSpeed;
public:
	Shaman(math::vec2 position, int hp, int ad, math::vec2 HPBarScale, math::vec2 movementSpeed, double attackSpeed);
	GameObjectType GetObjectType() override { return GameObjectType::Shaman; }
	std::string GetObjectTypeName() override { return "Shaman"; }
private:
	class State_Walking : public State {
	public:
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "walking"; }
	};
	class State_Attack : public State {
	public:
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "attack"; }
	};
	class State_Dead : public State {
	public:
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "dead"; }
	};
	State_Walking stateWalking;
	State_Attack stateAttack;
	State_Dead stateDead;
};
