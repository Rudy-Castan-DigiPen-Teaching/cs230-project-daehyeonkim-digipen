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
#include "Ship.h"
#include "..\Engine\Engine.h"

Hero::Hero(math::vec2 startPos) :startPos(startPos), moveLeftKey(CS230::InputKey::Keyboard::Left), moveRightKey(CS230::InputKey::Keyboard::Right), jumpKey(CS230::InputKey::Keyboard::Up)
{
}

void Hero::Load()
{
	sprite.Load("assets/Hero.png", { feetX, feetY });
	position = startPos;
	isJumping = false;
	isRising = false;
}

void Hero::Update(double dt)
{
	const math::vec2 stop{ 0,0 };
	const math::vec2 skidding = x_drag * 2;
	position += velocity * dt;
	if (moveRightKey.IsKeyDown() == true && velocity.x <= x_max_speed.x)
	{
		if (velocity.x >= x_max_speed.x)
		{
			Engine::GetLogger().LogDebug("+Max Velocity");
		}
		else if (velocity.x < -stop.x)
		{
			velocity += skidding * dt;
			Engine::GetLogger().LogDebug("+Skidding");
		}
		else
		{
			velocity += x_accel * dt;
			Engine::GetLogger().LogDebug("+Accelerating");
		}
	}
	else if (moveLeftKey.IsKeyDown() == true && velocity.x >= -x_max_speed.x)
	{
		if (velocity.x <= -x_max_speed.x)
		{
			Engine::GetLogger().LogDebug("-Max Velocity");
		}
		else if (velocity.x > stop.x)
		{
			velocity -= skidding * dt;
			Engine::GetLogger().LogDebug("-Skidding");
		}
		else
		{
			velocity -= x_accel * dt;
			Engine::GetLogger().LogDebug("-Accelerating");
		}
	} else if (moveRightKey.IsKeyDown() == false && moveLeftKey.IsKeyDown() == false)
	{
		const double drag = -velocity.Normalize().x * x_drag.x;
		if (drag > stop.x)
		{
			velocity.x += drag * dt;
			Engine::GetLogger().LogDebug("+Dragging");
			if (velocity.x > stop.x)
			{
				Engine::GetLogger().LogDebug("Stopped");
				velocity.x = 0;
			}
		}
		else if (drag < -stop.x)
		{
			velocity.x += drag * dt;
			Engine::GetLogger().LogDebug("-Dragging");
			if (velocity.x < stop.x)
			{
				Engine::GetLogger().LogDebug("Stopped");
				velocity.x = 0;
			}
		}
	}
	if(jumpKey.IsKeyDown() == true && isJumping == false)
	{
		isJumping = true;
		isRising = true;
		velocity += jump_accel;
		Engine::GetLogger().LogDebug("Starting Jump - YPos" + std::to_string(position.y));
	}
	if(isJumping == true)
	{
		velocity -= Level1::gravity * dt;
	}
	if(isRising == true)
	{
		if(velocity.y <= 0)
		{
			isRising = false;
			Engine::GetLogger().LogDebug("Top of jump - YPos" + std::to_string(position.y));
		}
		if(jumpKey.IsKeyReleased() == true)
		{
			velocity.y = 0;
			isRising = false;
			Engine::GetLogger().LogDebug("Top of jump(Early) - YPos" + std::to_string(position.y));
		}
	}
	if(position.y < Level1::floor)
	{
		velocity.y = 0;
		position.y = Level1::floor;
		isJumping = false;
		Engine::GetLogger().LogDebug("Ending Jump - YPos" + std::to_string(position.y));
	}
}

void Hero::Draw()
{
	sprite.Draw(position);
}
