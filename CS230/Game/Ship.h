/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.h
Project: CS230
Author: Daehyeon Kim
Creation date: 3/17/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "../Engine/TransformMatrix.h"
class Ship {
public:
    Ship(math::vec2 startPos);
    void Load();
    void Update(double dt);
    void Draw();

private:
    CS230::Sprite shipSprite;
    CS230::Sprite flameSpriteL;
    CS230::Sprite flameSpriteR;
    math::vec2 startPos;
    math::vec2 position;
    math::vec2 velocity;
    double rotation = 0;
    bool wasAccel = false;
	
    CS230::InputKey rotateCounterKey;
    CS230::InputKey rotateClockKey;
    CS230::InputKey accelerateKey;
    math::TransformMatrix objectMatrix;

    static constexpr math::ivec2 flameHotspot{ 8, 16 };
    static constexpr double accel = 400;
    static constexpr double drag = 1.0f;
    void TestForWrap();
};

