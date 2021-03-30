/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 3/17/2021
-----------------------------------------------------------------*/
#include "Ship.h"
#include "..\Engine\Engine.h"

Ship::Ship(math::vec2 startPos) : startPos(startPos), moveLeftKey(CS230::InputKey::Keyboard::A), moveRightKey(CS230::InputKey::Keyboard::D), moveUpKey(CS230::InputKey::Keyboard::W), moveDownKey(CS230::InputKey::Keyboard::S)
{
}

void Ship::Load()
{
	sprite.Load("assets/Ship.png");
	position = startPos;
}

void Ship::Update(double dt)
{
	if(moveLeftKey.IsKeyDown() == true)
	{
		velocity.x -= accel * dt;
	}
	if (moveRightKey.IsKeyDown() == true)
	{
		velocity.x += accel * dt;
	}
	if (moveUpKey.IsKeyDown() == true)
	{
		velocity.y += accel * dt;
	}
	if (moveDownKey.IsKeyDown() == true)
	{
		velocity.y -= accel * dt;
	}
	velocity -= velocity * drag * dt;
	Engine::GetLogger().LogDebug("Velocity = [" + std::to_string(velocity.x) + "],[" + std::to_string(velocity.y) + "]");
	position += velocity * dt;
	TestForWrap();
}

void Ship::Draw()
{
	sprite.Draw(position);
}

void Ship::TestForWrap()
{
	const int x_limit = Engine::GetWindow().GetSize().x + sprite.GetTextureSize().x / 2;
	const int y_limit = Engine::GetWindow().GetSize().y + sprite.GetTextureSize().y / 2;
	if(position.x > x_limit)
	{
		position.x = -sprite.GetTextureSize().x / 2;
	}
	else if(position.x < -sprite.GetTextureSize().x / 2)
	{
		position.x = x_limit;
	}
	if (position.y > y_limit)
	{
		position.y = -sprite.GetTextureSize().y / 2;
	}
	else if (position.y < -sprite.GetTextureSize().y / 2)
	{
		position.y = y_limit;
	}
}
