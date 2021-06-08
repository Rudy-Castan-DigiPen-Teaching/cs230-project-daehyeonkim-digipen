/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Shaman.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 06/08/2021
-----------------------------------------------------------------*/
#include "Shaman.h"
#include "HPBar.h"
#include "Unit_Anims.h"
#include "../Engine/Sprite.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"

Shaman::Shaman(math::vec2 position, int hp, int ad, math::vec2 HPBarScale, math::vec2 movementSpeed, double attackSpeed) : Level3Object(position, hp, HPBarScale), ad(ad), speed(movementSpeed), attackSpeed(attackSpeed), attackTimer(0), AttackWho(nullptr)
{
	AddGOComponent(new CS230::Sprite("assets/prince/shaman.spt", this));
	ChangeState(&stateWalking);
}

void Shaman::State_Walking::Enter(GameObject* object)
{
	Shaman* rifleman = static_cast<Shaman*>(object);
	rifleman->SetVelocity(rifleman->speed);
	rifleman->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Walk_Anim));
}

void Shaman::State_Walking::Update(GameObject*, double) {}

void Shaman::State_Walking::TestForExit(GameObject* object)
{
	Shaman* rifleman = static_cast<Shaman*>(object);
	if (rifleman->isDead() == true)
	{
		rifleman->ChangeState(&rifleman->stateDead);
		return;
	}
	for (GameObject* obj : Engine::GetGSComponent<CS230::GameObjectManager>()->Objects())
	{
		switch (obj->GetObjectType())
		{
		case GameObjectType::Alliance:
			[[fallthrough]];
		case GameObjectType::Footman:
			[[fallthrough]];
		case GameObjectType::Rifleman:
			[[fallthrough]];
		case GameObjectType::Knight:
			if (rifleman->GetGOComponent<CS230::CircleCollision>()->DoesCollideWith(obj->GetPosition()) == true && rifleman->AttackWho == nullptr)
			{
				Level3Object* targetObj = dynamic_cast<Level3Object*>(obj);
				if (targetObj->isDead() != true)
				{
					rifleman->AttackWho = targetObj;
					rifleman->ChangeState(&rifleman->stateAttack);
				}
			}
			break;
		default:
			break;
		}
	}
}

void Shaman::State_Attack::Enter(GameObject* object)
{
	Shaman* rifleman = static_cast<Shaman*>(object);
	rifleman->SetVelocity({ 0,0 });
	rifleman->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Attack_Anim));
}

void Shaman::State_Attack::Update(GameObject* object, double dt)
{
	Shaman* rifleman = static_cast<Shaman*>(object);
	rifleman->attackTimer += dt;
	if (rifleman->attackTimer >= rifleman->attackSpeed)
	{
		rifleman->AttackWho->UpdateHP(-rifleman->ad);
		rifleman->attackTimer = 0;
	}
}

void Shaman::State_Attack::TestForExit(GameObject* object)
{
	Shaman* rifleman = static_cast<Shaman*>(object);
	if (rifleman->GetGOComponent<CS230::CircleCollision>()->DoesCollideWith(rifleman->AttackWho->GetPosition()) == false || rifleman->AttackWho->isDead() == true)
	{
		rifleman->AttackWho = nullptr;
		rifleman->ChangeState(&rifleman->stateWalking);
	}
	if (rifleman->isDead() == true)
	{
		rifleman->ChangeState(&rifleman->stateDead);
	}
}

void Shaman::State_Dead::Enter(GameObject* object)
{
	Shaman* rifleman = static_cast<Shaman*>(object);
	rifleman->SetVelocity({ 0,0 });
	rifleman->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Dead_Anim));
	rifleman->RemoveGOComponent<CS230::Collision>();
	rifleman->RemoveGOComponent<HPBar>();
}

void Shaman::State_Dead::Update(GameObject*, double) {}

void Shaman::State_Dead::TestForExit(GameObject* object)
{
	Shaman* rifleman = static_cast<Shaman*>(object);
	if (rifleman->GetGOComponent<CS230::Sprite>()->GetCurrentAnim() == static_cast<int>(Unit_Anims::Dead_Anim) && rifleman->GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true)
	{
		rifleman->Destroy();
	}
}


