/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.h
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once
#include "GameObjectTypes.h"
#include "..\Engine\Input.h"
#include "..\Engine\GameObject.h"
namespace math { struct vec2; }

class Hero : public CS230::GameObject {
private:
    class State_Idle : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };
    class State_Running : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Running"; }
    };
    class State_Skidding : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Skidding"; }
    };
    class State_Jumping : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };
    class State_Falling : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void TestForExit(GameObject* object) override;
        std::string GetName() override { return "Falling"; }
    };
    State_Idle stateIdle;
    State_Running stateRunning;
    State_Skidding stateSkidding;
    State_Jumping stateJumping;
    State_Falling stateFalling;

    void UpdateXVelocity(double dt);     //Change X velocity stuff

public:
    Hero(math::vec2 startPos);
    //void Load();
    void Update(double dt) override;
    math::vec2 GetPosition();
    GameObjectType GetObjectType() override { return GameObjectType::Hero; }
    std::string GetObjectTypeName() override { return "Hero"; }
    bool CanCollideWith(GameObjectType) override { return true; }
    void Draw(math::TransformMatrix displayMatrix);
    void ResolveCollision(GameObject* objectB) override;
private:
    CS230::InputKey moveLeftKey;
    CS230::InputKey moveRightKey;
    CS230::InputKey jumpKey;
    static constexpr double hurtTime = 2;
	static constexpr math::vec2 x_drag{800, 0};
    static constexpr math::vec2 x_accel{ 400, 0 };
    static constexpr math::vec2 x_max_speed{ 800, 0 };
    static constexpr math::vec2 jump_accel{ 0, 1000 };

    double hurtTimer;
    bool drawHero;
};

