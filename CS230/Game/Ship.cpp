/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 3/17/2021
-----------------------------------------------------------------*/
#include "Ship.h"
#include "..\Engine\Engine.h"
#include "Flame_Anims.h"
#include "Laser.h"
#include "ScreenWarp.h"
#include "Ship_Anims.h"
#include "../Engine/Collision.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/ShowCollision.h"


Ship::Ship(math::vec2 startPos) : GameObject(startPos), wasAccel(false), isDead(false), rotateCounterKey(CS230::InputKey::Keyboard::A), rotateClockKey(CS230::InputKey::Keyboard::D), accelerateKey(CS230::InputKey::Keyboard::W), shootingKey(CS230::InputKey::Keyboard::Space), flameSpriteL("assets/Flame.spt", this), flameSpriteR("assets/Flame.spt", this)
{
	AddGOComponent(new CS230::Sprite("assets/Ship.spt", this));
	AddGOComponent(new ScreenWrap(*this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::None_Anim));

}

void Ship::Update(double dt)
{
	SetScale({ 0.75, 0.75 });
	if(isDead == false)
	{
		constexpr double rotateSpeed = 3.14159;
		if (rotateCounterKey.IsKeyDown() == true)
		{
			UpdateRotation(rotateSpeed * dt);
		}
		if (rotateClockKey.IsKeyDown() == true)
		{
			UpdateRotation(-rotateSpeed * dt);
		}
		if (accelerateKey.IsKeyDown() == true)
		{
			if (wasAccel == false)
			{
				flameSpriteL.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
				flameSpriteR.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
				wasAccel = true;
			}
			UpdateVelocity(math::RotateMatrix(GetRotation()) * accel * dt);
		}
		else
		{
			if (wasAccel == true)
			{
				flameSpriteL.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
				flameSpriteR.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
				wasAccel = false;
			}
		}
		if (shootingKey.IsKeyReleased() == true)
		{
			Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Laser(GetMatrix() * GetGOComponent<CS230::Sprite>()->GetHotSpot(3), GetRotation(), GetScale(), Laser::LaserVelocity));
			Engine::GetGSComponent<CS230::GameObjectManager>()->Add(new Laser(GetMatrix() * GetGOComponent<CS230::Sprite>()->GetHotSpot(4), GetRotation(), GetScale(), Laser::LaserVelocity));
		}
	}
	UpdateVelocity(-GetVelocity()*drag*dt);
	UpdatePosition(GetVelocity() * dt);
	flameSpriteL.Update(dt);
	flameSpriteR.Update(dt);
	UpdateGOComponents(dt);
}

void Ship::Draw(math::TransformMatrix cameraMatrix)
{
	flameSpriteL.Draw(GetMatrix() * math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)));
	flameSpriteR.Draw(GetMatrix() * math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(2)));
	GetGOComponent<CS230::Sprite>()->Draw(GetMatrix());
	if (Engine::GetGSComponent<ShowCollision>() != nullptr && GetGOComponent<CS230::Collision>() != nullptr && Engine::GetGSComponent<ShowCollision>()->IsEnabled() == true)
	{
 		GetGOComponent<CS230::Collision>()->Draw(cameraMatrix);
	}
}

bool Ship::CanCollideWith(GameObjectType objectBType)
{
	return objectBType == GameObjectType::Particle ? false : true;
}

void Ship::ResolveCollision(CS230::GameObject* objectB)
{
	switch (objectB->GetObjectType())
	{
	case GameObjectType::EnemyShip:
		[[fallthrough]];
	case GameObjectType::Meteor:
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::Explode_Anim));
		RemoveGOComponent<CS230::Collision>();
		isDead = true;
		flameSpriteL.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		flameSpriteR.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		break;
	}
}
