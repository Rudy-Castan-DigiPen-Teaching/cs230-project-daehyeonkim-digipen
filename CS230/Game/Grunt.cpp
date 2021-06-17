/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Grunt.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 06/04/2021
-----------------------------------------------------------------*/
#include "Grunt.h"

#include "Horde.h"
#include "HPBar.h"
#include "Score.h"
#include "UnitAmount.h"
#include "Unit_Anims.h"
#include "../Engine/Sprite.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"

Grunt::Grunt(math::vec2 position, int hp, int ad, math::vec2 HPBarScale, math::vec2 movementSpeed, double attackSpeed) : Level3Object(position, hp, HPBarScale), attackDamage(ad), speed(movementSpeed), attackSpeed(attackSpeed), attackTimer(0), AttackWho(nullptr)
{
	AddGOComponent(new CS230::Sprite("assets/LEVEL3/grunt.spt", this));
	ChangeState(&stateWalking);
}


void Grunt::ResolveCollision(GameObject* objectA)
{
	switch (objectA->GetObjectType())
	{
	case GameObjectType::Alliance:
		[[fallthrough]];
	case GameObjectType::Footman:
		[[fallthrough]];
	case GameObjectType::Rifleman:
		[[fallthrough]];
	case GameObjectType::Knight:
		if (AttackWho == nullptr)
		{
			AttackWho = static_cast<Level3Object*>(objectA);
		}
		break;
	}
}

bool Grunt::CanCollideWith(GameObjectType objectBType)
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
void Grunt::State_Walking::Enter(GameObject* object)
{
	Grunt* grunt = static_cast<Grunt*>(object);
	grunt->SetVelocity(-grunt->speed);
	grunt->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Walk_Anim));
}

void Grunt::State_Walking::Update(GameObject*, double) {}

void Grunt::State_Walking::TestForExit(GameObject* object)
{
	Grunt* grunt = static_cast<Grunt*>(object);
	if (grunt->isDead() == true)
	{
		grunt->ChangeState(&grunt->stateDead);
	}
	else if (grunt->AttackWho != nullptr && grunt->AttackWho->isDead() == false)
	{
		grunt->ChangeState(&grunt->stateAttack);
	}
}

void Grunt::State_Attack::Enter(GameObject* object)
{
	Grunt* grunt = static_cast<Grunt*>(object);
	grunt->SetVelocity({ 0,0 });
	grunt->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Attack_Anim));
}

void Grunt::State_Attack::Update(GameObject* object, double dt)
{
	Grunt* grunt = static_cast<Grunt*>(object);
	grunt->attackTimer += dt;
	if (grunt->attackTimer >= grunt->attackSpeed)
	{
		grunt->AttackWho->UpdateHP(-grunt->attackDamage);
		grunt->attackTimer = 0;
	}
}

void Grunt::State_Attack::TestForExit(GameObject* object)
{
	Grunt* grunt = static_cast<Grunt*>(object);
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

void Grunt::State_Dead::Enter(GameObject* object)
{
	Grunt* grunt = static_cast<Grunt*>(object);
	grunt->SetVelocity({ 0,0 });
	grunt->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Dead_Anim));
	grunt->RemoveGOComponent<CS230::Collision>();
	grunt->RemoveGOComponent<HPBar>();
	Engine::GetGSComponent<Score>()->AddScore(50);
	Engine::GetGSComponent<UnitAmount>()->UpdateUnitAmount(0, -1);
}

void Grunt::State_Dead::Update(GameObject*, double) {}

void Grunt::State_Dead::TestForExit(GameObject* object)
{
	Grunt* grunt = static_cast<Grunt*>(object);
	if (grunt->GetGOComponent<CS230::Sprite>()->GetCurrentAnim() == static_cast<int>(Unit_Anims::Dead_Anim) && grunt->GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true)
	{
		grunt->Destroy();
	}
}


