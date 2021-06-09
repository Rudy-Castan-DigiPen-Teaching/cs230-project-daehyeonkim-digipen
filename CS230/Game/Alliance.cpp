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
#include "Bullet.h"
#include "Gold.h"
#include "Footman.h"
#include "HPBar.h"
#include "Knight.h"
#include "Rifleman.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
Alliance::Alliance(math::vec2 initPos, int hp, math::vec2 HPBarScale, int ad, double attackSpeed, math::vec2 speed) : Level3Object(initPos, hp, HPBarScale), goldIncreasing(1), goldTimer(0),attackSpeed(attackSpeed), attackTimer(0), ad(ad), speed(speed), angle(0), footmanKey(CS230::InputKey::Keyboard::A), riflemanKey(CS230::InputKey::Keyboard::S), knightKey(CS230::InputKey::Keyboard::D), goldEarnKey(CS230::InputKey::Keyboard::G), shootDamageKey(CS230::InputKey::Keyboard::Z), shootSpeedKey(CS230::InputKey::Keyboard::X), bulletSpeedKey(CS230::InputKey::Keyboard::C), shootKey(CS230::InputKey::Keyboard::Space), angleUP(CS230::InputKey::Keyboard::Up), angleDown(CS230::InputKey::Keyboard::Down), upgradeNumberAttackDamage(0), upgradeNumberBulletSpeed(0), upgradeNumberAttackSpeed(0), Cannon(CS230::Sprite("assets/LEVEL3/cannon.spt", this))
{
	AddGOComponent(new CS230::Sprite("assets/LEVEL3/Base.spt", this));
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
	const unsigned int gold = Engine::GetGSComponent<Gold>()->GetGold();
	const unsigned int goldUpCost = goldIncreasingImproveCost * goldIncreasing;
	const unsigned int adUpCost = adImproveCost * upgradeNumberAttackDamage;
	const unsigned int attackSpeedUpCost = attackSpeedImproveCost * upgradeNumberAttackSpeed;
	const unsigned int rangeUpCost = rangeImproveCost * upgradeNumberBulletSpeed;
	if(footmanKey.IsKeyReleased() == true && gold >= footmanCost)
	{
		MakeFootman(footmanCost);
	}
	else if(riflemanKey.IsKeyReleased() == true && gold >= riflemanCost)
	{
		MakeRifleman(riflemanCost);
	}
	else if (knightKey.IsKeyReleased() == true && gold >= knightCost)
	{
		MakeKnight(knightCost);
	}
	else if(goldEarnKey.IsKeyReleased() == true && gold >= goldUpCost)
	{
		improveIncresing(goldUpCost);
	}
	else if (shootDamageKey.IsKeyReleased() == true && gold >= adUpCost)
	{
		improveIncresing(adUpCost);
	}
	else if (shootSpeedKey.IsKeyReleased() == true && gold >= attackSpeedUpCost)
	{
		improveIncresing(attackSpeedUpCost);
	}
	else if (bulletSpeedKey.IsKeyReleased() == true && gold >= rangeUpCost)
	{
		improveIncresing(rangeUpCost);
	}
	else if(shootKey.IsKeyDown() == true && attackTimer >= (1. / attackSpeed))
	{
		Shoot();
		attackTimer = 0;
	}
	if(angleUP.IsKeyDown() == true && angle <= angleDownLim)
	{
		angle += angleDownLim/2 * dt;
	}
	else if (angleDown.IsKeyDown() == true && angle >= angleUpLim)
	{
		angle += angleUpLim/2 * dt;
	}
}

void Alliance::Draw(math::TransformMatrix displayMatrix)
{
	Level3Object::Draw(displayMatrix);
	Cannon.Draw(displayMatrix * GetMatrix() * math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)) * math::ScaleMatrix({0.7,0.7}) * math::RotateMatrix(angle));
}

void Alliance::Shoot()
{
	Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Bullet(cannonPosition + GetPosition(), angle, { 1,1 }, speed, ad));
}

void Alliance::MakeFootman(int cost)
{
	Engine::GetGSComponent<Gold>()->UpdateGold(-cost);
	Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Footman(GetPosition(), 100, 10, {0.7,0.7}, { 50, 0 }, 0.5));
}

void Alliance::MakeRifleman(int cost)
{
	Engine::GetGSComponent<Gold>()->UpdateGold(-cost);
	Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Rifleman(GetPosition(), 100, 30, { 0.7,0.7 }, { 50, 0 }, 1.5));
}

void Alliance::MakeKnight(int cost)
{
	Engine::GetGSComponent<Gold>()->UpdateGold(-cost);
	Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Knight(GetPosition(), 250, 25, { 1,1 }, { 100, 0 }, 0.3));
}

void Alliance::improveIncresing(int cost)
{
	Engine::GetGSComponent<Gold>()->UpdateGold(-cost);
	goldIncreasing++;
}

void Alliance::improveAD(int cost)
{
	Engine::GetGSComponent<Gold>()->UpdateGold(-cost);
	ad = static_cast<int>(ad * factor);
}

void Alliance::inproveAttackSpeed(int cost)
{
	Engine::GetGSComponent<Gold>()->UpdateGold(-cost);
	attackSpeed *= factor;
}

void Alliance::inproveRange(int cost)
{
	Engine::GetGSComponent<Gold>()->UpdateGold(-cost);
	speed *= factor;
}
