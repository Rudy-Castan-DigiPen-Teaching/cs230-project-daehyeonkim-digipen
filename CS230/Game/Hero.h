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
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "../Engine/TransformMatrix.h"
namespace CS230 {
    class Camera;
}
class Hero {
public:
    Hero(math::vec2 startPos, const CS230::Camera& camera);
    void Load();
    void Update(double dt);
    void Draw(math::TransformMatrix cameraMatrix);
    math::vec2 GetPosition();
private:
    const CS230::Camera& camera;
    CS230::Sprite sprite;
    math::vec2 startPos;
    math::vec2 position;
    math::vec2 velocity;
    math::TransformMatrix objectMatrix;
    CS230::InputKey moveLeftKey;
    CS230::InputKey moveRightKey;
    CS230::InputKey jumpKey;

    static constexpr int feetX = 56, feetY = 14;
    static constexpr math::vec2 x_drag{600, 0};
    static constexpr math::vec2 x_accel{ 300, 0 };
    static constexpr math::vec2 x_max_speed{ 600, 0 };
    static constexpr math::vec2 jump_accel{ 0, 1000 };

    bool isJumping = false;
    bool isRising = false;
};

