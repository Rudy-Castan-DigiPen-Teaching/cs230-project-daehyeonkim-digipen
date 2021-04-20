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
#include "..\Engine\GameObject.h"
namespace math { struct vec2; }

class Ball : public CS230::GameObject {
private:
    class State_Bounce : public State {
    public:
        void Enter(GameObject* object) override;
        void Update(GameObject* object, double dt) override;
        void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Bounce"; }
    };
    class State_Land : public State {
    public:
        void Enter(GameObject* object) override;
        void Update(GameObject* object, double dt) override;
        void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Land"; }
    };
    State_Bounce stateBounce;
    State_Land stateLand;


public:
    Ball(math::vec2 startPos);

private:
    static constexpr int ballCenterX = 44;
    static constexpr double bounceVelocity = 750.0;
};