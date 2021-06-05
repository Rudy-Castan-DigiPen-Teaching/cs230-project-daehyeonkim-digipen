/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetLogger
#include "../Engine/Camera.h"
#include "../Engine/Collision.h"
#include "../Engine/GameObjectManager.h"
#include "Level1.h"	//Level1::gravity
#include "Hero.h"
#include "GameParticles.h"
#include "Gravity.h"
#include "Hero_Anims.h"

Hero::Hero(math::vec2 startPos) : GameObject(startPos),
									jumpKey(CS230::InputKey::Keyboard::Up),
									moveLeftKey(CS230::InputKey::Keyboard::Left), moveRightKey(CS230::InputKey::Keyboard::Right),
									hurtTimer(0), drawHero(true) {
	AddGOComponent(new CS230::Sprite("assets/Hero.spt", this));
	currState = &stateIdle;
	currState->Enter(this);
	CS230::GameObjectManager* gom = Engine::GetGSComponent<CS230::GameObjectManager>();
	for (GameObject* objPtr : gom->Objects()) {
		if (objPtr->GetObjectType() == GameObjectType::Floor && DoesCollideWith(objPtr) == true) {
			standingOnObject = objPtr;
			SetPosition({ GetPosition().x, objPtr->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Top() });
			break;
		}
	}
}

void Hero::Update(double dt) {
	if (hurtTimer > 0) {
		hurtTimer -= dt;
		drawHero = !drawHero;
		if (hurtTimer <= 0) {
			hurtTimer = 0;
			drawHero = true;
		}
	}

	GameObject::Update(dt);

	// Boundry Check
	CS230::Camera* cameraPtr = Engine::GetGSComponent<CS230::Camera>();
	if (GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Left() < cameraPtr->GetPosition().x) {
		UpdatePosition({cameraPtr->GetPosition().x - GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Left(), 0});
		SetVelocity({ 0, GetVelocity().y });
	}
	if (GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Right() > cameraPtr->GetPosition().x + Engine::GetWindow().GetSize().x) {
		UpdatePosition({ cameraPtr->GetPosition().x + Engine::GetWindow().GetSize().x - GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Right(), 0 });
		SetVelocity({ 0, GetVelocity().y });
	}
}

void Hero::Draw(math::TransformMatrix displayMatrix) {
	if (drawHero == true) {
		CS230::GameObject::Draw(displayMatrix);
	}
}

void Hero::State_Idle::Enter(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Idle_Anim));
	if (hero->standingOnObject == nullptr) {
		Engine::GetLogger().LogError("Hero standing on null");
	}
}
void Hero::State_Idle::Update(GameObject*, double) {}
void Hero::State_Idle::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveLeftKey.IsKeyDown() == true) {
		hero->ChangeState(&hero->stateRunning);
	}
	if (hero->moveRightKey.IsKeyDown() == true) {
		hero->ChangeState(&hero->stateRunning);
	}
	if (hero->jumpKey.IsKeyDown() == true) {
		hero->ChangeState(&hero->stateJumping);
	}
}

void Hero::State_Running::Enter(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Run_Anim));
	if (hero->moveRightKey.IsKeyDown() == true) {
		hero->SetScale({ 1, 1 });
	}
	if (hero->moveLeftKey.IsKeyDown() == true) {
		hero->SetScale({ -1, 1 });
	}
	if (hero->standingOnObject == nullptr) {
		Engine::GetLogger().LogError("Hero running on null");
	}
}
void Hero::State_Running::Update(GameObject* object, double dt) {
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateXVelocity(dt);
}
void Hero::State_Running::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveLeftKey.IsKeyDown() == true && hero->GetVelocity().x > 0) {
		hero->ChangeState(&hero->stateSkidding);
	}
	if (hero->moveRightKey.IsKeyDown() == true && hero->GetVelocity().x < 0) {
		hero->ChangeState(&hero->stateSkidding);
	}
	if (hero->GetVelocity().x == 0) {
		hero->ChangeState(&hero->stateIdle);
	}
	if (hero->jumpKey.IsKeyDown() == true) {
		hero->ChangeState(&hero->stateJumping);
	}
	if (hero->standingOnObject != nullptr && hero->standingOnObject->DoesCollideWith(hero->GetPosition()) == false) {
		hero->standingOnObject = nullptr;
		hero->ChangeState(&hero->stateFalling);
	}
}

