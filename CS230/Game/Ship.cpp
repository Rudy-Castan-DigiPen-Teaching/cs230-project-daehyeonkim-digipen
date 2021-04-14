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


Ship::Ship(math::vec2 startPos) : startPos(startPos), rotateCounterKey(CS230::InputKey::Keyboard::A), rotateClockKey(CS230::InputKey::Keyboard::D), accelerateKey(CS230::InputKey::Keyboard::W)
{
}

void Ship::Load()
{
	shipSprite.Load("assets/Ship.png", { {50,41},{-15,41},{15,41} });
	flameSpriteL.Load("assets/flame.png", { math::ivec2{shipSprite.GetHotSpot(1)} + flameHotspot });
	flameSpriteR.Load("assets/flame.png", { math::ivec2{shipSprite.GetHotSpot(2)} + flameHotspot });
	position = startPos;
	velocity = { 0, 0 };
	rotation = 0;
	wasAccel = false;
}

void Ship::Update(double dt)
{
	constexpr double rotateSpeed = 3.14;
	if(rotateCounterKey.IsKeyDown() == true)
	{
		rotation += rotateSpeed * dt;
	}
	if (rotateClockKey.IsKeyDown() == true)
	{
		rotation -= rotateSpeed * dt;
	}
	if (accelerateKey.IsKeyDown() == true)
	{
		if(wasAccel == false)
		{
			Engine::GetLogger().LogDebug("Accelerating");
			wasAccel = true;
		}
		velocity += math::RotateMatrix(rotation) * math::vec2{ 0, accel * dt };
	} else
	{
		if(wasAccel == true)
		{
			Engine::GetLogger().LogDebug("Stopped Accelerating");
			wasAccel = false;
		}
	}
	velocity -= velocity * drag * dt;
	position += velocity * dt;
	TestForWrap();
	objectMatrix = math::TranslateMatrix(position) * math::RotateMatrix(rotation) * math::ScaleMatrix({ 0.75, 0.75 });
}

void Ship::Draw()
{
	flameSpriteL.Draw(objectMatrix);
	flameSpriteR.Draw(objectMatrix);
	shipSprite.Draw(objectMatrix);
}

void Ship::TestForWrap()
{
	const int x_limit = Engine::GetWindow().GetSize().x + shipSprite.GetTextureSize().x / 2;
	const int y_limit = Engine::GetWindow().GetSize().y + shipSprite.GetTextureSize().y / 2;
	if (position.x > x_limit)
	{
		position.x = -shipSprite.GetTextureSize().x / 2;
	}
	else if (position.x < -shipSprite.GetTextureSize().x / 2)
	{
		position.x = x_limit;
	}
	if (position.y > y_limit)
	{
		position.y = -shipSprite.GetTextureSize().y / 2;
	}
	else if (position.y < -shipSprite.GetTextureSize().y / 2)
	{
		position.y = y_limit;
	}
}
