/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Barracks.h
Project: CS230
Author: Daehyeon Kim
Creation date: 06/04/2021
-----------------------------------------------------------------*/
#pragma once
#include "GameObjectTypes.h"
#include "../Engine/GameObject.h"

class Barracks : public CS230::GameObject
{
private:
	int hp;
	int gold;
	int goldIncreasing;
	double goldTimer;
public:
	Barracks(int _hp);
	void UpdateHP(int _hp);
	void SetHP(int hp);
	void Update(double dt) override;
	GameObjectType GetObjectType() override { return GameObjectType::Barracks; }
	std::string GetObjectTypeName() override { return "Barracks"; }
	bool CanCollideWith(GameObjectType objectBType) override;
	void ResolveCollision(GameObject*) override;
	void MakeKnight();
};