void Hero::State_Skidding::Enter(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Skid_Anim));
}
void Hero::State_Skidding::Update(GameObject* object, double dt) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->GetVelocity().x > 0) {
		hero->SetVelocity({hero->GetVelocity().x - (xDrag + xAccel) * dt, hero->GetVelocity().y });
	} else if (hero->GetVelocity().x < 0) {
		hero->SetVelocity({ hero->GetVelocity().x + (xDrag + xAccel) * dt, hero->GetVelocity().y });
	}
}
void Hero::State_Skidding::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveLeftKey.IsKeyDown() == true) {
		if (hero->GetVelocity().x <= 0) {
			hero->ChangeState(&hero->stateRunning);
		}
	} else if (hero->moveRightKey.IsKeyDown() == true) {
		if (hero->GetVelocity().x >= 0) {
			hero->ChangeState(&hero->stateRunning);
		}
	} else {
		hero->ChangeState(&hero->stateRunning);
	}
	if (hero->jumpKey.IsKeyDown() == true) {
		hero->ChangeState(&hero->stateJumping);
	}
}

void Hero::State_Jumping::Enter(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Jump_Anim));
	hero->SetVelocity({ hero->GetVelocity().x, Hero::jumpVelocity });
	hero->standingOnObject = nullptr;
}
void Hero::State_Jumping::Update(GameObject* object, double dt) {
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateVelocity({ 0, -Engine::GetGSComponent<Gravity>()->GetValue() * dt });
	hero->UpdateXVelocity(dt);
}
void Hero::State_Jumping::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->jumpKey.IsKeyDown() == false) {
		hero->ChangeState(&hero->stateFalling);
		hero->SetVelocity({ hero->GetVelocity().x, 0 });
	} else if (hero->GetVelocity().y <= 0) {
		hero->ChangeState(&hero->stateFalling);
	}
}

void Hero::State_Falling::Enter(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Fall_Anim));
}
void Hero::State_Falling::Update(GameObject* object, double dt) {
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateVelocity({ 0, -Engine::GetGSComponent<Gravity>()->GetValue() * dt });
	hero->UpdateXVelocity(dt);
}
void Hero::State_Falling::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->standingOnObject != nullptr) {
		if (hero->GetVelocity().x > 0) {
			if (hero->moveLeftKey.IsKeyDown() == true) {
				hero->ChangeState(&hero->stateSkidding);
			} else {
				hero->ChangeState(&hero->stateRunning);
			}
		} else if (hero->GetVelocity().x < 0) {
			if (hero->moveRightKey.IsKeyDown() == true) {
				hero->ChangeState(&hero->stateSkidding);
			} else {
				hero->ChangeState(&hero->stateRunning);
			}
		} else {
			hero->ChangeState(&hero->stateIdle);
		}
		hero->SetVelocity({ hero->GetVelocity().x, 0 });
	}
	if (hero->GetPosition().y < -300) {
		hero->isDead = true;
	}
}

void Hero::UpdateXVelocity(double dt) {
	if (moveLeftKey.IsKeyDown() == true) {
		UpdateVelocity({ -Hero::xAccel * dt, 0 });		// apply acceleration
		if (GetVelocity().x < -Hero::maxXVelocity) {
			SetVelocity({ -Hero::maxXVelocity, GetVelocity().y });
		}
	} else if (moveRightKey.IsKeyDown() == true) {
		UpdateVelocity({ Hero::xAccel * dt, 0 });		// apply acceleration
		if (GetVelocity().x > Hero::maxXVelocity) {
			SetVelocity({ Hero::maxXVelocity, GetVelocity().y });
		}
	} else {
		// no key is down, need to apply drag to slow down
		double xDragDt = Hero::xDrag * dt;
		if (GetVelocity().x > xDragDt) {
			UpdateVelocity({ -xDragDt, 0 });
		} else if (GetVelocity().x < -xDragDt) {
			UpdateVelocity({ xDragDt, 0 });
		} else {
			SetVelocity({ 0, GetVelocity().y });
		}
	}
}

bool Hero::CanCollideWith(GameObjectType objectType) {
	if (objectType == GameObjectType::Particle) {
		return false;
	}
	return true;
}

