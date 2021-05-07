/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ScreenWrap.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 04/30/2021
-----------------------------------------------------------------*/
#include "ScreenWarp.h"

#include "../Engine/Engine.h"
#include "../Engine/GameObject.h"

void ScreenWrap::Update([[maybe_unused]]double dt)
{
	const double x_limit = Engine::GetWindow().GetSize().x + object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0;
	const double y_limit = Engine::GetWindow().GetSize().y + object.GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0;
	if (object.GetPosition().x > x_limit)
	{
		object.SetPosition({ -object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0 ,object.GetPosition().y });
	}
	else if (object.GetPosition().x < -object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2)
	{
		object.SetPosition({ x_limit ,object.GetPosition().y });
	}
	if (object.GetPosition().y > y_limit)
	{
		object.SetPosition({ object.GetPosition().x ,-object.GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0 });
	}
	else if (object.GetPosition().y < -object.GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2)
	{
		object.SetPosition({ object.GetPosition().x , y_limit });
	}
}
