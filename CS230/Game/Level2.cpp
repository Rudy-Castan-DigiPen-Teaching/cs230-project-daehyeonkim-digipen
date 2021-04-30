/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level2.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 03/08/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "Screens.h"
#include "Level2.h"

#include "Fonts.h"
#include "Meteor.h"

Level2::Level2() : mainMenu(CS230::InputKey::Keyboard::Escape), levelReload(CS230::InputKey::Keyboard::R) {}

void Level2::Load() {
	std::string scoreString = "Score: " + std::to_string(score / 100) + std::to_string((score % 100) / 10) + std::to_string(score % 10);
	scoreTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture(scoreString, 0xFFFFFFFF, false);
	gameObjectManager.Add(new Ship({ Engine::GetWindow().GetSize() / 2.0 }));
	gameObjectManager.Add(new Meteor());
	gameObjectManager.Add(new Meteor());
	gameObjectManager.Add(new Meteor());
	gameObjectManager.Add(new Meteor());
	gameObjectManager.Add(new Meteor());
}
void Level2::Update(double dt) {
	gameObjectManager.UpdateAll(dt);
	if (mainMenu.IsKeyReleased() == true) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
#if _DEBUG
	if (levelReload.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().ReloadState();
	}
#endif
}
void Level2::Unload() {
	gameObjectManager.Unload();
}

void Level2::Draw()
{
	Engine::GetWindow().Clear(0x000000FF);
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	scoreTexture.Draw(math::TranslateMatrix(math::ivec2{ 10, winSize.y - scoreTexture.GetSize().y - 5 }));
	gameObjectManager.DrawAll(noCamera);
}

