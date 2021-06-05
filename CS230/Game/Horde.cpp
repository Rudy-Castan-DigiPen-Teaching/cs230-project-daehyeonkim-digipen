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
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"

Horde::Horde(math::vec2 initPos, int hp, math::vec2 HPBarScale) : Level3Object(initPos, hp, HPBarScale), enemyGold(0), goldIncreasing(1), goldTimer(0)
{
	AddGOComponent(new CS230::RectCollision({ {0,0}, {96,192} }, this));
	AddGOComponent(new HPBar(hp, { 2, 2}));
	ChangeState(&stateWating);
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

void Horde::MakeOrc()
{
	if(enemyGold >= OrcCost)
	{
		enemyGold -= OrcCost;
		Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Grunt(GetPosition(), 200, 25, { 1,1 },{ 50, 0 }, 0.5));
	}
}

void Horde::improveIncresing()
{
	const int goldUpCost = 50 * goldIncreasing;
	if (enemyGold >= goldUpCost)
	{
		enemyGold -= goldUpCost;
		goldIncreasing++;
	}
}

void Horde::State_Wating::Enter(GameObject*)
{
}

void Horde::State_Wating::Update(GameObject*, double)
{
}

void Horde::State_Wating::TestForExit(GameObject* object)
{
	constexpr int dangerHP = 400;
	Horde* horde = static_cast<Horde*>(object);
	if(horde->enemyGold % 10 == 0 || horde->GetHP() < dangerHP)
	{
		horde->ChangeState(&horde->stateDoing);
	}
}

void Horde::State_Doing::Enter(GameObject*)
{
}

void Horde::State_Doing::Update(GameObject* object, double)
{
	Horde* horde = static_cast<Horde*>(object);
	int randomize = rand() % 99;
	if(randomize < 100)
	{
		horde->MakeOrc();
		if(randomize < 30)
		{
			horde->ChangeState(this);
		}
	} else
	{
		horde->improveIncresing();
		if (randomize >= 80)
		{
			horde->ChangeState(this);
		}
	}
}

void Horde::State_Doing::TestForExit(GameObject* object)
{
	Horde* horde = static_cast<Horde*>(object);
	horde->ChangeState(&horde->stateWating);
}
