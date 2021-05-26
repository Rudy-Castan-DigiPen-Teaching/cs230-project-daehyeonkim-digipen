/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Bunny.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 04/19/2021
-----------------------------------------------------------------*/
#include "Bunny.h"
#include "Bunny_Anims.h"
#include "Hero.h"
#include "../Engine/Collision.h"

Bunny::Bunny(math::vec2 pos, std::vector<double> patrolNodes, Hero* heroPtr) : GameObject(pos), patrolNodes(patrolNodes), heroPtr(heroPtr), currPatrolNode(0)
{
	AddGOComponent(new CS230::Sprite("assets/Bunny.spt", this));
	currState = &statePatrol;
	currState->Enter(this);
}

void Bunny::ResolveCollision(GameObject* objectA)
{
	switch (objectA->GetObjectType())
	{
	case GameObjectType::Hero:
		ChangeState(&stateDead);
		break;
	}
}

void Bunny::State_Patrol::Enter(GameObject* object)
{
	Bunny* bunny = static_cast<Bunny*>(object);
	if(bunny->GetPosition().x > bunny->patrolNodes[bunny->currPatrolNode])
	{
		bunny->SetScale({ -1,1 });
		bunny->SetVelocity({ -bunny->velocity, 0 });
	} else if (bunny->GetPosition().x < bunny->patrolNodes[bunny->currPatrolNode])
	{
		bunny->SetScale({ 1,1 });
		bunny->SetVelocity({ bunny->velocity, 0 });
	}
	bunny->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Walk_Anim));
}

void Bunny::State_Patrol::Update(GameObject* object, double)
{
	Bunny* bunny = static_cast<Bunny*>(object);
	if ((bunny->GetPosition().x >= bunny->patrolNodes[bunny->currPatrolNode] && bunny->GetVelocity().x > 0) || (bunny->GetPosition().x <= bunny->patrolNodes[bunny->currPatrolNode] && bunny->GetVelocity().x < 0))
	{
		bunny->ChangeState(this);
		bunny->currPatrolNode++;
		bunny->currPatrolNode = bunny->currPatrolNode % bunny->patrolNodes.size();
	}
}

void Bunny::State_Patrol::TestForExit(GameObject* object)
{
	Bunny* bunny = static_cast<Bunny*>(object);
	bool isPlayerGround = bunny->heroPtr->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Bottom() <= bunny->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Bottom();
	bool isPlayerFrontBunny = bunny->GetVelocity().x > 0 ? (bunny->heroPtr->GetPosition().x >= bunny->GetPosition().x) == true : (bunny->heroPtr->GetPosition().x <= bunny->GetPosition().x) == true;
	bool isPlayerInNode = bunny->GetVelocity().x > 0 ? (bunny->heroPtr->GetPosition().x < bunny->patrolNodes[bunny->currPatrolNode]) == true : (bunny->heroPtr->GetPosition().x > bunny->patrolNodes[bunny->currPatrolNode]) == true;
	if(isPlayerGround == true && isPlayerFrontBunny == true && isPlayerInNode == true)
	{
		bunny->ChangeState(&bunny->stateAttack);
	}
}

void Bunny::State_Attack::Enter(GameObject* object)
{
	Bunny* bunny = static_cast<Bunny*>(object);
	bunny->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Attack_Anim));
	bunny->UpdateVelocity(bunny->GetVelocity());
}

void Bunny::State_Attack::Update(GameObject* object, double)
{
	Bunny* bunny = static_cast<Bunny*>(object);
	if ((bunny->GetPosition().x >= bunny->patrolNodes[bunny->currPatrolNode] && bunny->GetVelocity().x > 0) || (bunny->GetPosition().x <= bunny->patrolNodes[bunny->currPatrolNode] && bunny->GetVelocity().x < 0))
	{
		bunny->ChangeState(&bunny->statePatrol);
		bunny->currPatrolNode++;
		bunny->currPatrolNode = bunny->currPatrolNode % bunny->patrolNodes.size();
	}
}

void Bunny::State_Attack::TestForExit(GameObject*)
{
}

void Bunny::State_Dead::Enter(GameObject* object)
{
	Bunny* bunny = static_cast<Bunny*>(object);
	bunny->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Dead_Anim));
	bunny->RemoveGOComponent<CS230::Collision>();
	bunny->SetVelocity({ 0,0 });
}

void Bunny::State_Dead::Update(GameObject*, double)
{
}

void Bunny::State_Dead::TestForExit(GameObject*)
{
}
