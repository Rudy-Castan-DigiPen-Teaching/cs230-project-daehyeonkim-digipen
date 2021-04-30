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
#include "../Engine/Engine.h"


Meteor::Meteor() : GameObject({ 0,0 }, 0, { 0, 0 }) {
	constexpr double PI = 3.141592;
	sprite.Load("assets/Meteor.spt");
	SetVelocity({(rand() % 200) - 100.0,(rand() % 200) - 100.0 });
	SetPosition({ (rand() % Engine::GetWindow().GetSize().x + static_cast<double>(sprite.GetFrameSize().x)) - sprite.GetFrameSize().x / 2.0, (rand() % Engine::GetWindow().GetSize().y + static_cast<double>(sprite.GetFrameSize().y)) - sprite.GetFrameSize().y / 2.0 });
	SetRotation({(rand() % static_cast<int>(1024 * 2 * PI)) / 1024.0});
	SetScale({ (rand() % 1024 / 4096) + 0.75,(rand() % 1024 / 4096) + 0.75});
}

void Meteor::Update(double dt)
{
	GameObject::Update(dt);
	TestForWrap();
}

void Meteor::TestForWrap()
{
	const double x_limit = Engine::GetWindow().GetSize().x + sprite.GetFrameSize().x / 2.0;
	const double y_limit = Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y / 2.0;
	if (GetPosition().x > x_limit)
	{
		SetPosition({ -sprite.GetFrameSize().x / 2.0 ,GetPosition().y });
	}
	else if (GetPosition().x < -sprite.GetFrameSize().x / 2)
	{
		SetPosition({ x_limit ,GetPosition().y });
	}
	if (GetPosition().y > y_limit)
	{
		SetPosition({ GetPosition().x ,-sprite.GetFrameSize().y / 2.0 });
	}
	else if (GetPosition().y < -sprite.GetFrameSize().y / 2)
	{
		SetPosition({ GetPosition().x , y_limit });
	}
}
