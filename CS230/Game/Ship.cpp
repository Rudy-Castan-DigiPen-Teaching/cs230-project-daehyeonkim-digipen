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

Ship::Ship(math::vec2 startPos) : startPos(startPos), moveLeftKey(CS230::InputKey::Keyboard::A), moveRightKey(CS230::InputKey::Keyboard::D), moveUpKey(CS230::InputKey::Keyboard::W), moveDownKey(CS230::InputKey::Keyboard::S)
{
}

void Ship::Load()
{
	sprite.Load("assets/Ship.png");
	position = startPos;
}

void Ship::Update()
{
	if(moveLeftKey.IsKeyDown() == true)
	{
		position.x -= speed;
	}
	if (moveRightKey.IsKeyDown() == true)
	{
		position.x += speed;
	}
	if (moveUpKey.IsKeyDown() == true)
	{
		position.y += speed;
	}
	if (moveDownKey.IsKeyDown() == true)
	{
		position.y -= speed;
	}
}

void Ship::Draw()
{
	sprite.Draw(position);
}
