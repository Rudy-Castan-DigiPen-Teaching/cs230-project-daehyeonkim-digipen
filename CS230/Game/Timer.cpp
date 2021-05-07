/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Timer.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 04/30/2021
-----------------------------------------------------------------*/
#include "Timer.h"
#include "Fonts.h"
#include "../Engine/Engine.h"
#include "../Engine/TransformMatrix.h"

Timer::Timer(int time) : timer(time)
{
	std::string timerString = "Time: " + std::to_string(static_cast<int>(timer));
	timeTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(timerString, 0xFFFFFFFF, true);
}

void Timer::Update(double dt)
{
	if (static_cast<int>(timer) > static_cast<int>(timer - dt))
	{
		std::string timerString = "Time: " + std::to_string(static_cast<int>(timer));
		timeTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(timerString, 0xFFFFFFFF, true);
	}
	timer -= dt;
}

void Timer::Draw(math::ivec2 location)
{
	timeTexture.Draw(math::TranslateMatrix(location - math::ivec2{ 0, timeTexture.GetSize().y + 5 }));
}

bool Timer::hasEnded()
{
	return (timer <= 0) == true;
}
