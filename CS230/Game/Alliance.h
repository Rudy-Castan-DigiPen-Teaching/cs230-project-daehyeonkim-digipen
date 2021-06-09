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
	static constexpr math::vec2 cannonPosition = {48, 192};
	CS230::InputKey footmanKey;
	CS230::InputKey riflemanKey;
	CS230::InputKey knightKey;
	CS230::InputKey shootKey;
	CS230::InputKey goldEarnKey;
	CS230::InputKey shootDamageKey;
	CS230::InputKey shootSpeedKey;
	CS230::InputKey bulletSpeedKey;
	CS230::InputKey angleUP;
	CS230::InputKey angleDown;
	static constexpr int footmanCost = 20;
	static constexpr int riflemanCost = 30;
	static constexpr int knightCost = 100;
	static constexpr int goldIncreasingImproveCost = 50;
	static constexpr int adImproveCost = 50;
	static constexpr int attackSpeedImproveCost = 50;
	static constexpr int rangeImproveCost = 100;
	static constexpr double factor = 1.5;
	static constexpr double angleDownLim = PI / 3.;
	static constexpr double angleUpLim = -PI / 3.;

	int goldIncreasing;
	int ad;
	int upgradeNumberAttackDamage;
	math::vec2 speed;
	int upgradeNumberBulletSpeed;
	double attackSpeed;
	int upgradeNumberAttackSpeed;
	
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
private:
	void Shoot();
	void MakeFootman(int cost);
	void MakeRifleman(int cost);
	void MakeKnight(int cost);
	void improveIncresing(int cost);
	void improveAD(int cost);
	void inproveAttackSpeed(int cost);
	void inproveRange(int cost);

};
