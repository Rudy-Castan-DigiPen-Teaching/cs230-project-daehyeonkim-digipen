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
#include "Gravity.h"
#include "Level1.h"
#include "..\Engine\Engine.h"
#include "..\Engine\Camera.h"
#include "Hero_Anims.h"
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
	} else if(hero->jumpKey.IsKeyDown() == true)
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
}

void Hero::State_Running::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateXVelocity(dt);
}

void Hero::State_Running::TestForExit(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	if (hero->GetVelocity().x == 0)
	{
		hero->ChangeState(&hero->stateIdle);
	}
	if(hero->jumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
	if((hero->moveLeftKey.IsKeyDown() == true && hero->GetVelocity().x > 0) || (hero->moveRightKey.IsKeyDown() == true && hero->GetVelocity().x < 0))
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
	if (hero->GetPosition().y <= Level1::floor)
	{
		hero->SetVelocity({ hero->GetVelocity().x, 0 });
		hero->SetPosition({hero->GetPosition().x,Level1::floor});
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

Hero::Hero(math::vec2 startPos) : GameObject(startPos), moveLeftKey(CS230::InputKey::Keyboard::Left), moveRightKey(CS230::InputKey::Keyboard::Right), jumpKey(CS230::InputKey::Keyboard::Up), hurtTimer(0), drawHero(true)
{
	AddGOComponent(new CS230::Sprite("assets/Hero.spt", this));
	currState = &stateIdle;
	currState->Enter(this);
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
	if (heroRect.Center().x < collideRect.Center().x)
	{
		UpdatePosition({ -(heroRect.Right() - collideRect.Left()), 0 });
	}
	else
	{
		UpdatePosition({ -(heroRect.Left() - collideRect.Right()), 0 });
	}
	switch (objectB->GetObjectType())
	{
	case GameObjectType::Ball:
	case GameObjectType::Bunny:
		hurtTimer = hurtTime;
		ChangeState(&stateFalling);
		SetVelocity(-(GetVelocity().x / abs(GetVelocity().x)) * x_max_speed / 2 + jump_accel / 4);
		break;
	case GameObjectType::TreeStump:
		SetVelocity({ 0, GetVelocity().y });
		break;
	default: break;
	}
}
