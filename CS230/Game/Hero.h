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
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"		//Input::InputKey
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"

class Hero : public CS230::GameObject {
public:
    Hero(math::vec2 startPos);
    void Update(double dt);
    void Draw(math::TransformMatrix displayMatrix);
    GameObjectType GetObjectType() override { return GameObjectType::Hero; }
    std::string GetObjectTypeName() override { return "Hero"; }
    bool CanCollideWith(GameObjectType objectBType) override;
    void ResolveCollision(GameObject* objectB) override;

    bool IsDead() { return isDead; }
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

    void UpdateXVelocity(double dt);

	static constexpr double jumpVelocity = 950;
	static constexpr double xAccel = 500;
	static constexpr double xDrag = 750;
	static constexpr double maxXVelocity = 750;
    static constexpr double hurtTime = 2;

    double hurtTimer;
    bool drawHero;
    bool isDead;
    GameObject* standingOnObject;

	CS230::InputKey jumpKey;
	CS230::InputKey moveLeftKey;
	CS230::InputKey moveRightKey;
};