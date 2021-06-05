/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ball.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/14/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"  //GetLogger
#include "../Engine/Sprite.h"
#include "../Engine/Collision.h"
#include "Ball.h"
#include "Gravity.h"
#include "Ball_Anims.h"
#include "../Engine/Input.h"

Ball::Ball(math::vec2 startPos) : GameObject(startPos) {
    AddGOComponent(new CS230::Sprite("assets/Ball.spt", this));
    currState = &stateLand;
    currState->Enter(this);
}

void Ball::State_Bounce::Enter(GameObject* object) {
    Ball* ball = static_cast<Ball*>(object);
    ball->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ball_Anim::None_Anim));
    ball->UpdateVelocity({ 0, Ball::bounceVelocity });
}
void Ball::State_Bounce::Update(GameObject* object, double dt) {
    Ball* ball = static_cast<Ball*>(object);
    ball->UpdateVelocity({ 0, -Engine::GetGSComponent<Gravity>()->GetValue() * dt });
}
void Ball::State_Bounce::TestForExit(GameObject*) {
}

void Ball::State_Land::Enter(GameObject* object) {
    Ball* ball = static_cast<Ball*>(object);
    ball->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ball_Anim::Squish_Anim));
}
void Ball::State_Land::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt) {}
void Ball::State_Land::TestForExit(GameObject* object) {
    Ball* ball = static_cast<Ball*>(object);
    if (ball->GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true) {
        ball->ChangeState(&ball->stateBounce);
    }
}

bool Ball::CanCollideWith(GameObjectType objectBType) {
    if (objectBType == GameObjectType::Floor) {
        return true;
    }
    return false;
}

void Ball::ResolveCollision(CS230::GameObject* collideWith) {
    if (collideWith->GetObjectType() == GameObjectType::Floor) {

        CS230::RectCollision* collideRect =
            static_cast<CS230::RectCollision*>(collideWith->GetGOComponent<CS230::RectCollision>());
        SetPosition({ GetPosition().x, collideRect->GetWorldCoorRect().Top() });
        SetVelocity({ GetVelocity().x, 0 });
        ChangeState(&stateLand);
    }
}