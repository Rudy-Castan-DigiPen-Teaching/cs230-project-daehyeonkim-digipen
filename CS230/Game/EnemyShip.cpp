/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EnemyShip.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 5/25/2021
-----------------------------------------------------------------*/
#include "EnemyShip.h"

#include "Flame_Anims.h"
#include "GameObjectTypes.h"
#include "Score.h"
#include "Ship_Anims.h"
#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
#include "../Engine/ShowCollision.h"

EnemyShip::EnemyShip(GameObject* player) : GameObject(), player(player), isDead(false), flameLeft("assets/Flame.spt", this), flameRight("assets/Flame.spt", this)
{
	AddGOComponent(new CS230::Sprite("assets/enemyShip.spt", this));
	constexpr double PI = 3.141592;
	SetRotation((rand() % static_cast<int>(1024 * 2 * PI)) / 1024.0);
	SetPosition(player->GetPosition() + (math::RotateMatrix(GetRotation()) * math::vec2{ 0, -((rand() % 1024) + 1024.0)}));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::None_Anim));
	flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
	flameRight.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
}

void EnemyShip::Update(double dt)
{
	const math::vec2 playerDirection = player->GetPosition() - GetPosition();
	const math::vec2 facingDirection_accel = math::RotateMatrix(GetRotation()) * math::vec2{ 0, accel };
	const double facing_player_cross = facingDirection_accel.Normalize().Cross(playerDirection.Normalize());
	if(isDead == false)
	{
		if (facing_player_cross >= 0.05)
		{
			UpdateRotation(rotationRate * dt);
		}
		else if (facing_player_cross <= -0.05)
		{
			UpdateRotation(rotationRate * -dt);
		}
		UpdateVelocity(facingDirection_accel *dt);
		UpdateVelocity(-GetVelocity() * drag * dt);
	}
	UpdatePosition(GetVelocity() * dt);
	flameLeft.Update(dt);
	flameRight.Update(dt);
	UpdateGOComponents(dt);
	if (GetGOComponent<CS230::Sprite>()->GetCurrAnim() == static_cast<int>(Ship_Anim::Explode_Anim) && GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true)
	{
		destroyed = true;
	}
}

void EnemyShip::Draw(math::TransformMatrix displayMatrix)
{
	flameLeft.Draw(GetMatrix() * math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)));
	flameRight.Draw(GetMatrix() * math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(2)));
	GetGOComponent<CS230::Sprite>()->Draw(GetMatrix());
	if (Engine::GetGSComponent<ShowCollision>() != nullptr && GetGOComponent<CS230::Collision>() != nullptr && Engine::GetGSComponent<ShowCollision>()->IsEnabled() == true)
	{
		GetGOComponent<CS230::Collision>()->Draw(displayMatrix);
	}
}

bool EnemyShip::CanCollideWith(GameObjectType collideAgainstType)
{
	return (collideAgainstType == GameObjectType::Laser || collideAgainstType == GameObjectType::Ship) == true;
}

void EnemyShip::ResolveCollision(GameObject* collidedWith)
{
	switch(collidedWith->GetObjectType())
	{
	case GameObjectType::Laser:
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::Explode_Anim));
		RemoveGOComponent<CS230::Collision>();
		Engine::GetGSComponent<Score>()->AddScore(300);
		isDead = true;
		flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		break;
	}
}
