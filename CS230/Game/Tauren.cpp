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
#include "Score.h"
#include "Unit_Anims.h"
#include "../Engine/Sprite.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"

Tauren::Tauren(math::vec2 position, int hp, int ad, math::vec2 HPBarScale, math::vec2 movementSpeed, double attackSpeed) : Level3Object(position, hp, HPBarScale),attackDamage(ad), speed(movementSpeed), attackSpeed(attackSpeed), attackTimer(0)
{
	AddGOComponent(new CS230::Sprite("assets/LEVEL3/tauren.spt", this));
	ChangeState(&stateWalking);
}


void Tauren::ResolveCollision(GameObject* objectA)
{
	const std::list<int>::iterator attackListFirst = std::begin(AttackWhos);
	const std::list<int>::iterator attackListLast = std::end(AttackWhos);
	switch (objectA->GetObjectType())
	{
	case GameObjectType::Alliance:
		[[fallthrough]];
	case GameObjectType::Footman:
		[[fallthrough]];
	case GameObjectType::Rifleman:
		[[fallthrough]];
	case GameObjectType::Knight:
		Level3Object* affectObject = dynamic_cast<Level3Object*>(objectA);
		int targetID = affectObject->GetIdentityID();
		if (std::find(attackListFirst, attackListLast, targetID) == attackListLast)
		{
			if(affectObject != nullptr && affectObject->isDead() == false)
			{
				AttackWhos.push_back(targetID);
			}
		}
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
	Tauren* tauren = static_cast<Tauren*>(object);
	tauren->SetVelocity(-tauren->speed);
	tauren->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Walk_Anim));
}

void Tauren::State_Walking::Update(GameObject*, double) {}

void Tauren::State_Walking::TestForExit(GameObject* object)
{
	Tauren* tauren = static_cast<Tauren*>(object);
	if (tauren->isDead() == true)
	{
		tauren->ChangeState(&tauren->stateDead);
	}
	else if(tauren->AttackWhos.empty() == false)
	{
		tauren->ChangeState(&tauren->stateAttack);
	}
}

void Tauren::State_Attack::Enter(GameObject* object)
{
	Tauren* tauren = static_cast<Tauren*>(object);
	tauren->SetVelocity({ 0,0 });
	tauren->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Attack_Anim));
}

void Tauren::State_Attack::Update(GameObject* object, double dt)
{

	Tauren* tauren = static_cast<Tauren*>(object);
	tauren->attackTimer += dt;
	if (tauren->attackTimer >= tauren->attackSpeed)
	{
		std::list<int> removeList;
		for(GameObject* allObj : Engine::GetGSComponent<CS230::GameObjectManager>()->Objects())
		{
			for (int affectObjID : tauren->AttackWhos)
			{
				Level3Object* targetObj = dynamic_cast<Level3Object*>(allObj);
				if (targetObj != nullptr && affectObjID == targetObj->GetIdentityID() && targetObj->isDead() == false)
				{
					targetObj->UpdateHP(-tauren->attackDamage);
				} else
				{
					removeList.push_back(affectObjID);
				}
			}
		}
		for(int removeWho : removeList)
		{
			tauren->AttackWhos.remove(removeWho);
		}
		tauren->attackTimer = 0;
	}
	
}

void Tauren::State_Attack::TestForExit(GameObject* object)
{
	Tauren* tauren = static_cast<Tauren*>(object);
	if (tauren->AttackWhos.empty() == true)
	{
		tauren->ChangeState(&tauren->stateWalking);
	}
	if (tauren->isDead() == true)
	{
		tauren->ChangeState(&tauren->stateDead);
	}
}

void Tauren::State_Dead::Enter(GameObject* object)
{
	Tauren* tauren = static_cast<Tauren*>(object);
	tauren->SetVelocity({ 0,0 });
	tauren->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Unit_Anims::Dead_Anim));
	tauren->AttackWhos.clear();
	tauren->RemoveGOComponent<CS230::Collision>();
	tauren->RemoveGOComponent<HPBar>();
	Engine::GetGSComponent<Score>()->AddScore(300);
}

void Tauren::State_Dead::Update(GameObject*, double) {}

void Tauren::State_Dead::TestForExit(GameObject* object)
{
	Tauren* tauren = static_cast<Tauren*>(object);
	if (tauren->GetGOComponent<CS230::Sprite>()->GetCurrentAnim() == static_cast<int>(Unit_Anims::Dead_Anim) && tauren->GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true)
	{
		tauren->Destroy();
	}
}


