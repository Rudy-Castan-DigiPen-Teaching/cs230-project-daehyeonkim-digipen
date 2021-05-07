/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Score.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 04/30/2021
-----------------------------------------------------------------*/
#include "Score.h"
#include "../Engine/Engine.h"
#include "../Engine/TransformMatrix.h"

Score::Score(int startingScore, Fonts fontToUse) : score(startingScore), fontToUse(fontToUse)
{
	RenderText();
}

void Score::AddScore(int newPoints)
{
	score += newPoints;
	RenderText();
}

void Score::Draw(math::ivec2 location)
{
	scoreTexture.Draw(math::TranslateMatrix(location - math::ivec2{0, scoreTexture.GetSize().y + 5}));
}

void Score::RenderText()
{
	std::string scoreString = "Score: " + std::to_string(score / 100) + std::to_string((score % 100) / 10) + std::to_string(score % 10);
	scoreTexture = Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);
}