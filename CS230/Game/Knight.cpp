/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Knight.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 06/08/2021
-----------------------------------------------------------------*/
#include "Knight.h"
#include "HPBar.h"
#include "Unit_Anims.h"
#include "../Engine/Sprite.h"
#include "../Engine/Collision.h"
Knight::Knight(math::vec2 position, int hp, int ad, math::vec2 HPBarScale, math::vec2 movementSpeed, double attackSpeed) : Level3Object(position, hp, HPBarScale), ad(ad), speed(movementSpeed), attackSpeed(attackSpeed), attackTimer(0), AttackWho(nullptr)
{
	AddGOComponent(new CS230::Sprite("assets/LEVEL3/knight.spt", this));
	ChangeState(&stateWalking);
}


void Knight::ResolveCollision(GameObject* objectA)
{
	AttackWho = static_cast<Level3Object*>(objectA);
	switch (objectA->GetObjectType())
	{
	case GameObjectType::Horde:
		[[fallthrough]];
	case GameObjectType::Grunt:
		[[fallthrough]];
	case GameObjectType::Shaman:
		[[fallthrough]];
	case GameObjectType::Tauren:
		ChangeState(&stateAttack);
		break;
	}
}

bool Knight::CanCollideWith(GameObjectType objectBType)
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

void Knight::State_Walking::Enter(GameObject* object)
{
	Knight* footman = static_cast<Knight*>(object);
	footman->SetVelocity(footman->speed);
	footman->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Walk_Anim));
}

void Knight::State_Walking::Update(GameObject*, double) {}

void Knight::State_Walking::TestForExit(GameObject* object)
{
	Knight* footman = static_cast<Knight*>(object);
	if (footman->isDead() == true)
	{
		footman->ChangeState(&footman->stateDead);
	}
}

void Knight::State_Attack::Enter(GameObject* object)
{
	Knight* footman = static_cast<Knight*>(object);
	footman->SetVelocity({ 0,0 });
	footman->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Attack_Anim));
}

void Knight::State_Attack::Update(GameObject* object, double dt)
{
	Knight* footman = static_cast<Knight*>(object);
	footman->attackTimer += dt;
	if (footman->attackTimer >= footman->attackSpeed)
	{
		footman->AttackWho->UpdateHP(-footman->ad);
		footman->attackTimer = 0;
	}
}

void Knight::State_Attack::TestForExit(GameObject* object)
{
	Knight* footman = static_cast<Knight*>(object);
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

void Knight::State_Dead::Enter(GameObject* object)
{
	Knight* footman = static_cast<Knight*>(object);
	footman->SetVelocity({ 0,0 });
	footman->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Dead_Anim));
	footman->RemoveGOComponent<CS230::Collision>();
	footman->RemoveGOComponent<HPBar>();
}

void Knight::State_Dead::Update(GameObject*, double) {}

void Knight::State_Dead::TestForExit(GameObject* object)
{
	Knight* footman = static_cast<Knight*>(object);
	if (footman->GetGOComponent<CS230::Sprite>()->GetCurrentAnim() == static_cast<int>(Unit_Anims::Dead_Anim) && footman->GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true)
	{
		footman->Destroy();
	}
}


