/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Gold.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 06/04/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"		//DrawTextToTexture
#include "../Engine/TransformMatrix.h"
#include "../Engine/Vec2.h"
#include "Gold.h"
#include "Fonts.h"

Gold::Gold(int startingGold, Fonts fontToUse) : fontToUse(fontToUse), gold(startingGold) {
	RenderText();
}

void Gold::UpdateGold(int newPoints) {
	gold += newPoints;
	RenderText();
}

void Gold::Draw(math::ivec2 location) {
	goldTexture.Draw(math::TranslateMatrix(location - goldTexture.GetSize()));
}

void Gold::RenderText() {
	std::string scoreString = "Gold: " + std::to_string(gold);
	goldTexture = Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);
}