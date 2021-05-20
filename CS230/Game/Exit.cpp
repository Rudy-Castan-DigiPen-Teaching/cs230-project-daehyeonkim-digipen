/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Exit.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 5/17/2021
-----------------------------------------------------------------*/
#include "Exit.h"
#include "Screens.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
#include "../Engine/Rect.h"

Exit::Exit(math::irect2 rect) : GameObject(rect.point1)
{
	AddGOComponent(new CS230::RectCollision({{ 0,0 }, rect.Size() }, this));
}

void Exit::ResolveCollision(GameObject* objectA)
{
	switch(objectA->GetObjectType())
	{
	case GameObjectType::Hero:
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
		break;
	}
}
