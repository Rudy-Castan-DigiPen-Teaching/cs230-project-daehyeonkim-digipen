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
#include "UnitAmount.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Sprite.h"
Horde::Horde(math::vec2 initPos, int hp, math::vec2 HPBarScale) : Level3Object(initPos, hp, HPBarScale), goldIncreasing(1), enemyGold(0), goldTimer(0), unitLevel(1)
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
	if (goldTimer >= (1. / goldIncreasing))
	{
		enemyGold++;
		goldTimer = 0;
	}
	GameObject::Update(dt);
}

void Horde::MakeGrunt()
{
	UnitAmount* currentUnitAmount = Engine::GetGSComponent<UnitAmount>();
	if(enemyGold >= gruntCost && currentUnitAmount->GetEnemyUnitAmount() <= UnitAmount::unitLimit)
	{
		enemyGold -= gruntCost;
		Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Grunt(GetPosition(), 150 * unitLevel, 15 * unitLevel, { 1,1 },{ 70, 0 }, 0.5));
		currentUnitAmount->UpdateUnitAmount(0, 1);
	}
}

void Horde::MakeShaman()
{
	UnitAmount* currentUnitAmount = Engine::GetGSComponent<UnitAmount>();
	if (enemyGold >= shamanCost && currentUnitAmount->GetEnemyUnitAmount() <= UnitAmount::unitLimit)
	{
		enemyGold -= shamanCost;
		Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Shaman(GetPosition(), 120 * unitLevel, 50 * unitLevel, { 1,1 }, { 40, 0 }, 2));
		currentUnitAmount->UpdateUnitAmount(0, 1);
	}
}

void Horde::MakeTauren()
{
	UnitAmount* currentUnitAmount = Engine::GetGSComponent<UnitAmount>();
	if (enemyGold >= taurenCost && currentUnitAmount->GetEnemyUnitAmount() <= UnitAmount::unitLimit)
	{
		enemyGold -= taurenCost;
		Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Tauren(GetPosition(), 340 * unitLevel, 100 * unitLevel, { 1,1 }, { 60, 0 }, 1));
		currentUnitAmount->UpdateUnitAmount(0, 1);
	}
}

void Horde::improveUnitLevel()
{
	const int unitLevelUpcost = unitImproveCost * unitLevel;
	if (enemyGold >= unitLevelUpcost && unitLevel <= levelLimit)
	{
		enemyGold -= unitLevelUpcost;
		unitLevel++;
	}
}

void Horde::improveGoldIncresing()
{
	const int goldUpCost = goldIncreasingImproveCost * goldIncreasing;
	if (enemyGold >= goldUpCost && goldIncreasing <= levelLimit)
	{
		enemyGold -= goldUpCost/2; 
		goldIncreasing++;
	}
}

void Horde::State_EarnGold::Enter(GameObject*)
{
	produceTimer = 0;
}

void Horde::State_EarnGold::Update(GameObject*, double dt)
{
	produceTimer += dt;
}

void Horde::State_EarnGold::TestForExit(GameObject* object)
{
	Horde* horde = static_cast<Horde*>(object);
	if(horde->enemyGold % 10 == 0 && produceTimer >= produceCoolDown)
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
	if (Behavior % static_cast<int>(EnemyBehavior::upgrade) == 0)
	{
		horde->improveGoldIncresing();
		horde->improveUnitLevel();
	}
	if(Behavior % static_cast<int>(EnemyBehavior::make_unit) == 0)
	{
		horde->MakeTauren();
		horde->MakeShaman();
		horde->MakeGrunt();
	}
}

void Horde::State_Produce::TestForExit(GameObject* object)
{
	Horde* horde = static_cast<Horde*>(object);
	if (Behavior % static_cast<int>(EnemyBehavior::reProduce) == 0)
	{
		horde->ChangeState(this);
	} else
	{
		horde->ChangeState(&horde->stateEarnGold);
	}
}
