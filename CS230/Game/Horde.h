/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Horde.h
Project: CS230
Author: Daehyeon Kim
Creation date: 06/04/2021
-----------------------------------------------------------------*/
#pragma once
#include "GameObjectTypes.h"
#include "Level3Object.h"

class Horde final : public Level3Object
{
private:
	static constexpr int OrcCost = 20;
	static constexpr int GunnerCost = 150;
	static constexpr int HeavyCavalryCost = 300;

	int goldIncreasing;
	int enemyGold;
	double goldTimer;
public:
	Horde(math::vec2 initPos, int hp, math::vec2 HPBarScale);
	void UpateGold(int _gold);
	void Update(double dt) override;
	GameObjectType GetObjectType() override { return GameObjectType::Horde; }
	std::string GetObjectTypeName() override { return "Horde"; }

private:
	class State_Wating : public State {
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "waiting"; }
	};
	class State_Doing : public State {
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "doing"; }
	};
	State_Wating stateWating;
	State_Doing stateDoing;

	void MakeOrc();
	void improveIncresing();
};
