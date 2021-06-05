/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Knight.h
Project: CS230
Author: Daehyeon Kim
Creation date: 06/04/2021
-----------------------------------------------------------------*/
#pragma once
#include "../Engine/GameObject.h"
#include "GameObjectTypes.h"

class Knight : public CS230::GameObject
{
private:
	int hp;
	int ad;
	static constexpr int cost = 100;
	static constexpr math::vec2 speed{ 50, 0 };
	GameObject* CollideWithWhat;
public:
	Knight(int hp, int ad, math::vec2 position);
	GameObjectType GetObjectType() override { return GameObjectType::Knight; }
	std::string GetObjectTypeName() override { return "Knight"; }
	void ResolveCollision(GameObject* objectA) override;
	//void Update(double dt) override;
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
	//class State_WalkingAttack : public State {
	//public:
	//	void Enter(GameObject* object) override;
	//	void Update(GameObject* object, double dt) override;
	//	void TestForExit(GameObject* object) override;
	//	std::string GetName() override { return "walking_attack"; }
	//};
	class State_Waiting : public State {
	public:
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "waiting"; }
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
	//State_WalkingAttack stateWalkingAttack;
	State_Waiting stateWaiting;
	State_Dead stateDead;
};
