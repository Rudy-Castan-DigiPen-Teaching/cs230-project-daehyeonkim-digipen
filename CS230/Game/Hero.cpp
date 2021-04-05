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
#include "../Engine/TransformMatrix.h"
Hero::Hero(math::vec2 startPos, const CS230::Camera& camera) : startPos(startPos), camera(camera), moveLeftKey(CS230::InputKey::Keyboard::Left), moveRightKey(CS230::InputKey::Keyboard::Right), jumpKey(CS230::InputKey::Keyboard::Up)
{
}

void Hero::Load()
{
	sprite.Load("assets/Hero.png", { feetX, feetY });
	position = startPos;
	velocity = { 0, 0 };
	isJumping = false;
	isRising = false;
}

void Hero::Update(double dt)
{
	const math::vec2 stop{ 0,0 };
	const math::vec2 skidding = x_drag * 2;
	const double collisionOffset = sprite.GetTextureSize().x / 2;
	const double screenPositionX = position.x - camera.GetPosition().x;
	if (moveRightKey.IsKeyDown() == true)
	{
		if (velocity.x < -stop.x)
		{
			velocity += skidding * dt;
			Engine::GetLogger().LogDebug("+Skidding");
		}
		else
		{
			if (velocity.x >= x_max_speed.x)
			{
				Engine::GetLogger().LogDebug("+Max Velocity");
			} else
			{
				velocity += x_accel * dt;
				Engine::GetLogger().LogDebug("+Accelerating");
			}
		}
	}
	else if (moveLeftKey.IsKeyDown() == true)
	{
		if (velocity.x > stop.x)
		{
			velocity -= skidding * dt;
			Engine::GetLogger().LogDebug("-Skidding");
		}
		else
		{
			if (velocity.x <= -x_max_speed.x)
			{
				Engine::GetLogger().LogDebug("-Max Velocity");
			} else
			{
				velocity -= x_accel * dt;
				Engine::GetLogger().LogDebug("-Accelerating");
			}
		}
	} else if (moveRightKey.IsKeyDown() == false && moveLeftKey.IsKeyDown() == false)
	{
		const double drag = -(velocity.x / sqrt(velocity.x * velocity.x)) * x_drag.x;
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
	if (screenPositionX - collisionOffset < 0)
	{
		velocity.x = 0;
		position.x = collisionOffset;
	} else if(screenPositionX + collisionOffset > Engine::GetWindow().GetSize().x)
	{
		velocity.x = 0;
		position.x = camera.GetPosition().x + Engine::GetWindow().GetSize().x - collisionOffset;
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
	position += velocity * dt;
}

void Hero::Draw(math::TransformMatrix cameraMatrix)
{
	sprite.Draw(math::TranslateMatrix(position) * cameraMatrix);
}

math::vec2 Hero::GetPosition()
{
	return position;
}