void Hero::ResolveCollision(GameObject* objectB) {
	math::rect2 collideRect = objectB->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
	math::rect2 heroRect = GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();

	switch (objectB->GetObjectType()) {
	case GameObjectType::Ball:
		if (currState == &stateFalling) {
			if (GetPosition().y > collideRect.Bottom()) {
				SetVelocity({ GetVelocity().x, Hero::jumpVelocity });
			}
			return;
		}
		hurtTimer = Hero::hurtTime;
		if (heroRect.Left() < collideRect.Left()) {
			SetPosition({ GetPosition().x - (heroRect.Right() - collideRect.Left()), GetPosition().y });
			SetVelocity({ -Hero::xAccel / 2, Hero::jumpVelocity / 4 });
			ChangeState(&stateFalling);
			standingOnObject = nullptr;
		} else {
			SetPosition({ GetPosition().x + (collideRect.Right() - heroRect.Left()), GetPosition().y });
			SetVelocity({ Hero::xAccel / 2, Hero::jumpVelocity / 4 });
			ChangeState(&stateFalling);
			standingOnObject = nullptr;
		}
		break;
	case GameObjectType::Bunny:
		if (currState == &stateFalling) {
			if (GetPosition().y > collideRect.Bottom()) {
				objectB->ResolveCollision(this);
				math::vec2 particlePos;
				if (GetVelocity().x < 0) {
					particlePos = { (heroRect.Left() + collideRect.Right()) / 2, (heroRect.Bottom() + collideRect.Top()) / 2 };
				} else {
					particlePos = { (heroRect.Right() + collideRect.Left()) / 2, (heroRect.Bottom() + collideRect.Top()) / 2 };
				}
				Engine::GetGameStateManager().GetGSComponent<SmokeEmitter>()->Emit(1, particlePos, { 0, 0 }, { 0,0 }, 0);
				SetVelocity({ GetVelocity().x, Hero::jumpVelocity / 2 });
				return;
			}
		} else if (currState == &stateSkidding) {
			objectB->ResolveCollision(this);
			math::vec2 particlePos;
			if (GetVelocity().x < 0) {
				particlePos = { (heroRect.Left() + collideRect.Right()) / 2, (heroRect.Bottom() + collideRect.Bottom()) / 2 };
			} else {
				particlePos = { (heroRect.Right() + collideRect.Left()) / 2, (heroRect.Bottom() + collideRect.Bottom()) / 2 };
			}
			Engine::GetGameStateManager().GetGSComponent<SmokeEmitter>()->Emit(1, particlePos, { 0, 0 }, { 0,0 }, 0);
			return;
		}
		hurtTimer = Hero::hurtTime;
		if (heroRect.Left() < collideRect.Left()) {
			UpdatePosition(math::vec2{ (collideRect.Left() - heroRect.Right()), 0.0 });
			SetVelocity({ -Hero::xAccel / 2, Hero::jumpVelocity / 4 });
			ChangeState(&stateFalling);
			standingOnObject = nullptr;
		} else {
			UpdatePosition(math::vec2{ (collideRect.Right() - heroRect.Left()), 0.0 });
			SetVelocity({ Hero::xAccel / 2, Hero::jumpVelocity / 4 });
			ChangeState(&stateFalling);
			standingOnObject = nullptr;
		}
		break;
	case GameObjectType::Floor: [[fallthrough]];
	case GameObjectType::TreeStump:
		if (currState == &stateFalling) {
			if (heroRect.Top() > collideRect.Top() && objectB->DoesCollideWith(GetPosition())) {
				SetPosition({ GetPosition().x, collideRect.Top() });
				standingOnObject = objectB;
				if (GetVelocity().y < -jumpVelocity) {
					Engine::GetGameStateManager().GetGSComponent<SmokeEmitter>()->Emit(1, GetPosition(), { 0, 0 }, { 0,0 }, 0);
				}
				currState->TestForExit(this);
				return;
			}
		}
		if (heroRect.Left() < collideRect.Left()) {
			UpdatePosition(math::vec2{ (collideRect.Left() - heroRect.Right()), 0.0 });
			SetVelocity({ 0, GetVelocity().y });
		} else {
			UpdatePosition(math::vec2{ (collideRect.Right() - heroRect.Left()), 0.0 });
			SetVelocity({ 0, GetVelocity().y });
		}
		break;
	case GameObjectType::Trigger:
		objectB->ResolveCollision(this);
		break;
	}

}