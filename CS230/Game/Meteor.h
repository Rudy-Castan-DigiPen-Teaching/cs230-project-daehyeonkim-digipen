/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Meteor.h
Project: CS230
Author: Kevin Wright
Creation date: 2/15/2021
-----------------------------------------------------------------*/
#pragma once
#include "GameObjectTypes.h"
#include "..\Engine\GameObject.h"

class Meteor : public CS230::GameObject {
public:
	Meteor();
	Meteor(Meteor& original);
	void Update(double dt) override;
	GameObjectType GetObjectType() override { return GameObjectType::Meteor; }
	std::string GetObjectTypeName() override { return "Meteor"; }
	void ResolveCollision(GameObject* objectB) override;
	static constexpr double PI = 3.141592;
private:
	int health;
	int size;
};