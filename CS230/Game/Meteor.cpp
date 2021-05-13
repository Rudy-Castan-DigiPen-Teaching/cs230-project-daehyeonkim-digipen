/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Meteor.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 4/19/2021
-----------------------------------------------------------------*/
#include "Meteor.h"
#include "ScreenWarp.h"
#include "../Engine/Engine.h"

Meteor::Meteor() : GameObject({ 0,0 }, 0, { 0, 0 }) {
	constexpr double PI = 3.141592;
	AddGOComponent(new CS230::Sprite("assets/Meteor.spt", this));
	AddGOComponent(new ScreenWrap(*this));
	SetVelocity({ (rand() % 200) - 100.0,(rand() % 200) - 100.0 });
	SetPosition({ (rand() % Engine::GetWindow().GetSize().x + static_cast<double>(GetGOComponent<CS230::Sprite>()->GetFrameSize().x)) - GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0, (rand() % Engine::GetWindow().GetSize().y + static_cast<double>(GetGOComponent<CS230::Sprite>()->GetFrameSize().y)) - GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0 });
	SetRotation({ (rand() % static_cast<int>(1024 * 2 * PI)) / 1024.0 });
	const double scales = ((rand() % 1024) / 4096.0) + 0.75;
	SetScale({ scales,scales });
}
