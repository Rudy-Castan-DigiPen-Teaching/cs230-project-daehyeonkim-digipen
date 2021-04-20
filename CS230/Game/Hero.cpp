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
#include "Level1.h"
#include "..\Engine\Engine.h"
#include "..\Engine\Camera.h"
#include "Hero_Anims.h"

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
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Idle_Anim));
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
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Run_Anim));
	if (hero->moveLeftKey.IsKeyDown() == true)
	{
		hero->isFlipped = true;
	}
	else if (hero->moveRightKey.IsKeyDown() == true)
	{
		hero->isFlipped = false;
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
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Skid_Anim));
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
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Jump_Anim));
	hero->SetVelocity({hero->GetVelocity().x, Hero::jump_accel.y});   //Set the velocity.y
}
void Hero::State_Jumping::Update(GameObject* object, double dt) {
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateVelocity(-Level1::gravity * dt);  //Apply Gravity
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
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Fall_Anim));
}

void Hero::State_Falling::Update(GameObject* object, double dt)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateVelocity(-Level1::gravity * dt);
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

Hero::Hero(math::vec2 startPos, const CS230::Camera& camera) : GameObject(startPos), camera(camera), moveLeftKey(CS230::InputKey::Keyboard::Left), moveRightKey(CS230::InputKey::Keyboard::Right), jumpKey(CS230::InputKey::Keyboard::Up)
{
	sprite.Load("assets/Hero.spt");
	currState = &stateIdle;
	currState->Enter(this);
}

void Hero::Update(double dt)
{
	GameObject::Update(dt);
	const double collisionOffset = sprite.GetFrameSize().x / 2;
	const double screenPositionX = GetPosition().x - camera.GetPosition().x;
	if (screenPositionX - collisionOffset < 0)
	{
		SetVelocity({0, GetVelocity().y});
		SetPosition({ collisionOffset, GetPosition().y });
	}
	else if (screenPositionX + collisionOffset > Engine::GetWindow().GetSize().x)
	{
		SetVelocity({ 0, GetVelocity().y });
		SetPosition({ camera.GetPosition().x + Engine::GetWindow().GetSize().x - collisionOffset, GetPosition().y });
	}
	
	if (isFlipped == true) {
		SetScale( {-1.0, 1.0} );
	} else
	{
		SetScale({ 1.0, 1.0 });
	}
}

math::vec2 Hero::GetPosition()
{
	return GameObject::GetPosition();
}
