/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ball.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 3/26/2021
-----------------------------------------------------------------*/
#include "Ball.h"
#include "Level1.h"
Ball::Ball(math::vec2 startPos) : initPosition(startPos)
{
}

void Ball::Load()
{
	sprite.Load("assets/Ball.png");
	sprite.Load("assets/Ball.png", { sprite.GetTextureSize().x / 2, 0 });
	position = initPosition;
	velocity = { 0, bounceVelocity };
}

void Ball::Update(double dt)
{
	position += velocity * dt;
	velocity -= Level1::gravity * dt;
	if (position.y < Level1::floor)
	{
		velocity.y = bounceVelocity;
		position.y = Level1::floor;
	}
}

void Ball::Draw()
{
	sprite.Draw(position);
}
