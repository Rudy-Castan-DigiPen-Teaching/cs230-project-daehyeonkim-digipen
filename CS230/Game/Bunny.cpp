/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Bunny.h
Project: CS230
Author: Daehyeon Kim
Creation date: 04/19/2021
-----------------------------------------------------------------*/
#include "Bunny.h"
#include "Bunny_Anims.h"
#include "Score.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"

Bunny::Bunny(math::vec2 pos) : GameObject(pos)
{
	AddGOComponent(new CS230::Sprite("assets/bunny.spt", this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::None_Anim));

}

void Bunny::ResolveCollision(GameObject* objectA)
{
	switch(objectA->GetObjectType())
	{
	case GameObjectType::Hero:
		RemoveGOComponent<CS230::Collision>();
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Dead_Anim));
		Engine::GetGSComponent<Score>()->AddScore(100);
		break;
	}
}
