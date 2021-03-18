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

Hero::Hero(math::vec2 startPos) :startPos(startPos), moveLeftKey(CS230::InputKey::Keyboard::Left), moveRightKey(CS230::InputKey::Keyboard::Right)
{
}

void Hero::Load()
{
	sprite.Load("assets/Hero.png", { feetX, feetY });
	position = startPos;
}

void Hero::Update()
{
	if(moveRightKey.IsKeyDown() == true)
	{
		position.x += 5;
	} else if (moveLeftKey.IsKeyDown() == true)
	{
		position.x -= 5;
	}
}

void Hero::Draw()
{
	sprite.Draw(position);
}
