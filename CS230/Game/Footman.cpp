/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Footman.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 06/04/2021
-----------------------------------------------------------------*/
#include "Footman.h"
#include "HPBar.h"
#include "UnitAmount.h"
#include "Unit_Anims.h"
#include "../Engine/Sprite.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"

Footman::Footman(math::vec2 position, int hp, int ad, math::vec2 HPBarScale, math::vec2 movementSpeed, double attackSpeed) : Level3Object(position, hp, HPBarScale), attackDamage(ad), speed(movementSpeed), attackSpeed(attackSpeed), attackTimer(0), AttackWho(nullptr)
{
	AddGOComponent(new CS230::Sprite("assets/LEVEL3/footman.spt", this));
	ChangeState(&stateWalking);
}


void Footman::ResolveCollision(GameObject* objectA)
{
	switch (objectA->GetObjectType())
	{
	case GameObjectType::Horde:
		[[fallthrough]];
	case GameObjectType::Grunt:
		[[fallthrough]];
	case GameObjectType::Shaman:
		[[fallthrough]];
	case GameObjectType::Tauren:
		if (AttackWho == nullptr)
		{
			AttackWho = static_cast<Level3Object*>(objectA);
		}
		break;
	}
}

bool Footman::CanCollideWith(GameObjectType objectBType)
{
	switch (objectBType)
	{
	case GameObjectType::Horde:
		[[fallthrough]];
	case GameObjectType::Grunt:
		[[fallthrough]];
	case GameObjectType::Shaman:
		[[fallthrough]];
	case GameObjectType::Tauren:
		return true;
	default:
		return false;
	}
}

void Footman::State_Walking::Enter(GameObject* object)
{
	Footman* footman = static_cast<Footman*>(object);
	footman->SetVelocity(footman->speed);
	footman->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Walk_Anim));
}

void Footman::State_Walking::Update(GameObject*, double) {}

void Footman::State_Walking::TestForExit(GameObject* object)
{
	Footman* footman = static_cast<Footman*>(object);
	if (footman->isDead() == true)
	{
		footman->ChangeState(&footman->stateDead);
	}
	else if (footman->AttackWho != nullptr && footman->AttackWho->isDead() == false)
	{
		footman->ChangeState(&footman->stateAttack);
	}
}

void Footman::State_Attack::Enter(GameObject* object)
{
	Footman* footman = static_cast<Footman*>(object);
	footman->SetVelocity({ 0,0 });
	footman->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Attack_Anim));
}

void Footman::State_Attack::Update(GameObject* object, double dt)
{
	Footman* footman = static_cast<Footman*>(object);
	footman->attackTimer += dt;
	if(footman->attackTimer >= footman->attackSpeed)
	{
		footman->AttackWho->UpdateHP(-footman->attackDamage);
		footman->attackTimer = 0;
	}
}

void Footman::State_Attack::TestForExit(GameObject* object)
{
	Footman* footman = static_cast<Footman*>(object);
	if (footman->DoesCollideWith(footman->AttackWho) == false)
	{
		footman->AttackWho = nullptr;
		footman->ChangeState(&footman->stateWalking);
	}
	if (footman->isDead() == true)
	{
		footman->ChangeState(&footman->stateDead);
	}
}

void Footman::State_Dead::Enter(GameObject* object)
{
	Footman* footman = static_cast<Footman*>(object);
	footman->SetVelocity({ 0,0 });
	footman->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Dead_Anim));
	footman->RemoveGOComponent<CS230::Collision>();
	footman->RemoveGOComponent<HPBar>();
	Engine::GetGSComponent<UnitAmount>()->UpdateUnitAmount(-1, 0);
}

void Footman::State_Dead::Update(GameObject*, double) {}

void Footman::State_Dead::TestForExit(GameObject* object)
{
	Footman* footman = static_cast<Footman*>(object);
	if (footman->GetGOComponent<CS230::Sprite>()->GetCurrentAnim() == static_cast<int>(Unit_Anims::Dead_Anim) && footman->GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true)
	{
		footman->Destroy();
	}
}


