/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Horde.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 06/04/2021
-----------------------------------------------------------------*/
#include "Horde.h"
#include "Grunt.h"
#include "HPBar.h"
#include "Shaman.h"
#include "Tauren.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Sprite.h"
Horde::Horde(math::vec2 initPos, int hp, math::vec2 HPBarScale) : Level3Object(initPos, hp, HPBarScale), goldIncreasing(1), enemyGold(0), goldTimer(0), unitLevel(0), whenEnemyRageHP(static_cast<int>(hp / 5))
{
	AddGOComponent(new CS230::Sprite("assets/LEVEL3/enemyBase.spt", this));
	AddGOComponent(new HPBar(hp, { 2, 2}));
	ChangeState(&stateEarnGold);
}

void Horde::UpateGold(int _gold)
{
	enemyGold += _gold;
}

void Horde::Update(double dt)
{
	goldTimer += dt;
	if (goldTimer >= (1 / goldIncreasing))
	{
		enemyGold++;
		goldTimer = 0;
	}
	GameObject::Update(dt);
}

void Horde::MakeGrunt()
{
	if(enemyGold >= GruntCost)
	{
		enemyGold -= GruntCost;
		Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Grunt(GetPosition(), 200, 25 * unitLevel, { 1,1 },{ 50, 0 }, 0.5));
	}
}

void Horde::MakeShaman()
{
	if (enemyGold >= ShamanCost)
	{
		enemyGold -= ShamanCost;
		Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Shaman(GetPosition(), 160, 50 * unitLevel, { 1,1 }, { 50, 0 }, 2));
	}
}

void Horde::MakeTauren()
{
	if (enemyGold >= TaurenCost)
	{
		enemyGold -= TaurenCost;
		Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Tauren(GetPosition(), 400, 100 * unitLevel, { 1,1 }, { 50, 0 }, 3));
	}
}

void Horde::improveUnitLevel()
{
	const int unitLevelUpcost = unitImproveCost * unitLevel;
	if (enemyGold >= unitLevelUpcost)
	{
		enemyGold -= unitLevelUpcost;
		unitLevel++;
	}
}

void Horde::improveIncresing()
{
	const int goldUpCost = goldIncreasingImproveCost * goldIncreasing;
	if (enemyGold >= goldUpCost)
	{
		enemyGold -= goldUpCost;
		goldIncreasing++;
	}
}

void Horde::State_EarnGold::Enter(GameObject*)
{
}

void Horde::State_EarnGold::Update(GameObject*, double)
{
}

void Horde::State_EarnGold::TestForExit(GameObject* object)
{
	constexpr int dangerHP = 400;
	Horde* horde = static_cast<Horde*>(object);
	if(horde->enemyGold % 10 == 0 || horde->GetHP() < dangerHP)
	{
		horde->ChangeState(&horde->stateProduce);
	}
}

void Horde::State_Produce::Enter(GameObject*)
{
	Behavior = rand() % 99;
}

void Horde::State_Produce::Update(GameObject* object, double)
{
	Horde* horde = static_cast<Horde*>(object);
	if (Behavior % static_cast<int>(EnemyBehavior::upgrade))
	{
		horde->improveIncresing();
		horde->improveUnitLevel();
	}
	if(Behavior % static_cast<int>(EnemyBehavior::make_unit))
	{
		horde->MakeTauren();
		horde->MakeShaman();
		horde->MakeGrunt();
	}
}

void Horde::State_Produce::TestForExit(GameObject* object)
{
	Horde* horde = static_cast<Horde*>(object);
	if (Behavior % static_cast<int>(EnemyBehavior::reProduce) || horde->GetHP() <= horde->whenEnemyRageHP)
	{
		horde->ChangeState(&horde->stateEarnGold);
	} else
	{
		horde->ChangeState(this);
	}
}
