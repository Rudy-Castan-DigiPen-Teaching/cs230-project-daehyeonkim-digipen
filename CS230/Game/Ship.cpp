/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"    //Engine::GetWindow
#include "../Engine/TransformMatrix.h"
#include "../Engine/Sprite.h"
#include "../Engine/ShowCollision.h"
#include "../Engine/Collision.h"
#include "../Engine/GameObjectManager.h"
#include "Ship.h"
#include "Laser.h"
#include "Flame_Anims.h"
#include "Ship_Anims.h"
#include "ScreenWrap.h"

Ship::Ship(math::vec2 pos) : GameObject(pos, 0, { .75, .75 }), rotateCounterKey(CS230::InputKey::Keyboard::A),
			rotateClockKey(CS230::InputKey::Keyboard::D), accelerateKey(CS230::InputKey::Keyboard::W), isAccelerating(false),
			flameLeft("assets/flame.spt", this), flameRight("assets/flame.spt", this),
			fireLazerKey(CS230::InputKey::Keyboard::Space), isDead(false) {
	AddGOComponent(new CS230::Sprite("assets/Ship.spt", this));
	AddGOComponent(new ScreenWrap(*this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::None_Anim));
	flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
}

void Ship::Update(double dt) {
	flameLeft.Update(dt);
	flameRight.Update(dt);

	if (IsDead() == false) {
		if (rotateClockKey.IsKeyDown() == true) {
			UpdateRotation(-Ship::rotationRate * dt);
		}
		if (rotateCounterKey.IsKeyDown() == true) {
			UpdateRotation(Ship::rotationRate * dt);
		}
		if (accelerateKey.IsKeyDown() == true) {
			SetVelocity(GetVelocity() + math::RotateMatrix(GetRotation()) * math::vec2{ 0, accel * dt });
			if (isAccelerating == false) {
				flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
				flameRight.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
				isAccelerating = true;
			}
		} else {
			if (isAccelerating == true) {
				flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
				flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
				isAccelerating = false;
			}
		}
		if (fireLazerKey.IsKeyReleased() == true) {
			Engine::GetGSComponent<CS230::GameObjectManager>()->Add(
				new Laser(GetMatrix() * static_cast<math::vec2>(GetGOComponent<CS230::Sprite>()->GetHotSpot(3)),
					GetRotation(), GetScale(), math::RotateMatrix(GetRotation()) * Laser::LaserVelocity));
			Engine::GetGSComponent<CS230::GameObjectManager>()->Add(
				new Laser(GetMatrix() * static_cast<math::vec2>(GetGOComponent<CS230::Sprite>()->GetHotSpot(4)),
					GetRotation(), GetScale(), math::RotateMatrix(GetRotation()) * Laser::LaserVelocity));
		}
	}
	SetVelocity(GetVelocity() - GetVelocity() * Ship::drag * dt);
	UpdatePosition(GetVelocity() * dt);

	UpdateGOComponents(dt);
}

void Ship::Draw(math::TransformMatrix cameraMatrix) {

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

bool Ship::CanCollideWith(GameObjectType objectBType) {
	if (objectBType == GameObjectType::Meteor || objectBType == GameObjectType::EnemyShip) {
		return true;
	} else {
		return false;
	}
}

void Ship::ResolveCollision(CS230::GameObject* objectB) {
	switch (objectB->GetObjectType()) {
	case GameObjectType::EnemyShip: [[fallthrough]];
	case GameObjectType::Meteor:
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::Explode_Anim));
		flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		RemoveGOComponent<CS230::Collision>();
		isDead = true;
		break;
	}
}