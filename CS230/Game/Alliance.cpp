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
#include "Bomb.h"
#include "Gold.h"
#include "Footman.h"
#include "GameParticles.h"
#include "HPBar.h"
#include "Knight.h"
#include "Rifleman.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "Fonts.h"
#include "Level3.h"

Alliance::Alliance(math::vec2 initPos, int hp, math::vec2 HPBarScale, int ad, double attackSpeed, math::vec2 speed) : Level3Object(initPos, hp, HPBarScale, 100), goldIncreasing(1), goldTimer(0), attackSpeed(attackSpeed), attackTimer(0), attackDamage(ad), speed(speed), angle(0), footmanKey(CS230::InputKey::Keyboard::A), shamanKey(CS230::InputKey::Keyboard::S), knightKey(CS230::InputKey::Keyboard::D), improveUnitKey(CS230::InputKey::Keyboard::F), goldEarnKey(CS230::InputKey::Keyboard::G), shootDamageKey(CS230::InputKey::Keyboard::Z), shootSpeedKey(CS230::InputKey::Keyboard::X), bulletSpeedKey(CS230::InputKey::Keyboard::C), shootKey(CS230::InputKey::Keyboard::Space), angleUP(CS230::InputKey::Keyboard::Up), angleDown(CS230::InputKey::Keyboard::Down), unitLevel(1), attackDamageLevel(1), rangeLevel(1), attackSpeedLevel(1), Cannon(CS230::Sprite("assets/LEVEL3/cannon.spt", this)), font(Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)))
{
	AddGOComponent(new CS230::Sprite("assets/LEVEL3/Base.spt", this));
	AddGOComponent(new HPBar(hp, { 2, 2 }));
	
	GoldUpLevelTexture = font.DrawTextToTexture("Gold Up Level: " + std::to_string(goldIncreasing), 0xFFFFFFFF, true);
	UnitLevelTexture = font.DrawTextToTexture("Unit Level: " + std::to_string(unitLevel), 0xFFFFFFFF, true);
	DamageLevelTexture = font.DrawTextToTexture("Bomb Damage Level: " + std::to_string(attackDamageLevel), 0xFFFFFFFF, true);
	SpeedLevelTexture = font.DrawTextToTexture("Shoot Speed Level: " + std::to_string(attackSpeedLevel), 0xFFFFFFFF, true);
	RangeLevelTexture = font.DrawTextToTexture("Bomb Range Level: " + std::to_string(rangeLevel), 0xFFFFFFFF, true);
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
	const int gold = Engine::GetGSComponent<Gold>()->GetGold();
	const int unitUpCost = unitImproveCost * unitLevel;
	const int goldUpCost = goldIncreasingImproveCost * goldIncreasing;
	const int attackDamageUpCost = attackDamageImproveCost * attackDamageLevel;
	const int attackSpeedUpCost = attackSpeedImproveCost * attackSpeedLevel;
	const int rangeUpCost = rangeImproveCost * rangeLevel;
	if(footmanKey.IsKeyReleased() == true && gold >= footmanCost)
	{
		MakeFootman(footmanCost);
	}
	else if(shamanKey.IsKeyReleased() == true && gold >= riflemanCost)
	{
		MakeRifleman(riflemanCost);
	}
	else if (knightKey.IsKeyReleased() == true && gold >= knightCost)
	{
		MakeKnight(knightCost);
	}
	else if(improveUnitKey.IsKeyReleased() == true && gold >= unitUpCost)
	{
		ImproveUnitLevel(unitUpCost);
	}
	else if(goldEarnKey.IsKeyReleased() == true && gold >= goldUpCost)
	{
		ImproveGoldIncresing(goldUpCost);
	}
	else if (shootDamageKey.IsKeyReleased() == true && gold >= attackDamageUpCost)
	{
		ImproveDamage(attackDamageUpCost);
	}
	else if (shootSpeedKey.IsKeyReleased() == true && gold >= attackSpeedUpCost)
	{
		ImproveAttackSpeed(attackSpeedUpCost);
	}
	else if (bulletSpeedKey.IsKeyReleased() == true && gold >= rangeUpCost)
	{
		ImproveRange(rangeUpCost);
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
	Cannon.Draw(displayMatrix * GetMatrix() * math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)) * math::RotateMatrix(angle));
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	math::vec2 textInitPosition = math::vec2{ 20 ,static_cast<double>(winSize.y)};
	math::vec2 textInterval = math::vec2{ 0, winSize.y * 0.1 };
	math::TransformMatrix textScale = math::ScaleMatrix({ 0.5, 0.5 });
	GoldUpLevelTexture.Draw(textScale * math::TranslateMatrix(textInitPosition + textInterval * 5 + math::vec2{0, static_cast<double>(GoldUpLevelTexture.GetSize().y)}));
	UnitLevelTexture.Draw(textScale * math::TranslateMatrix(textInitPosition + textInterval * 4 + math::vec2{ 0, static_cast<double>(GoldUpLevelTexture.GetSize().y) }));
	DamageLevelTexture.Draw(textScale * math::TranslateMatrix(textInitPosition + textInterval * 3 + math::vec2{ 0,static_cast<double>(GoldUpLevelTexture.GetSize().y) }));
	SpeedLevelTexture.Draw(textScale * math::TranslateMatrix(textInitPosition + textInterval * 2 + math::vec2{ 0, static_cast<double>(GoldUpLevelTexture.GetSize().y)}));
	RangeLevelTexture.Draw(textScale * math::TranslateMatrix(textInitPosition + textInterval * 1 + math::vec2{ 0, static_cast<double>(GoldUpLevelTexture.GetSize().y)}));
	Level3Object::Draw(displayMatrix);
}

