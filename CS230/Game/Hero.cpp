/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 03/16/2021
-----------------------------------------------------------------*/
#include "Hero.h"

#include "GameParticles.h"
#include "Gravity.h"
#include "Level1.h"
#include "..\Engine\Engine.h"
#include "..\Engine\Camera.h"
#include "Hero_Anims.h"
#include "Score.h"
#include "../Engine/Collision.h"

void Hero::UpdateXVelocity(double dt)
{
	const math::vec2 stop{ 0,0 };
	if (moveRightKey.IsKeyDown() == true)
	{
		if (GetVelocity().x < x_max_speed.x)
		{
			UpdateVelocity(x_accel * dt);
		}
	}
	else if (moveLeftKey.IsKeyDown() == true)
	{
		if (GetVelocity().x > -x_max_speed.x)
		{
			UpdateVelocity(-x_accel * dt);
		}
	}
	else if (moveRightKey.IsKeyDown() == false && moveLeftKey.IsKeyDown() == false)
	{
		if (-GetVelocity().x > stop.x)
		{
			UpdateVelocity(x_drag * dt);
			if (GetVelocity().x > stop.x)
			{
				SetVelocity({0, GetVelocity().y});
			}
		}
		else if (-GetVelocity().x < -stop.x)
		{
			UpdateVelocity(-x_drag * dt);
			if (GetVelocity().x < stop.x)
			{
				SetVelocity({ 0, GetVelocity().y });
			}
		}
	}
}


void Hero::State_Idle::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Idle_Anim));
	if(hero->standingOnObject == nullptr)
	{
		Engine::GetLogger().LogError("Error: Cannot read hero idle on where");
	}
}

void Hero::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
}

void Hero::State_Idle::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if(hero->moveLeftKey.IsKeyDown() == true || hero->moveRightKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateRunning);
	}
	else if(hero->jumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
}

void Hero::State_Running::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Run_Anim));
	if (hero->moveLeftKey.IsKeyDown() == true)
	{
		hero->SetScale({ -1.0, 1.0 });
	}
	else if (hero->moveRightKey.IsKeyDown() == true)
	{
		hero->SetScale({ 1.0, 1.0 });
	}
	if (hero->standingOnObject == nullptr)
	{
		Engine::GetLogger().LogError("Error: Cannot read hero running on where");
	}
}

void Hero::State_Running::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateXVelocity(dt);
}

void Hero::State_Running::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->standingOnObject != nullptr && hero->standingOnObject->DoesCollideWith(hero->GetPosition()) == false)
	{
		hero->ChangeState(&hero->stateFalling);
		hero->standingOnObject = nullptr;
	}
	else if (hero->GetVelocity().x == 0)
	{
		hero->ChangeState(&hero->stateIdle);
	}
	else if(hero->jumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
	else if((hero->moveLeftKey.IsKeyDown() == true && hero->GetVelocity().x > 0) || (hero->moveRightKey.IsKeyDown() == true && hero->GetVelocity().x < 0))
	{
		hero->ChangeState(&hero->stateSkidding);
	}

}

void Hero::State_Skidding::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Skid_Anim));
}

void Hero::State_Skidding::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	const math::vec2 skidding = x_drag * 2;
	if (hero->GetVelocity().x > 0)
	{
		hero->UpdateVelocity(-skidding * dt);
	} else if(hero->GetVelocity().x < 0)
	{
		hero->UpdateVelocity(skidding * dt);
	}
}

void Hero::State_Skidding::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if ((hero->moveLeftKey.IsKeyDown() == true && hero->GetVelocity().x <= 0) || (hero->moveRightKey.IsKeyDown() == true && hero->GetVelocity().x >= 0) || (hero->moveLeftKey.IsKeyDown() == false && hero->moveRightKey.IsKeyDown() == false))
	{
		hero->ChangeState(&hero->stateRunning);
	}
	else if (hero->jumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
}

