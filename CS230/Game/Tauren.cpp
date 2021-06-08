/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Tauren.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 06/08/2021
-----------------------------------------------------------------*/
#include "Tauren.h"
#include "HPBar.h"
#include "Unit_Anims.h"
#include "../Engine/Sprite.h"
#include "../Engine/Collision.h"
Tauren::Tauren(math::vec2 position, int hp, int ad, math::vec2 HPBarScale, math::vec2 movementSpeed, double attackSpeed) : Level3Object(position, hp, HPBarScale), ad(ad), speed(movementSpeed), attackSpeed(attackSpeed), attackTimer(0), AttackWho(nullptr)
{
	AddGOComponent(new CS230::Sprite("assets/prince/tauren.spt", this));
	ChangeState(&stateWalking);
}


void Tauren::ResolveCollision(GameObject* objectA)
{
	AttackWho = static_cast<Level3Object*>(objectA);
	switch (objectA->GetObjectType())
	{
	case GameObjectType::Alliance:
		[[fallthrough]];
	case GameObjectType::Footman:
		[[fallthrough]];
	case GameObjectType::Rifleman:
		[[fallthrough]];
	case GameObjectType::Knight:
		ChangeState(&stateAttack);
		break;
	}
}

bool Tauren::CanCollideWith(GameObjectType objectBType)
{
	switch (objectBType)
	{
	case GameObjectType::Alliance:
		[[fallthrough]];
	case GameObjectType::Footman:
		[[fallthrough]];
	case GameObjectType::Rifleman:
		[[fallthrough]];
	case GameObjectType::Knight:
		return true;
	default:
		return false;
	}
}
void Tauren::State_Walking::Enter(GameObject* object)
{
	Tauren* grunt = static_cast<Tauren*>(object);
	grunt->SetVelocity(-grunt->speed);
	grunt->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Walk_Anim));
}

void Tauren::State_Walking::Update(GameObject*, double) {}

void Tauren::State_Walking::TestForExit(GameObject* object)
{
	Tauren* grunt = static_cast<Tauren*>(object);
	if (grunt->isDead() == true)
	{
		grunt->ChangeState(&grunt->stateDead);
	}
}

void Tauren::State_Attack::Enter(GameObject* object)
{
	Tauren* grunt = static_cast<Tauren*>(object);
	grunt->SetVelocity({ 0,0 });
	grunt->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Attack_Anim));

}

void Tauren::State_Attack::Update(GameObject* object, double dt)
{
	Tauren* grunt = static_cast<Tauren*>(object);
	grunt->attackTimer += dt;
	if (grunt->attackTimer >= grunt->attackSpeed)
	{
		grunt->AttackWho->UpdateHP(-grunt->ad);
		grunt->attackTimer = 0;
	}
}

void Tauren::State_Attack::TestForExit(GameObject* object)
{
	Tauren* grunt = static_cast<Tauren*>(object);
	if (grunt->DoesCollideWith(grunt->AttackWho) == false)
	{
		grunt->AttackWho = nullptr;
		grunt->ChangeState(&grunt->stateWalking);
	}
	if (grunt->isDead() == true)
	{
		grunt->ChangeState(&grunt->stateDead);
	}
}

void Tauren::State_Dead::Enter(GameObject* object)
{
	Tauren* grunt = static_cast<Tauren*>(object);
	grunt->SetVelocity({ 0,0 });
	grunt->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Dead_Anim));
	grunt->RemoveGOComponent<CS230::Collision>();
	grunt->RemoveGOComponent<HPBar>();
}

void Tauren::State_Dead::Update(GameObject*, double) {}

void Tauren::State_Dead::TestForExit(GameObject* object)
{
	Tauren* grunt = static_cast<Tauren*>(object);
	if (grunt->GetGOComponent<CS230::Sprite>()->GetCurrentAnim() == static_cast<int>(Unit_Anims::Dead_Anim) && grunt->GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true)
	{
		grunt->Destroy();
	}
}


