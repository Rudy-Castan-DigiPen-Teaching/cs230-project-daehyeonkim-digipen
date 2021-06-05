/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Score.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/17/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"		//DrawTextToTexture
#include "../Engine/TransformMatrix.h"
#include "../Engine/Vec2.h"
#include "Timer.h"
#include "Fonts.h"

Timer::Timer(int time) : timer(time) {
	std::string scoreString = "Time: " + std::to_string(static_cast<int>(timer));
	timeTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);
}

void Timer::Update(double dt) {
	int oldTimerInt = static_cast<int>(timer);
	timer -= dt;
	if (oldTimerInt != static_cast<int>(timer)) {
		std::string scoreString = "Time: " + std::to_string(static_cast<int>(timer) + 1);
		timeTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);
	}
}

void Timer::Draw(math::ivec2 location) {
	timeTexture.Draw(math::TranslateMatrix(location - timeTexture.GetSize()));
}

bool Timer::hasEnded() {
	return timer <= 0;
}