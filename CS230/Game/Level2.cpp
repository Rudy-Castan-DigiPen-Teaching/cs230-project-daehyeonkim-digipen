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
#include "Score.h"
#include "../Engine/ShowCollision.h"

Level2::Level2() : gameObjectManager(nullptr), mainMenu(CS230::InputKey::Keyboard::Escape), levelReload(CS230::InputKey::Keyboard::R) { gameObjectManager = GetGSComponent<CS230::GameObjectManager>(); }

void Level2::Load() {
#if _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif
	AddGSComponent(new CS230::GameObjectManager());
	gameObjectManager = GetGSComponent<CS230::GameObjectManager>();
	AddGSComponent(new Score(0, Fonts::Font2));
	gameObjectManager->Add(new Ship({ Engine::GetWindow().GetSize() / 2.0 }));
	gameObjectManager->Add(new Meteor());
	gameObjectManager->Add(new Meteor());
	gameObjectManager->Add(new Meteor());
	gameObjectManager->Add(new Meteor());
	gameObjectManager->Add(new Meteor());
}
void Level2::Update(double dt) {
	gameObjectManager->Update(dt);
	if (mainMenu.IsKeyReleased() == true) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
#if _DEBUG
	if (levelReload.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().ReloadState();
	}
	GetGSComponent<ShowCollision>()->Update(dt);
#endif
}
void Level2::Unload() {
	ClearGSComponent();
}

void Level2::Draw()
{
	Engine::GetWindow().Clear(0x000000FF);
	gameObjectManager->DrawAll(noCamera);
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	GetGSComponent<Score>()->Draw(math::ivec2{ 10, winSize.y });
}

