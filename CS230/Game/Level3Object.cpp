/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level3Object.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 06/05/2021
-----------------------------------------------------------------*/
#include "Level3Object.h"
#include "GameObjectTypes.h"
#include "GameParticles.h"
#include "../Engine/Collision.h"
#include "HPBar.h"
#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"

Level3Object::Level3Object(math::vec2 initPos, int hp, math::vec2 HPBarScale) : GameObject(initPos), hp(hp), HPBarScale(HPBarScale)
{
	AddGOComponent(new HPBar(hp, HPBarScale));
}

void Level3Object::Draw(math::TransformMatrix displayMatrix)
{
	GameObject::Draw(displayMatrix);
	HPBar* hpbar = GetGOComponent<HPBar>();
	if(hpbar != nullptr)
	{
		CS230::RectCollision* collisionPtr = GetGOComponent<CS230::RectCollision>();
		math::TransformMatrix barPosition;
		if(collisionPtr != nullptr)
		{
			math::vec2 objSize = collisionPtr->GetWorldCoorRect().Size();
			barPosition = math::TranslateMatrix(math::vec2{ -(HPBar::initBarSize.x * HPBarScale.x - objSize.x) / 2., (HPBar::initBarSize.y / 2.) * HPBarScale.y + objSize.y }) * math::TranslateMatrix(math::vec2{ -collisionPtr->GetWorldCoorRect().Size().x / 2, 0 });
		}
		hpbar->Draw(displayMatrix * GetMatrix() * barPosition);
	}

}

void Level3Object::UpdateHP(int _hp)
{
	HPBar* hpbar = GetGOComponent<HPBar>();
	if (hpbar != nullptr)
	{
		hpbar->UpdateHP(_hp);
	}
	this->hp += _hp;
	if(_hp < 0 && hp > 0)
	{
		constexpr double PI = 3.141592;
		switch(GetObjectType())
		{
		case GameObjectType::Footman:
			[[fallthrough]];
		case GameObjectType::Rifleman:
			[[fallthrough]];
		case GameObjectType::Knight:
			Engine::GetGameStateManager().GetGSComponent<UnitHurtEmitter>()->Emit(3, GetPosition() + math::vec2(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)), { GetVelocity() }, { 1,1 }, PI / 6);
			break;
		case GameObjectType::Grunt:
			[[fallthrough]];
		case GameObjectType::Shaman:
			[[fallthrough]];
		case GameObjectType::Tauren:
			Engine::GetGameStateManager().GetGSComponent<UnitHurtEmitter>()->Emit(3, GetPosition() + math::vec2(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)), { GetVelocity() }, { 1,1 }, PI / 6, {-1, 1});
			break;
		}
	}
}

int Level3Object::GetHP()
{
	return hp;
}

bool Level3Object::isDead()
{
	if(hp <= 0)
	{
		return true;
	}
	return false;
}
