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
	static constexpr int GruntCost = 20;
	static constexpr int ShamanCost = 30;
	static constexpr int TaurenCost = 100;
	static constexpr int goldIncreasingImproveCost = 50;
	static constexpr int unitImproveCost = 50;

	int whenEnemyRageHP;
	
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
	};
	class State_Produce : public State {
		void Enter(GameObject* object) override;
		void Update(GameObject* object, double dt) override;
		void TestForExit(GameObject* object) override;
		std::string GetName() override { return "produce"; }
		int Behavior = 0;
		enum class EnemyBehavior
		{
			do_nothing = 1,
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
	void improveIncresing();
	void improveUnitLevel();
};
