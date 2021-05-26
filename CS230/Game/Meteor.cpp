/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Meteor.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 4/19/2021
-----------------------------------------------------------------*/
#include "Meteor.h"

#include "GameParticles.h"
#include "Meteor_Anims.h"
#include "Score.h"
#include "ScreenWarp.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"

Meteor::Meteor() : GameObject({ 0,0 }), health(100), size(1)
{
	AddGOComponent(new CS230::Sprite("assets/Meteor.spt", this));
	AddGOComponent(new ScreenWrap(*this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::None_Anim));
	SetVelocity({ (rand() % 200) - 100.0,(rand() % 200) - 100.0 });
	SetPosition({ (rand() % Engine::GetWindow().GetSize().x + static_cast<double>(GetGOComponent<CS230::Sprite>()->GetFrameSize().x)) - GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0, (rand() % Engine::GetWindow().GetSize().y + static_cast<double>(GetGOComponent<CS230::Sprite>()->GetFrameSize().y)) - GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0 });
	SetRotation({ (rand() % static_cast<int>(1024 * 2 * PI)) / 1024.0 });
	const double scales = ((rand() % 1024) / 4096.0) + 0.75;
	SetScale({ scales,scales });
}

Meteor::Meteor(Meteor& original) : GameObject(original.GetPosition()), size(original.size), health(100)
{
	
	AddGOComponent(new CS230::Sprite("assets/Meteor.spt", this));
	AddGOComponent(new ScreenWrap(*this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::None_Anim));
	SetVelocity({ original.GetVelocity()});
	SetPosition({ original.GetPosition() });
	SetRotation({ (rand() % static_cast<int>(1024 * 2 * PI)) / 1024.0 });
	size++;
	if(size == 2)
	{
		const double scales = ((rand() % 1024) / 4096.0) + 0.5;
		SetScale({ scales,scales });
	} else if(size == 3)
	{
		const double scales = ((rand() % 1024) / 4096.0) + 0.25;
		SetScale({ scales,scales });
	}
}

void Meteor::Update(double dt)
{
	GameObject::Update(dt);
	if (GetGOComponent<CS230::Sprite>()->GetCurrAnim() == static_cast<int>(Meteor_Anim::Fade_Anim) && GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true) 
	{
		destroyed = true;
	}
}

void Meteor::ResolveCollision(GameObject* objectB)
{
	switch(objectB->GetObjectType())
	{
	case GameObjectType::Laser:
		health -= 10;
		math::vec2 vectorToObject = objectB->GetPosition() - GetPosition();
		math::vec2 collisionSpot = GetPosition() + (vectorToObject.Normalize() * GetGOComponent<CS230::CircleCollision>()->GetRadius());
		Engine::GetGSComponent<HitEmitter>()->Emit(1, collisionSpot, GetVelocity(), { 0,0 }, 0);
		Engine::GetGSComponent<MeteorBitEmitter>()->Emit(10, collisionSpot, GetVelocity(),  math::ScaleMatrix({ 50,50 }) * (vectorToObject.Normalize() * 2 + GetVelocity().Normalize()), PI / 2);

		if(health == 0)
		{
			if(size != 3)
			{
 				constexpr double offsetAngle = PI / 6.0;
				Meteor* smallMeteor1 = new Meteor{ *this };
				smallMeteor1->SetVelocity(math::RotateMatrix(offsetAngle) * GetVelocity());
				Meteor* smallMeteor2 = new Meteor{ *this };
				smallMeteor2->SetVelocity(math::RotateMatrix(-offsetAngle) * GetVelocity());
				Engine::GetGSComponent<CS230::GameObjectManager>()->Add(smallMeteor1);
				Engine::GetGSComponent<CS230::GameObjectManager>()->Add(smallMeteor2);
			}
			GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::Fade_Anim));
   			RemoveGOComponent<CS230::Collision>();
			Engine::GetGSComponent<Score>()->AddScore(100 * size);
		} else
		{
			UpdateVelocity(objectB->GetVelocity() * 0.01);
		}
		break;
	}
}
