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
	static constexpr int gruntCost = 10;
	static constexpr int shamanCost = 15;
	static constexpr int taurenCost = 50;
	static constexpr int goldIncreasingImproveCost = 15;
	static constexpr int unitImproveCost = 30;

	int whenEnemyFeelDangerHP;
	
	int goldIncreasing;
	int enemyGold;
	double goldTimer;
	int unitLevel;
public:
	Horde(math::vec2 initPos, int hp, math::vec2 HPBarScale);
	void UpateGold(int _gold);
	void Update(double dt) override;
	GameObjectType GetObjectType() override { return GameObjectType::Horde; }
	std::string GetObjectTypeName() override { return "Horde"; }

private:
	class State_EarnGold : public State {
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "earngold"; }
		static constexpr double produceCoolDown = 3;
		double produceTimer;
	};
	class State_Produce : public State {
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "produce"; }
		int Behavior;
		enum class EnemyBehavior
		{
			do_nothing = 2,
			make_unit,
			upgrade,
			reProduce,
			count
		};
	};
	State_EarnGold stateEarnGold;
	State_Produce stateProduce;

	void MakeGrunt();
	void MakeShaman();
	void MakeTauren();
	void improveGoldIncresing();
	void improveUnitLevel();
};
