/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Knight.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 06/04/2021
-----------------------------------------------------------------*/
#include "Knight.h"
#include "Knight_Anims.h"
#include "../Engine/Sprite.h"
#include "../Engine/Collision.h"
Knight::Knight(int hp, int ad, math::vec2 position) : GameObject(position), hp(hp), ad(ad), CollideWithWhat(nullptr)
{
	AddGOComponent(new CS230::Sprite("assets/knight_S.spt", this));
	ChangeState(&stateWalking);
}

void Knight::ResolveCollision(GameObject* objectA)
{
	CollideWithWhat = objectA;
	switch(objectA->GetObjectType())
	{
	case GameObjectType::Hatchery:
		ChangeState(&stateAttack);
		break;
	case GameObjectType::Knight:
		ChangeState(&stateWaiting);
		break;
	}
}

void Knight::State_Walking::Enter(GameObject* object)
{
	Knight* knight = static_cast<Knight*>(object);
	knight->SetVelocity(speed);
	knight->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Knight_Anims::Walk_Anim));
}

void Knight::State_Walking::Update(GameObject*, double) {}

void Knight::State_Walking::TestForExit(GameObject* object)
{
	Knight* knight = static_cast<Knight*>(object);
	if (knight->hp <= 0)
	{
		knight->ChangeState(&knight->stateDead);
	}
}

void Knight::State_Attack::Enter(GameObject* object)
{
	Knight* knight = static_cast<Knight*>(object);
	knight->SetVelocity({ 0,0 });
	knight->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Knight_Anims::Attack_Anim));
}

void Knight::State_Attack::Update(GameObject*, double) {}

void Knight::State_Attack::TestForExit(GameObject* object)
{
	Knight* knight = static_cast<Knight*>(object);
	if (knight->DoesCollideWith(knight->CollideWithWhat) == false)
	{
		knight->ChangeState(&knight->stateWalking);
	}
	if (knight->hp <= 0)
	{
		knight->ChangeState(&knight->stateDead);
	}
}

//void Knight::State_WalkingAttack::Enter(GameObject* object)
//{
//}
//
//void Knight::State_WalkingAttack::Update(GameObject* object, double dt)
//{
//}
//
//void Knight::State_WalkingAttack::TestForExit(GameObject* object)
//{
//}

void Knight::State_Waiting::Enter(GameObject* object)
{
	Knight* knight = static_cast<Knight*>(object);
	knight->SetVelocity({0,0});
	knight->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Knight_Anims::Waiting_Anim));
}

void Knight::State_Waiting::Update(GameObject*, double)
{
}

void Knight::State_Waiting::TestForExit(GameObject* object)
{
	Knight* knight = static_cast<Knight*>(object);
	if(knight->DoesCollideWith(knight->CollideWithWhat)==false)
	{
		knight->ChangeState(&knight->stateWalking);
	}
}

void Knight::State_Dead::Enter(GameObject* object)
{
	Knight* knight = static_cast<Knight*>(object);
	knight->SetVelocity({ 0,0 });
	knight->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Knight_Anims::Dead_Anim));
	knight->RemoveGOComponent<CS230::Collision>();
}

void Knight::State_Dead::Update(GameObject*, double) {}

void Knight::State_Dead::TestForExit(GameObject* object)
{
	Knight* knight = static_cast<Knight*>(object);
	if (knight->GetGOComponent<CS230::Sprite>()->GetCurrentAnim() == static_cast<int>(Knight_Anims::Dead_Anim) && knight->GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true)
	{
		knight->Destroy();
	}
}


