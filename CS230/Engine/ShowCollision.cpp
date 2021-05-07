/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ShowCollision.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 5/03/2021
-----------------------------------------------------------------*/
#pragma once
#include "ShowCollision.h"

ShowCollision::ShowCollision(CS230::InputKey::Keyboard keyToUse) : enabled(false), showCollisionKey(keyToUse)
{}

void ShowCollision::Update(double)
{
	if(showCollisionKey.IsKeyReleased() == true)
	{
		if(enabled == false)
		{
			enabled = true;
		} else
		{
			enabled = false;
		}
	}
}

bool ShowCollision::IsEnabled()
{
	return enabled;
}
