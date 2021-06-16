/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Alliance.h
Project: CS230
Author: Daehyeon Kim
Creation date: 06/04/2021
-----------------------------------------------------------------*/
#pragma once
#include "GameObjectTypes.h"
#include "Level3Object.h"
#include "../Engine/Input.h"
#include "../Engine/Sprite.h"

class Alliance final : public Level3Object
{
private:
	static constexpr double PI = 3.141592;
	
	CS230::InputKey footmanKey;
	CS230::InputKey shamanKey;
	CS230::InputKey knightKey;
	CS230::InputKey shootKey;
	CS230::InputKey improveUnitKey;
	CS230::InputKey goldEarnKey;
	CS230::InputKey shootDamageKey;
	CS230::InputKey shootSpeedKey;
	CS230::InputKey bulletSpeedKey;
	CS230::InputKey angleUP;
	CS230::InputKey angleDown;
	
	static constexpr int footmanCost = 10;
	static constexpr int riflemanCost = 15;
	static constexpr int knightCost = 30;
	static constexpr int unitImproveCost = 30;
	static constexpr int goldIncreasingImproveCost = 20;
	static constexpr int attackDamageImproveCost = 20;
	static constexpr int attackSpeedImproveCost = 30;
	static constexpr int rangeImproveCost = 50;
	
	static constexpr double factor = 1.3;
	static constexpr double angleDownLim = PI / 3.;
	static constexpr double angleUpLim = -PI / 3.;

	int goldIncreasing;
	int unitLevel;
	
	int attackDamage;
	int attackDamageLevel;
	
	double attackSpeed;
	int attackSpeedLevel;
	
	math::vec2 speed;
	int rangeLevel;
	
	double goldTimer;
	double attackTimer;
	double angle;

	CS230::Sprite Cannon;
public:
	Alliance(math::vec2 initPos, int hp, math::vec2 HPBarScale, int ad, double attackSpeed, math::vec2 speed);
	void Update(double dt) override;
	void Draw(math::TransformMatrix displayMatrix) override;
	GameObjectType GetObjectType() override { return GameObjectType::Alliance; }
	std::string GetObjectTypeName() override { return "Alliance"; }

	int GetGoldUpLevel() const { return goldIncreasing; }
	int GetUnitLevel() const { return unitLevel; }
	int GetDamageLevel() const { return attackDamageLevel; }
	int GetAttackSpeedLevel() const { return attackSpeedLevel; }
	int GetAttackRangeLevel() const { return rangeLevel; }
private:
	void Shoot();
	void MakeFootman(int cost);
	void MakeRifleman(int cost);
	void MakeKnight(int cost);
	void ImproveUnitLevel(int cost);
	void ImproveGoldIncresing(int cost);
	void ImproveDamage(int cost);
	void ImproveAttackSpeed(int cost);
	void ImproveRange(int cost);

		
};														  
