/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ScreenWrap.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/17/2021
-----------------------------------------------------------------*/
#include "..\Engine\Engine.h"
#include "..\Engine\Sprite.h"
#include "..\Engine\GameObject.h"
#include "ScreenWrap.h"


void ScreenWrap::Update(double) {
	math::ivec2 frameSize = object.GetGOComponent<CS230::Sprite>()->GetFrameSize();
	if (object.GetPosition().y > Engine::GetWindow().GetSize().y + frameSize.y / 2.0) {
		object.SetPosition({ object.GetPosition().x, 0 - frameSize.y / 2.0 });
	} else if (object.GetPosition().y < 0 - frameSize.y / 2.0) {
		object.SetPosition({ object.GetPosition().x, Engine::GetWindow().GetSize().y + frameSize.y / 2.0 });
	}
	if (object.GetPosition().x > Engine::GetWindow().GetSize().x + object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0) {
		object.SetPosition({ 0 - frameSize.x / 2.0, object.GetPosition().y });
	} else if (object.GetPosition().x < 0 - frameSize.x / 2.0) {
		object.SetPosition({ Engine::GetWindow().GetSize().x + frameSize.x / 2.0, object.GetPosition().y });
	}
}