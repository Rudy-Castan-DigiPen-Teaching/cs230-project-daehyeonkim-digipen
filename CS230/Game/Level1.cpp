/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"
#include "../Engine/Camera.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/ShowCollision.h"
#include "Screens.h"
#include "Level1.h"
#include "Hero.h"
#include "Ball.h"
#include "Bunny.h"
#include "TreeStump.h"
#include "Fonts.h"
#include "Score.h"
#include "Timer.h"
#include "Gravity.h"
#include "Floor.h"
#include "Exit.h"
#include "GameParticles.h"

Level1::Level1() : levelReload(CS230::InputKey::Keyboard::R), mainMenu(CS230::InputKey::Keyboard::Escape), lives(3), heroPtr(nullptr) {
}

void Level1::Load() {
	AddGSComponent(new Gravity(1875));
#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif

	Background* bgPtr = new Background();
	AddGSComponent(bgPtr);
	bgPtr->Add("assets/clouds.png", 4);
	bgPtr->Add("assets/mountains.png", 2);
	bgPtr->Add("assets/foreground.png", 1);

	AddGSComponent(new Score(0, Fonts::Font1));
	AddGSComponent(new Timer(60));

	CS230::Camera* cameraPtr = new CS230::Camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, {0.35 * Engine::GetWindow().GetSize().x, 0 } });
	AddGSComponent(cameraPtr);
	cameraPtr->SetExtent({ { 0,0 }, { GetGSComponent<Background>()->Size() - Engine::GetWindow().GetSize() } });

	CS230::GameObjectManager* gom = new CS230::GameObjectManager();
	AddGSComponent(gom);
	gom->Add(new Ball({ 600, Level1::floor }));
	gom->Add(new Ball({ 2700, Level1::floor }));
	gom->Add(new Ball({ 4800, Level1::floor }));
	gom->Add(new TreeStump({ 300, Level1::floor }, 3));
	gom->Add(new TreeStump({ 1200, Level1::floor }, 2));
	gom->Add(new TreeStump({ 2200, Level1::floor }, 1));
	gom->Add(new TreeStump({ 2800, Level1::floor }, 5));
	gom->Add(new TreeStump({ 5100, Level1::floor }, 5));
	gom->Add(new Floor({ {0, 0}, {1471, static_cast<int>(Level1::floor)} }));
	gom->Add(new Floor({ {1602, 0}, {4262, static_cast<int>(Level1::floor)} }));
	gom->Add(new Floor({ {4551, 0}, {5760, static_cast<int>(Level1::floor)} }));
	gom->Add(new Exit({ {5550, static_cast<int>(Level1::floor)}, {5760, 683} }));
	heroPtr = new Hero({ 100, Level1::floor - 1 });
	gom->Add(new Bunny({ 1000, floor }, { 674, 1132 }, heroPtr));
	gom->Add(new Bunny({ 2000, floor }, { 1635, 2135 }, heroPtr));
	gom->Add(new Bunny({ 3200, floor }, { 2860, 4250 }, heroPtr));
	gom->Add(new Bunny({ 3800, floor }, { 2860, 4250 }, heroPtr));
	gom->Add(heroPtr);


	CS230::SpriteFont& font = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1));
	livesTexture = font.DrawTextToTexture("Lives: " + std::to_string(lives), 0xFFFFFFFF, true);
	AddGSComponent(new SmokeEmitter());
}
void Level1::Update(double dt) {
	UpdateGSComponents(dt);
	GetGSComponent<CS230::Camera>()->Update(heroPtr->GetPosition());

	if (GetGSComponent<Timer>()->hasEnded() || heroPtr->IsDead() == true) {
		if (lives > 1) {
			lives--;
			Engine::GetGameStateManager().ReloadState();
		} else {
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
			lives = 3;
		}
	}
	if (mainMenu.IsKeyReleased() == true) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
#ifdef _DEBUG
	if (levelReload.IsKeyReleased() == true) {
		Engine::GetGameStateManager().ReloadState();
	}
#endif
}
void Level1::Unload() {
	ClearGSComponent();
	heroPtr = nullptr;
}

void Level1::Draw() {
	Engine::GetWindow().Clear(0x3399DAFF);

	CS230::Camera* cameraPtr = GetGSComponent<CS230::Camera>();
	GetGSComponent<Background>()->Draw(*cameraPtr);
	math::TransformMatrix cameraMatrix = cameraPtr->GetMatrix();
	GetGSComponent<CS230::GameObjectManager>()->DrawAll(cameraMatrix);

	math::ivec2 winSize = Engine::GetWindow().GetSize();
	if (GetGSComponent<Score>() != nullptr) {
		GetGSComponent<Score>()->Draw({ 10, winSize.y - 5 });
	}
	if (GetGSComponent<Timer>() != nullptr) {
		GetGSComponent<Timer>()->Draw({ winSize.x - 10, winSize.y - 5 });
	}
	livesTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - livesTexture.GetSize().x / 2, winSize.y - livesTexture.GetSize().y - 5 }));
}