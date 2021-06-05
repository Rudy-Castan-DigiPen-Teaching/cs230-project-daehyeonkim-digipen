/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Alliance.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 06/04/2021
-----------------------------------------------------------------*/
#include "Alliance.h"
#include "Gold.h"
#include "Footman.h"
#include "HPBar.h"
#include "Rifleman.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"

Alliance::Alliance(math::vec2 initPos, int hp, math::vec2 HPBarScale, double attackSpeed) : Level3Object(initPos, hp, HPBarScale), goldIncreasing(1), goldTimer(0),attackSpeed(attackSpeed), attackTimer(attackTimer), footmanKey(CS230::InputKey::Keyboard::A), riflemanKey(CS230::InputKey::Keyboard::S), knightKey(CS230::InputKey::Keyboard::D), goldEarnKey(CS230::InputKey::Keyboard::Z), shootDamageKey(CS230::InputKey::Keyboard::X), shootSpeedKey(CS230::InputKey::Keyboard::C), shootKey(CS230::InputKey::Keyboard::Space)
{
	AddGOComponent(new CS230::RectCollision({ {0,0}, {96,192} }, this));
	AddGOComponent(new HPBar(hp, { 2, 2 }));
}

void Alliance::Update(double dt)
{
	goldTimer += dt;
	attackTimer += dt;
	if(goldTimer >= (1. / goldIncreasing))
	{
		Engine::GetGSComponent<Gold>()->UpdateGold(1);
		goldTimer = 0;
	}
	unsigned int gold = Engine::GetGSComponent<Gold>()->GetGold();
	const unsigned int goldUpCost = 50 * goldIncreasing;
	if(footmanKey.IsKeyReleased() && gold >= FootmanCost)
	{
		MakeFootman();
	}
	if(riflemanKey.IsKeyReleased() && gold >= RiflemanCost)
	{
		MakeRifleman();
	}
	if(goldEarnKey.IsKeyReleased() && gold >= goldUpCost)
	{
		improveIncresing();
	}
	if(shootKey.IsKeyDown() && attackTimer >= 1. / attackSpeed)
	{
		Shoot();
	}
}

void Alliance::Shoot()
{
	
}

void Alliance::MakeFootman()
{
	Engine::GetGSComponent<Gold>()->UpdateGold(-FootmanCost);
	Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Footman(GetPosition(), 100, 10, {0.7,0.7}, { 50, 0 }, 0.5));
}

void Alliance::MakeRifleman()
{
	Engine::GetGSComponent<Gold>()->UpdateGold(-RiflemanCost);
	Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Rifleman(GetPosition(), 100, 30, { 0.7,0.7 }, { 50, 0 }, 1.5));
}

void Alliance::improveIncresing()
{
	Engine::GetGSComponent<Gold>()->UpdateGold(-50 * goldIncreasing);
	goldIncreasing++;
}