void Alliance::Shoot()
{
	const math::vec2 shootPosition = GetPosition() + math::vec2(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)) + math::RotateMatrix(angle) * math::vec2(Cannon.GetHotSpot(1));
	Engine::GetGSComponent<CS230::GameObjectManager>()->AddFront(new Bomb(shootPosition, angle, { 1,1 }, speed, attackDamage));
	Engine::GetGameStateManager().GetGSComponent<ShootCannonEmitter>()->Emit(1, shootPosition, { 0, 0 }, { 0,0 }, 0, {1,1}, angle);
}

void Alliance::MakeFootman(int cost)
{
	Engine::GetGSComponent<Gold>()->UpdateGold(-cost);
	Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Footman(unitIdentityCode, GetPosition(), 100 * unitLevel, 10 * unitLevel, {0.7,0.7}, { 50, 0 }, 0.5));
	Level3::objIDAdress++;
}

void Alliance::MakeRifleman(int cost)
{
	Engine::GetGSComponent<Gold>()->UpdateGold(-cost);
	Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Rifleman(unitIdentityCode, GetPosition(), 100 * unitLevel, 30 * unitLevel, { 0.7,0.7 }, { 50, 0 }, 1.5));
	unitIdentityCode++;
}

void Alliance::MakeKnight(int cost)
{
	Engine::GetGSComponent<Gold>()->UpdateGold(-cost);
	Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Knight(unitIdentityCode, GetPosition(), 250 * unitLevel, 25 * unitLevel, { 1,1 }, { 100, 0 }, 0.3));
	unitIdentityCode++;
}

void Alliance::ImproveUnitLevel(int cost)
{
	Engine::GetGSComponent<Gold>()->UpdateGold(-cost);
	unitLevel++;
	UnitLevelTexture = font.DrawTextToTexture("Unit Level: " + std::to_string(unitLevel), 0xFFFFFFFF, true);
}

void Alliance::ImproveGoldIncresing(int cost)
{
	Engine::GetGSComponent<Gold>()->UpdateGold(-cost);
	goldIncreasing++;
	GoldUpLevelTexture = font.DrawTextToTexture("Gold Up Level: " + std::to_string(goldIncreasing), 0xFFFFFFFF, true);
}

void Alliance::ImproveDamage(int cost)
{
	Engine::GetGSComponent<Gold>()->UpdateGold(-cost);
	attackDamage = static_cast<int>(attackDamage * factor);
	attackDamageLevel++;
	DamageLevelTexture = font.DrawTextToTexture("Bomb Damage Level: " + std::to_string(attackDamageLevel), 0xFFFFFFFF, true);
}

void Alliance::ImproveAttackSpeed(int cost)
{
	Engine::GetGSComponent<Gold>()->UpdateGold(-cost);
	attackSpeed *= factor;
	attackSpeedLevel++;
	SpeedLevelTexture = font.DrawTextToTexture("Shoot Speed Level: " + std::to_string(attackSpeedLevel), 0xFFFFFFFF, true);
}

void Alliance::ImproveRange(int cost)
{
	Engine::GetGSComponent<Gold>()->UpdateGold(-cost);
	speed *= factor;
	rangeLevel++;
	RangeLevelTexture = font.DrawTextToTexture("Bomb Range Level: " + std::to_string(rangeLevel), 0xFFFFFFFF, true);
}
