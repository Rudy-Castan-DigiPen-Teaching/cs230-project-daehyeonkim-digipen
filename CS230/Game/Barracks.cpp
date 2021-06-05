/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Barracks.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 06/04/2021
-----------------------------------------------------------------*/
#include "Barracks.h"


#include "Knight.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"

Barracks::Barracks(int hp) : GameObject({0,0}) ,hp(hp), gold(0), goldIncreasing(1), goldTimer(0)
{
	AddGOComponent(new CS230::RectCollision({ {0,0}, {96,192} }, this));
}

void Barracks::UpdateHP(int _hp)
{
	hp += _hp;
}

void Barracks::SetHP(int _hp)
{
	hp = _hp;
}

void Barracks::Update(double dt)
{
	goldTimer += dt;
	if(goldTimer >= (1 / goldIncreasing))
	{
		gold++;
	}
}

bool Barracks::CanCollideWith(GameObjectType)
{
	return true;
}

void Barracks::ResolveCollision(GameObject*)
{
}

void Barracks::MakeKnight()
{
	Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Knight(100, 10, GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Center()));
}