void Hero::State_Jumping::Enter(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	hero->standingOnObject = nullptr;
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Jump_Anim));
	hero->SetVelocity({hero->GetVelocity().x, Hero::jump_accel.y});   //Set the velocity.y
}
void Hero::State_Jumping::Update(GameObject* object, double dt) {
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateVelocity({ 0,-Engine::GetGSComponent<Gravity>()->GetValue() * dt });  //Apply Gravity
	hero->UpdateXVelocity(dt);  //Change X Velocity stuff
}
void Hero::State_Jumping::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->jumpKey.IsKeyDown() == false) {  //Jump Key not pressed
		hero->SetVelocity({hero->GetVelocity().x, 0});
	}
	if (hero->GetVelocity().y <= 0) {
		hero->ChangeState(&hero->stateFalling);
	}
}

void Hero::State_Falling::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Fall_Anim));
}

void Hero::State_Falling::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateVelocity({ 0,-Engine::GetGSComponent<Gravity>()->GetValue() * dt });
	hero->UpdateXVelocity(dt);
}

void Hero::State_Falling::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if(hero->GetPosition().y <= -300)
	{
		hero->isDead = true;
	}
	if (hero->standingOnObject != nullptr)
	{
		hero->SetVelocity({ hero->GetVelocity().x, 0 });
		if(hero->GetVelocity().x > 0)
		{
			if (hero->moveLeftKey.IsKeyDown() == true)
			{
				hero->ChangeState(&hero->stateSkidding);
			}
			else
			{
				hero->ChangeState(&hero->stateRunning);
			}
		}
		else if (hero->GetVelocity().x < 0)
		{
			if (hero->moveRightKey.IsKeyDown() == true)
			{
				hero->ChangeState(&hero->stateSkidding);
			}
			else
			{
				hero->ChangeState(&hero->stateRunning);
			}
		}
		else
		{
			hero->ChangeState(&hero->stateIdle);
		}
	} 
}

Hero::Hero(math::vec2 startPos) : GameObject(startPos), moveLeftKey(CS230::InputKey::Keyboard::Left), moveRightKey(CS230::InputKey::Keyboard::Right), jumpKey(CS230::InputKey::Keyboard::Up), hurtTimer(0), drawHero(true), isDead(false), standingOnObject(nullptr)
{
	AddGOComponent(new CS230::Sprite("assets/Hero.spt", this));
	currState = &stateIdle;
	currState->Enter(this);
	for(GameObject* standingObj : Engine::GetGSComponent<CS230::GameObjectManager>()->Objects())
	{
		if(standingObj->GetObjectType() == GameObjectType::Floor && DoesCollideWith(standingObj) == true)
		{
			standingOnObject = standingObj;
			SetPosition({ startPos.x, standingObj->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Top() });
		}
	}
}

void Hero::Update(double dt)
{
	if(hurtTimer > 0)
	{
		hurtTimer -= dt;
		drawHero = !drawHero;
	}
	else
	{
		drawHero = true;
	}
	GameObject::Update(dt);
	const double collisionOffset = GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect().Size().x / 2;
	const double screenPositionX = GetPosition().x - Engine::GetGSComponent<CS230::Camera>()->GetPosition().x;
	if (screenPositionX - collisionOffset <= 0)
	{
		SetVelocity({0, GetVelocity().y});
		SetPosition({ collisionOffset, GetPosition().y });
	}
	else if (screenPositionX + collisionOffset >= Engine::GetWindow().GetSize().x)
	{
		SetVelocity({ 0, GetVelocity().y });
		SetPosition({ Engine::GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x - collisionOffset, GetPosition().y });
	}
}

math::vec2 Hero::GetPosition()
{
	return GameObject::GetPosition();
}

bool Hero::CanCollideWith(GameObjectType objectBType)
{
	return objectBType == GameObjectType::Particle ? false : true;
}

void Hero::Draw(math::TransformMatrix displayMatrix)
{
	if(drawHero == true)
	{
		GameObject::Draw(displayMatrix);
	}
}

