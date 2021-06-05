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

class Alliance final : public Level3Object
{
private:
	CS230::InputKey footmanKey;
	CS230::InputKey riflemanKey;
	CS230::InputKey knightKey;
	CS230::InputKey shootKey;
	CS230::InputKey goldEarnKey;
	CS230::InputKey shootDamageKey;
	CS230::InputKey shootSpeedKey;
	static constexpr int FootmanCost = 20;
	static constexpr int RiflemanCost = 30;
	static constexpr int KnightCost = 100;

	int goldIncreasing;
	double goldTimer;
	double attackSpeed;
	double attackTimer;
public:
	Alliance(math::vec2 initPos, int hp, math::vec2 HPBarScale, double attackSpeed);

	void Update(double dt) override;
	GameObjectType GetObjectType() override { return GameObjectType::Alliance; }
	std::string GetObjectTypeName() override { return "Alliance"; }
private:
	void Shoot();
	void MakeFootman();
	void MakeRifleman();
	void improveIncresing();

};
