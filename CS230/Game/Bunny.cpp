/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Bunny.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/15/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "../Engine/Collision.h"
#include "Hero.h"
#include "Score.h"
#include "Bunny.h"
#include "Bunny_Anims.h"

Bunny::Bunny(math::vec2 pos, std::vector<double> patrolNodes, Hero* heroPtr) : GameObject(pos),
									patrolNodes(patrolNodes), currPatrolNode(0), heroPtr(heroPtr) {
	AddGOComponent(new CS230::Sprite("assets/Bunny.spt", this));
	ChangeState(&statePatrol);
}


void Bunny::ResolveCollision(CS230::GameObject* objectA) {
    if (objectA->GetObjectType() == GameObjectType::Hero) {
		ChangeState(&stateDead);
        Engine::GetGSComponent<Score>()->AddScore(100);
    }
}

void Bunny::State_Patrol::Enter(GameObject* object) {
	Bunny* bunny = static_cast<Bunny*>(object);
	bunny->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Walk_Anim));
	if (bunny->GetPosition().x < bunny->patrolNodes[bunny->currPatrolNode]) {
		bunny->SetVelocity({ Bunny::velocity, 0 });
		bunny->SetScale({ 1, 1 });
	} else {
		bunny->SetVelocity({ -Bunny::velocity, 0 });
		bunny->SetScale({ -1, 1 });
	}
}

void Bunny::State_Patrol::Update(GameObject* object, double dt) {
	Bunny* bunny = static_cast<Bunny*>(object);
	math::vec2 newPos = bunny->GetPosition() + bunny->GetVelocity() * dt;
	if (bunny->GetPosition().x <= bunny->patrolNodes[bunny->currPatrolNode] && newPos.x >= bunny->patrolNodes[bunny->currPatrolNode] ||
		bunny->GetPosition().x >= bunny->patrolNodes[bunny->currPatrolNode] && newPos.x <= bunny->patrolNodes[bunny->currPatrolNode]) {
		if (bunny->currPatrolNode == bunny->patrolNodes.size() - 1) {
			bunny->currPatrolNode = 0;
		} else {
			bunny->currPatrolNode++;
		}
		bunny->ChangeState(this);
	}
}
void Bunny::State_Patrol::TestForExit(GameObject* object) {
	Bunny* bunny = static_cast<Bunny*>(object);

	const math::vec2& bunnyPos = bunny->GetPosition();
	const math::vec2& heroPos = bunny->heroPtr->GetPosition();

	if ((bunnyPos - heroPos).y == 0) {
		if ((bunny->GetVelocity().x < 0) && (heroPos.x < bunny->GetPosition().x && heroPos.x > bunny->patrolNodes[bunny->currPatrolNode])) {
			bunny->ChangeState(&bunny->stateAttack);
		}
		if ((bunny->GetVelocity().x > 0) && (heroPos.x > bunny->GetPosition().x && heroPos.x < bunny->patrolNodes[bunny->currPatrolNode])) {
			bunny->ChangeState(&bunny->stateAttack);
		}
	}
}

void Bunny::State_Attack::Enter(GameObject* object) {
	Bunny* bunny = static_cast<Bunny*>(object);
	bunny->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Attack_Anim));
	if (bunny->GetPosition().x < bunny->patrolNodes[bunny->currPatrolNode]) {
		bunny->SetVelocity({ Bunny::velocity * 2, 0 });
		bunny->SetScale({ 1, 1 });
	} else {
		bunny->SetVelocity({ -Bunny::velocity * 2, 0 });
		bunny->SetScale({ -1, 1 });
	}
}
void Bunny::State_Attack::Update(GameObject* object, double dt) {
	Bunny* bunny = static_cast<Bunny*>(object);
	math::vec2 newPos = bunny->GetPosition() + bunny->GetVelocity() * dt;
	if (bunny->GetPosition().x <= bunny->patrolNodes[bunny->currPatrolNode] && newPos.x >= bunny->patrolNodes[bunny->currPatrolNode] ||
		bunny->GetPosition().x >= bunny->patrolNodes[bunny->currPatrolNode] && newPos.x <= bunny->patrolNodes[bunny->currPatrolNode]) {
		if (bunny->currPatrolNode == bunny->patrolNodes.size() - 1) {
			bunny->currPatrolNode = 0;
		} else {
			bunny->currPatrolNode++;
		}
		bunny->ChangeState(&bunny->statePatrol);
	}
}
void Bunny::State_Attack::TestForExit(GameObject*) {
}

void Bunny::State_Dead::Enter(GameObject* object) {
	Bunny* bunny = static_cast<Bunny*>(object);
	bunny->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Dead_Anim));
	bunny->SetVelocity({ 0, 0 });
	bunny->RemoveGOComponent<CS230::Collision>();
}
void Bunny::State_Dead::Update(GameObject*, double) {}
void Bunny::State_Dead::TestForExit(GameObject*) {}