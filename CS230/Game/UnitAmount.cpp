/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: UnitAmount.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 06/17/2021
-----------------------------------------------------------------*/
#include "UnitAmount.h"
#include "../Engine/Engine.h"
#include "../Engine/TransformMatrix.h"

UnitAmount::UnitAmount(int playerUnitAmount, int enemyUnitAmount, Fonts fontToUse) : playerUnitAmount(playerUnitAmount), enemyUnitAmount(enemyUnitAmount), fontToUse(fontToUse)
{
	RenderText();
}

void UnitAmount::UpdateUnitAmount(int playerUpdate, int enemyUpdate)
{
	playerUnitAmount += playerUpdate;
	enemyUnitAmount += enemyUpdate;
	RenderText();
}

void UnitAmount::Draw(math::ivec2 location)
{
	constexpr double scaleSize = 0.4;
	math::TransformMatrix textScale = math::ScaleMatrix({ scaleSize, scaleSize });
	playerUnitAmountTexture.Draw(math::TranslateMatrix(location + math::ivec2{10,0}) * textScale);
	enemyUnitAmountTexture.Draw(math::TranslateMatrix(location + math::ivec2{ -10,0 } + (math::ivec2{ Engine::GetWindow().GetSize().x - static_cast<int>(enemyUnitAmountTexture.GetSize().x * scaleSize), 0 })) * textScale);
}

void UnitAmount::RenderText()
{

	std::string scoreString = std::to_string(playerUnitAmount) + " / " + std::to_string(unitLimit);
	playerUnitAmountTexture = Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);
	scoreString = std::to_string(enemyUnitAmount) + " / " + std::to_string(unitLimit);
	enemyUnitAmountTexture = Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);
}
