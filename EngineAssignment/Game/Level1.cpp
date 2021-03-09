/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 03/08/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "Screens.h"
#include "Level1.h"

Level1::Level1() : levelNext(CS230::InputKey::Keyboard::Enter), levelReload(CS230::InputKey::Keyboard::R) {}

void Level1::Load() {
}
void Level1::Update() {
	if (levelNext.IsKeyReleased()) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Level2));
	}
#if _DEBUG
	if(levelReload.IsKeyReleased())
	{
		Engine::GetGameStateManager().ReloadState();
	}
#endif
}
void Level1::Unload() {
}