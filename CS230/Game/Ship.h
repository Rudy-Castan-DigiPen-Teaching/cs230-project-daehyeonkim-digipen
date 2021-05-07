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
#include "..\Engine\Input.h"
#include "../Engine/GameObject.h"
namespace math { struct vec2; }
class Ship : public CS230::GameObject {
public:
    Ship(math::vec2 startPos);
    void Update(double dt) override;
    void Draw(math::TransformMatrix cameraMatrix) override;

private:
    CS230::Sprite flameSpriteL;
    CS230::Sprite flameSpriteR;
    bool wasAccel;
	
    CS230::InputKey rotateCounterKey;
    CS230::InputKey rotateClockKey;
    CS230::InputKey accelerateKey;

    static constexpr math::vec2 accel{ 0, 400 };
    static constexpr double drag = 1.0f;
};