void Hero::ResolveCollision(GameObject* objectB)
{
	math::rect2 collideRect = objectB->GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
	math::rect2 heroRect = GetGOComponent<CS230::RectCollision>()->GetWorldCoorRect();
	switch (objectB->GetObjectType())
	{
	case GameObjectType::Ball:
		if (heroRect.Left() < collideRect.Right() || heroRect.Right() > collideRect.Left())
		{
			if (currState == &stateFalling && heroRect.Bottom() > collideRect.Center().y)
			{
				SetVelocity({ GetVelocity().x, jump_accel.y });
			}
			else
			{
				if (heroRect.Center().x < collideRect.Center().x)
				{
					UpdatePosition({ -(heroRect.Right() - collideRect.Left()), 0 });
				}
				else
				{
					UpdatePosition({ -(heroRect.Left() - collideRect.Right()), 0 });
				}
				hurtTimer = hurtTime;
				SetVelocity(-(GetVelocity().x / abs(GetVelocity().x)) * x_max_speed / 2 + jump_accel / 4);
			}
		}
		break;
	case GameObjectType::Bunny:
		if (heroRect.Left() < collideRect.Right() || heroRect.Right() > collideRect.Left())
		{
			if (currState == &stateSkidding)
			{
				objectB->ResolveCollision(this);
				if (heroRect.Center().x < collideRect.Center().x)
				{
					UpdatePosition({ -(heroRect.Right() - collideRect.Left()), 0 });
					Engine::GetGSComponent<SmokeEmitter>()->Emit(1, math::vec2{ (heroRect.Right() + collideRect.Left()) / 2., heroRect.Bottom() }, { 0,0 }, { 0,0 }, 0);
				}
				else
				{
					UpdatePosition({ -(heroRect.Left() - collideRect.Right()), 0 });
					Engine::GetGSComponent<SmokeEmitter>()->Emit(1, math::vec2{ (heroRect.Left()+ collideRect.Right()) / 2., heroRect.Bottom() }, { 0,0 }, { 0,0 }, 0);
				}
			}
			else if(currState == &stateFalling && heroRect.Bottom() > collideRect.Center().y)
			{
				SetVelocity({ GetVelocity().x, jump_accel.y / 2 });
				objectB->ResolveCollision(this);
				Engine::GetGSComponent<SmokeEmitter>()->Emit(1, math::vec2{ heroRect.Center().x ,(heroRect.Bottom() + collideRect.Top()) / 2 }, { 0,0 }, { 0,0 }, 0);
			}
			else
			{
				if (heroRect.Center().x < collideRect.Center().x)
				{
					UpdatePosition({ -(heroRect.Right() - collideRect.Left()), 0 });
				}
				else
				{
					UpdatePosition({ -(heroRect.Left() - collideRect.Right()), 0 });
				}
				hurtTimer = hurtTime;
				SetVelocity(-(GetVelocity().x / abs(GetVelocity().x)) * x_max_speed / 2 + jump_accel / 4);
			}
		}
		break;
	case GameObjectType::TreeStump:
		[[fallthrough]];
	case GameObjectType::Floor:
		if (heroRect.Center().x < collideRect.Right() && heroRect.Center().x > collideRect.Left() && objectB->DoesCollideWith(GetPosition()))
		{
			if(GetVelocity().y < -jump_accel.y)
			{
				Engine::GetGSComponent<SmokeEmitter>()->Emit(1, math::vec2{ heroRect.Center().x , heroRect.Bottom() }, { 0,0 }, { 0,0 }, 0);
			}
			SetPosition({ GetPosition().x, collideRect.Top()});
			standingOnObject = objectB;
			currState->TestForExit(this);
		}
		else
		{
			if (heroRect.Center().x < collideRect.Center().x)
			{
				UpdatePosition({ -(heroRect.Right() - collideRect.Left()), 0 });
			}
			else
			{
				UpdatePosition({ -(heroRect.Left() - collideRect.Right()), 0 });
			}
			SetVelocity({ 0, GetVelocity().y });
		}
		break;
	case GameObjectType::Trigger:
		objectB->ResolveCollision(this);
		break;
	default: break;
	}
}
