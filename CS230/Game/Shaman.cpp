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
#include "Score.h"
#include "Unit_Anims.h"
#include "../Engine/Sprite.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"

Shaman::Shaman(math::vec2 position, int hp, int ad, math::vec2 HPBarScale, math::vec2 movementSpeed, double attackSpeed) : Level3Object(position, hp, HPBarScale), attackDamage(ad), speed(movementSpeed), attackSpeed(attackSpeed), attackTimer(0), AttackWho(nullptr)
{
	AddGOComponent(new CS230::Sprite("assets/LEVEL3/shaman.spt", this));
	ChangeState(&stateWalking);
}

void Shaman::State_Walking::Enter(GameObject* object)
{
	Shaman* shaman = static_cast<Shaman*>(object);
	shaman->SetVelocity(-shaman->speed);
	shaman->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Walk_Anim));
}

void Shaman::State_Walking::Update(GameObject*, double) {}

void Shaman::State_Walking::TestForExit(GameObject* object)
{
	Shaman* shaman = static_cast<Shaman*>(object);
	if (shaman->isDead() == true)
	{
		shaman->ChangeState(&shaman->stateDead);
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
			if (shaman->GetGOComponent<CS230::CircleCollision>()->DoesCollideWith(obj->GetPosition()) == true && (shaman->AttackWho == nullptr || shaman->AttackWho->GetObjectType() == GameObjectType::Alliance))
			{
				Level3Object* targetObj = dynamic_cast<Level3Object*>(obj);
				if (targetObj->isDead() != true)
				{
					shaman->AttackWho = targetObj;
					shaman->ChangeState(&shaman->stateAttack);
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
	Shaman* shaman = static_cast<Shaman*>(object);
	shaman->SetVelocity({ 0,0 });
	shaman->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Attack_Anim));
}

void Shaman::State_Attack::Update(GameObject* object, double dt)
{
	Shaman* shaman = static_cast<Shaman*>(object);
	shaman->attackTimer += dt;
	if (shaman->attackTimer >= shaman->attackSpeed)
	{
		shaman->AttackWho->UpdateHP(-shaman->attackDamage);
		shaman->attackTimer = 0;
	}
}

void Shaman::State_Attack::TestForExit(GameObject* object)
{
	Shaman* shaman = static_cast<Shaman*>(object);
	if (shaman->GetGOComponent<CS230::CircleCollision>()->DoesCollideWith(shaman->AttackWho->GetPosition()) == false || shaman->AttackWho->isDead() == true)
	{
		shaman->AttackWho = nullptr;
		shaman->ChangeState(&shaman->stateWalking);
	}
	if (shaman->isDead() == true)
	{
		shaman->ChangeState(&shaman->stateDead);
	}
}

void Shaman::State_Dead::Enter(GameObject* object)
{
	Shaman* shaman = static_cast<Shaman*>(object);
	shaman->SetVelocity({ 0,0 });
	shaman->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Dead_Anim));
	shaman->RemoveGOComponent<CS230::Collision>();
	shaman->RemoveGOComponent<HPBar>();
	Engine::GetGSComponent<Score>()->AddScore(100);
}

void Shaman::State_Dead::Update(GameObject*, double) {}

void Shaman::State_Dead::TestForExit(GameObject* object)
{
	Shaman* shaman = static_cast<Shaman*>(object);
	if (shaman->GetGOComponent<CS230::Sprite>()->GetCurrentAnim() == static_cast<int>(Unit_Anims::Dead_Anim) && shaman->GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true)
	{
		shaman->Destroy();
	}
}


