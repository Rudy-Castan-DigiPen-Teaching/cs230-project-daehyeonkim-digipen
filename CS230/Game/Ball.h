/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ball.h
Project: CS230
Author: Kevin Wright
Creation date: 2/14/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Vec2.h"
#include "../Engine/TransformMatrix.h"
class Ball {
private:
    class State {
    public:
        virtual void Enter(Ball* ball) = 0;
        virtual void Update(Ball* ball, double dt) = 0;
        virtual void TestForExit(Ball* ball) = 0;
        virtual std::string GetName() = 0;
    };
    class State_Bounce : public State {
    public:
        virtual void Enter(Ball* ball) override;
        virtual void Update(Ball* ball, double dt) override;
        virtual void TestForExit(Ball* ball) override;
        std::string GetName() override { return "Bounce"; }
    };
    class State_Land : public State {
    public:
        virtual void Enter(Ball* ball) override;
        virtual void Update(Ball* ball, double dt) override;
        virtual void TestForExit(Ball* ball) override;
        std::string GetName() override { return "Land"; }
    };
    State_Bounce stateBounce;
    State_Land stateLand;
    State* currState;

    void ChangeState(State* newState);
public:
    Ball(math::vec2 startPos);
    void Load();
    void Update(double dt);
    void Draw(math::TransformMatrix cameraMatrix);

private:
    CS230::Sprite sprite;
    math::vec2 initPosition;
    math::vec2 position;
    math::vec2 velocity;
    math::TransformMatrix objectMatrix;
    static constexpr int ballCenterX = 44;
    static constexpr double bounceVelocity = 750 ;
};