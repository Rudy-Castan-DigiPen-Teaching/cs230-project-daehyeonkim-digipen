/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level2.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"   //GetWindow, GetGameStateManager
#include "../Engine/ShowCollision.h"
#include "Screens.h"
#include "Level2.h"
#include "Ship.h"
#include "EnemyShip.h"
#include "Meteor.h"
#include "Fonts.h"
#include "Score.h"
#include "GameParticles.h"

Level2::Level2() : levelReload(CS230::InputKey::Keyboard::R), mainMenu(CS230::InputKey::Keyboard::Escape), shipPtr(nullptr) {}

void Level2::Load() {
#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif

	CS230::GameObjectManager* gom = new CS230::GameObjectManager();
	AddGSComponent(gom);
	shipPtr = new Ship({ Engine::GetWindow().GetSize() / 2.0 });
	EnemyShip* enemy = new EnemyShip(shipPtr);
	gom->Add(new Meteor());
	gom->Add(new Meteor());
	gom->Add(new Meteor());
	gom->Add(new Meteor());
	gom->Add(new Meteor());
	gom->Add(enemy);
	gom->Add(shipPtr);

	AddGSComponent(new Score(0, Fonts::Font2));
	AddGSComponent(new HitEmitter());
	AddGSComponent(new MeteorBitEmitter());

	GameOverTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Game Over", 0xFFFFFFFF, false);
	RestartTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Press r to restart", 0xFFFFFFFF, false);
}

void Level2::Update(double dt) {
	UpdateGSComponents(dt);

	if (mainMenu.IsKeyReleased() == true) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
#ifdef _DEBUG
    if (levelReload.IsKeyReleased() == true) {
        Engine::GetGameStateManager().ReloadState();
    }
#else
	if (shipPtr != nullptr && shipPtr->IsDead() == true && levelReload.IsKeyReleased() == true) {
		Engine::GetGameStateManager().ReloadState();
	}
#endif
}

void Level2::Unload() {
	ClearGSComponent();
	shipPtr = nullptr;
}

void Level2::Draw() {
	Engine::GetWindow().Clear(0x000000FF);
	math::TransformMatrix camera;
	GetGSComponent<CS230::GameObjectManager>()->DrawAll(camera);

	math::ivec2 winSize = Engine::GetWindow().GetSize();
	GetGSComponent<Score>()->Draw({ 10, winSize.y - 5 });

	if (shipPtr->IsDead() == true) {
		GameOverTexture.Draw(math::TranslateMatrix(winSize / 2 + math::ivec2{ 0, 30 } - GameOverTexture.GetSize() / 2));
		RestartTexture.Draw(math::TranslateMatrix(winSize / 2 + math::ivec2{ 0, -30 } - RestartTexture.GetSize() / 2));
	}
}