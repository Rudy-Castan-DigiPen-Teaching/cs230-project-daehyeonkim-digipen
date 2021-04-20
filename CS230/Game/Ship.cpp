/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 3/17/2021
-----------------------------------------------------------------*/
#include "Ship.h"
#include "..\Engine\Engine.h"
#include "Flame_Anims.h"


Ship::Ship(math::vec2 startPos) : GameObject(startPos), wasAccel(false), rotateCounterKey(CS230::InputKey::Keyboard::A), rotateClockKey(CS230::InputKey::Keyboard::D), accelerateKey(CS230::InputKey::Keyboard::W)
{
	sprite.Load("assets/Ship.spt");
	flameSpriteL.Load("assets/Flame.spt");
	flameSpriteR.Load("assets/Flame.spt");
}

void Ship::Update(double dt)
{
	constexpr double rotateSpeed = 3.14;
	if(rotateCounterKey.IsKeyDown() == true)
	{
		UpdateRotation(rotateSpeed * dt);
	}
	if (rotateClockKey.IsKeyDown() == true)
	{
		UpdateRotation(-rotateSpeed * dt);
	}
	if (accelerateKey.IsKeyDown() == true)
	{
		if(wasAccel == false)
		{
			flameSpriteL.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
			flameSpriteR.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
			wasAccel = true;
		}
		UpdateVelocity(math::RotateMatrix(GetRotation()) * accel * dt);
	} else
	{
		if(wasAccel == true)
		{
			flameSpriteL.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
			flameSpriteR.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
			wasAccel = false;
		}
	}
	UpdateVelocity(-GetVelocity()*drag*dt);
	UpdatePosition(GetVelocity() * dt);
	SetScale({ 0.75, 0.75 });
	TestForWrap();
	flameSpriteL.Update(dt);
	flameSpriteR.Update(dt);
	sprite.Update(dt);
}

void Ship::Draw([[maybe_unused]] math::TransformMatrix cameraMatrix)
{
	flameSpriteL.Draw(GetMatrix() * math::TranslateMatrix(-sprite.GetHotSpot(1)));
	flameSpriteR.Draw(GetMatrix() * math::TranslateMatrix(-sprite.GetHotSpot(2)));
	sprite.Draw(GetMatrix());
}

void Ship::TestForWrap()
{
	const double x_limit = Engine::GetWindow().GetSize().x + sprite.GetFrameSize().x / 2;
	const double y_limit = Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y / 2;
	if (GetPosition().x > x_limit)
	{
		SetPosition({-sprite.GetFrameSize().x / 2.0 ,GetPosition().y});
	}
	else if (GetPosition().x < -sprite.GetFrameSize().x / 2)
	{
		SetPosition({ x_limit ,GetPosition().y });
	}
	if (GetPosition().y > y_limit)
	{
		SetPosition({ GetPosition().x ,-sprite.GetFrameSize().y / 2.0 });
	}
	else if (GetPosition().y < -sprite.GetFrameSize().y / 2)
	{
		SetPosition({ GetPosition().x , y_limit });
	}
}
