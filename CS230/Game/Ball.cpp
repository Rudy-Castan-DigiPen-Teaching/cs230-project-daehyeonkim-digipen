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
#include "Gravity.h"

void Ball::State_Bounce::Enter(GameObject* object)
{
	Ball* ball = static_cast<Ball*>(object);
	ball->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ball_Anim::None_Anim));
	ball->SetVelocity({ball->GetVelocity().x, bounceVelocity});
}

void Ball::State_Bounce::Update(GameObject* object, double dt)
{
	Ball* ball = static_cast<Ball*>(object);
	ball->UpdateVelocity({ 0, -Engine::GetGSComponent<Gravity>()->GetValue() * dt });
}

void Ball::State_Bounce::TestForExit(GameObject* object) {
	Ball* ball = static_cast<Ball*>(object);
	if (ball->GetPosition().y < Level1::floor) {
		ball->SetPosition({ ball->GetPosition().x, Level1::floor });
		ball->SetVelocity({ 0, 0 });
		ball->ChangeState(&ball->stateLand);
	}
}

void Ball::State_Land::Enter(GameObject* object)
{
	Ball* ball = static_cast<Ball*>(object);
	ball->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ball_Anim::Squish_Anim));
	ball->SetVelocity({0,0});
	ball->SetPosition({ ball->GetPosition().x, Level1::floor });
}

void Ball::State_Land::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
}

void Ball::State_Land::TestForExit(GameObject* object)
{
	Ball* ball = static_cast<Ball*>(object);
	if (ball->GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true) {
		ball->ChangeState(&ball->stateBounce);
	}
}

Ball::Ball(math::vec2 startPos) : GameObject(startPos) {
	AddGOComponent(new CS230::Sprite("assets/Ball.spt", this));
	currState = &stateBounce;
	currState->Enter(this);
}