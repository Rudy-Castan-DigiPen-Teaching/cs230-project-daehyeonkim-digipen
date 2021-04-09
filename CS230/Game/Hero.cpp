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

void Hero::UpdateXVelocity(double dt)
{
	const math::vec2 stop{ 0,0 };
	const math::vec2 skidding = x_drag * 2;
	if (moveRightKey.IsKeyDown() == true)
	{
		if (velocity.x <= x_max_speed.x)
		{
			velocity += x_accel * dt;
		}
	}
	else if (moveLeftKey.IsKeyDown() == true)
	{
		if (velocity.x >= -x_max_speed.x)
		{
			velocity -= x_accel * dt;
		}
	}
	else if (moveRightKey.IsKeyDown() == false && moveLeftKey.IsKeyDown() == false)
	{
		if (-velocity.x > stop.x)
		{
			velocity.x += x_drag.x * dt;
			if (velocity.x > stop.x)
			{
				velocity.x = 0;
			}
		}
		else if (-velocity.x < -stop.x)
		{
			velocity.x -= x_drag.x * dt;
			if (velocity.x < stop.x)
			{
				velocity.x = 0;
			}
		}
	}
}

void Hero::ChangeState(State* newState) {
	Engine::GetLogger().LogDebug("Leaving State: " + currState->GetName() + " Entering State: " + newState->GetName());
	currState = newState;
	currState->Enter(this);
}

void Hero::State_Idle::Enter([[maybe_unused]] Hero* hero)
{
}

void Hero::State_Idle::Update([[maybe_unused]] Hero* hero, [[maybe_unused]] double dt)
{
}

void Hero::State_Idle::TestForExit(Hero* hero)
{
	if(hero->moveLeftKey.IsKeyDown() == true || hero->moveRightKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateRunning);
	} else if(hero->jumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
}

void Hero::State_Running::Enter(Hero* hero)
{
	if (hero->moveLeftKey.IsKeyDown() == true)
	{
		hero->isFlipped = true;
	}
	else if (hero->moveRightKey.IsKeyDown() == true)
	{
		hero->isFlipped = false;
	}
}

void Hero::State_Running::Update(Hero* hero, double dt)
{
	hero->UpdateXVelocity(dt);
}

void Hero::State_Running::TestForExit(Hero* hero)
{
	if (hero->velocity.x == 0)
	{
		hero->ChangeState(&hero->stateIdle);
	}
	if(hero->jumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
	if((hero->moveLeftKey.IsKeyDown() == true && hero->velocity.x > 0) || (hero->moveRightKey.IsKeyDown() == true && hero->velocity.x < 0))
	{
		hero->ChangeState(&hero->stateSkidding);
	}
}

void Hero::State_Skidding::Enter([[maybe_unused]] Hero* hero)
{
	
}

void Hero::State_Skidding::Update(Hero* hero, double dt)
{
	const math::vec2 skidding = x_drag * 2;
	if (hero->moveLeftKey.IsKeyDown() == true && hero->velocity.x > 0)
	{
		hero->velocity -= skidding * dt;
	} else if(hero->moveRightKey.IsKeyDown() == true && hero->velocity.x < 0)
	{
		hero->velocity += skidding * dt;
	}
}

void Hero::State_Skidding::TestForExit(Hero* hero)
{
	if ((hero->moveLeftKey.IsKeyDown() == true && hero->velocity.x <= 0) || (hero->moveRightKey.IsKeyDown() == true && hero->velocity.x >= 0) || (hero->moveLeftKey.IsKeyDown() == false && hero->moveRightKey.IsKeyDown() == false))
	{
		hero->ChangeState(&hero->stateRunning);
	}
	else if (hero->jumpKey.IsKeyDown() == true)
	{
		hero->ChangeState(&hero->stateJumping);
	}
}

void Hero::State_Jumping::Enter(Hero* hero) {
	hero->velocity.y = Hero::jump_accel.y;   //Set the velocity.y
}
void Hero::State_Jumping::Update(Hero* hero, double dt) {
	hero->velocity.y -= Level1::gravity.y * dt;  //Apply Gravity
	hero->UpdateXVelocity(dt);  //Change X Velocity stuff
}
void Hero::State_Jumping::TestForExit(Hero* hero) {
	if (hero->jumpKey.IsKeyDown() == false) {  //Jump Key not pressed
		hero->velocity.y = 0;
	}
	if (hero->velocity.y <= 0) {
		hero->ChangeState(&hero->stateFalling);
	}
}

void Hero::State_Falling::Enter([[maybe_unused]] Hero* hero)
{
}

void Hero::State_Falling::Update(Hero* hero, double dt)
{
	hero->velocity.y -= Level1::gravity.y * dt;
	hero->UpdateXVelocity(dt);
}

void Hero::State_Falling::TestForExit(Hero* hero)
{
	if(hero->position.y <= Level1::floor)
	{
		hero->velocity.y = 0;
		hero->position.y = Level1::floor;
		if (hero->moveLeftKey.IsKeyDown() == true)
		{
			if(hero->velocity.x > 0)
			{
				hero->ChangeState(&hero->stateSkidding);
			} else
			{
				hero->ChangeState(&hero->stateRunning);
			}
		} else if (hero->moveRightKey.IsKeyDown() == true)
		{
			if(hero->velocity.x < 0)
			{
				hero->ChangeState(&hero->stateSkidding);
			} else
			{
				hero->ChangeState(&hero->stateRunning);
			}
		} else
		{
			hero->ChangeState(&hero->stateIdle);
		}
	}
}

Hero::Hero(math::vec2 startPos, const CS230::Camera& camera) : startPos(startPos), camera(camera), moveLeftKey(CS230::InputKey::Keyboard::Left), moveRightKey(CS230::InputKey::Keyboard::Right), jumpKey(CS230::InputKey::Keyboard::Up)
{
}

void Hero::Load()
{
	sprite.Load("assets/Hero.png", { {feetX, feetY} });
	currState = &stateIdle;
	currState->Enter(this);
	position = startPos;
	velocity = { 0, 0 };
	isJumping = false;
	isRising = false;
}

void Hero::Update(double dt)
{
	currState->Update(this, dt);
	position += velocity * dt;
	currState->TestForExit(this);
	const double collisionOffset = sprite.GetTextureSize().x / 2;
	const double screenPositionX = position.x - camera.GetPosition().x;
	if (screenPositionX - collisionOffset < 0)
	{
		velocity.x = 0;
		position.x = collisionOffset;
	}
	else if (screenPositionX + collisionOffset > Engine::GetWindow().GetSize().x)
	{
		velocity.x = 0;
		position.x = camera.GetPosition().x + Engine::GetWindow().GetSize().x - collisionOffset;
	}
	
	objectMatrix = math::TranslateMatrix(position);
	if (isFlipped == true) {
		objectMatrix *= math::ScaleMatrix{ {-1.0, 1.0} };
	}
}

void Hero::Draw(math::TransformMatrix cameraMatrix)
{
	sprite.Draw(cameraMatrix * objectMatrix);
}

math::vec2 Hero::GetPosition()
{
	return position;
}
