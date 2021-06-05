/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Enemy.cpp
Project: CS230
Author: Kevin Wright
Creation date: 3/1/2021
-----------------------------------------------------------------*/
#include "..\Engine\Engine.h"	//Logger, Window
#include "..\Engine\GameObject.h"		//GetCollision
#include "..\Engine\Collision.h"		
#include "..\Engine\ShowCollision.h"
#include "ScreenWrap.h"
#include "EnemyShip.h"
#include "Score.h"
#include "Flame_Anims.h"
#include "Ship_Anims.h"
#include "GameObjectTypes.h"

constexpr double PI = 3.1415926535897932384626433832795;

EnemyShip::EnemyShip(GameObject* player) : player(player), isDead(false),
							flameLeft("assets/flame.spt", this), flameRight("assets/flame.spt", this) {
	SetRotation((rand() % 1024 / 1024.0) * 2 * PI);
	SetPosition(math::RotateMatrix(GetRotation()) * math::vec2{ 0, -(rand() % 1024 + 1024.0) } + player->GetPosition());
	AddGOComponent(new CS230::Sprite("assets/EnemyShip.spt", this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::None_Anim));
	flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
	flameRight.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
}

void EnemyShip::Update(double dt) {
	flameLeft.Update(dt);
	flameRight.Update(dt);
	if (IsDead() == false) {
		math::vec2 facingDir = math::RotateMatrix(GetRotation()) * math::vec2 { 0, 1 };
		math::vec2 diffVector = (player->GetPosition() - GetPosition()).Normalize();

		double cross = facingDir.Cross(diffVector);
		Engine::GetLogger().LogDebug("Cross result = " + std::to_string(cross));
		if (cross <= -0.05) {
			UpdateRotation(-EnemyShip::rotationRate * dt);
		}
		if (cross >= 0.05) {
			UpdateRotation(EnemyShip::rotationRate * dt);
		}
		SetVelocity(GetVelocity() + math::RotateMatrix(GetRotation()) * math::vec2{ 0, accel * dt });
	}
	SetVelocity(GetVelocity() - GetVelocity() * EnemyShip::drag * dt);
	UpdatePosition(GetVelocity() * dt);

	UpdateGOComponents(dt);
}

void EnemyShip::Draw(math::TransformMatrix cameraMatrix) {
	math::TransformMatrix shipScreenMatrix = cameraMatrix * GetMatrix();
	flameRight.Draw(shipScreenMatrix * math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)));
	flameLeft.Draw(shipScreenMatrix * math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(2)));
	GetGOComponent<CS230::Sprite>()->Draw(shipScreenMatrix);

	ShowCollision* showCollisionPtr = Engine::GetGSComponent<ShowCollision>();
	if (showCollisionPtr != nullptr && showCollisionPtr->IsEnabled() == true) {
		CS230::Collision* collisionPtr = GetGOComponent<CS230::Collision>();
		if (collisionPtr != nullptr) {
			collisionPtr->Draw(cameraMatrix);
		}
	}
}

GameObjectType EnemyShip::GetObjectType() {
	return GameObjectType::EnemyShip;
}

std::string EnemyShip::GetObjectTypeName() {
	return "Enemy";
}

bool EnemyShip::CanCollideWith(GameObjectType) {
	return false;
}

void EnemyShip::ResolveCollision(GameObject* collidedWith) {
	switch (collidedWith->GetObjectType()) {
	case GameObjectType::Laser:
		Engine::GetGSComponent<Score>()->AddScore(300);
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::Explode_Anim));
		flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		isDead = true;
		collidedWith->Destroy();
		RemoveGOComponent<CS230::Collision>();
		break;
	}
}