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
#include "..\Engine\Engine.h"
#include "Ball_Anims.h"
void Ball::ChangeState(State* newState) {
	Engine::GetLogger().LogDebug("Leaving State: " + currState->GetName() + " Entering State: " + newState->GetName());
	currState = newState;
	currState->Enter(this);
}
void Ball::State_Bounce::Enter(Ball* ball)
{
	ball->sprite.PlayAnimation(static_cast<int>(Ball_Anim::None_Anim));
	ball->velocity.y = bounceVelocity;
}

void Ball::State_Bounce::Update(Ball* ball, double dt)
{
	ball->velocity -= Level1::gravity * dt;
}

void Ball::State_Bounce::TestForExit(Ball* ball)
{
	if (ball->position.y <= Level1::floor)
	{
		ball->ChangeState(&ball->stateLand);
	}
}

void Ball::State_Land::Enter(Ball* ball)
{
	ball->sprite.PlayAnimation(static_cast<int>(Ball_Anim::Squish_Anim));
	ball->velocity.y = 0;
	ball->position.y = Level1::floor;
}

void Ball::State_Land::Update([[maybe_unused]] Ball* ball, [[maybe_unused]] double dt)
{
}

void Ball::State_Land::TestForExit(Ball* ball)
{
	if(ball->sprite.IsAnimationDone() == true)
	{
		ball->ChangeState(&ball->stateBounce);
	}
}

Ball::Ball(math::vec2 startPos) : initPosition(startPos)
{
}

void Ball::Load()
{
	sprite.Load("assets/Ball.spt");
	currState = &stateLand;
	currState->Enter(this);
	position = initPosition;
	velocity = { 0, 0 };
}

void Ball::Update(double dt)
{
	sprite.Update(dt);
	currState->Update(this, dt);
	position += velocity * dt;
	currState->TestForExit(this);
	objectMatrix = math::TranslateMatrix(position);
}

void Ball::Draw(math::TransformMatrix cameraMatrix)
{
	sprite.Draw(cameraMatrix * objectMatrix);
}
