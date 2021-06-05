/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level3.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 06/04/2021
-----------------------------------------------------------------*/
#include "Level3.h"
#include "Alliance.h"
#include "Horde.h"
#include "Score.h"
#include "Fonts.h"
#include "Gold.h"
#include "Screens.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/ShowCollision.h"

Level3::Level3() : levelReload(CS230::InputKey::Keyboard::R), mainMenu(CS230::InputKey::Keyboard::Escape), player(nullptr), enemy(nullptr) {}

void Level3::Load()
{
#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif
	AddGSComponent(new Score(0, Fonts::Font1));
	AddGSComponent(new Gold(1000, Fonts::Font1));
	Background* bgPtr = new Background();
	AddGSComponent(bgPtr);
	bgPtr->Add("assets/map.png", 1);
	CS230::GameObjectManager* gom = new CS230::GameObjectManager();
	AddGSComponent(gom);
	player = new Alliance({0, floor}, 2000, { 1.5,1.5 });
	enemy = new Horde({ Engine::GetWindow().GetSize().x - 96., floor }, 2000, {1.5,1.5});
	gom->Add(player);
	gom->Add(enemy);
	
}

void Level3::Update(double dt)
{
	UpdateGSComponents(dt);
	if (mainMenu.IsKeyReleased() == true) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
#ifdef _DEBUG
	if (levelReload.IsKeyReleased() == true) {
		Engine::GetGameStateManager().ReloadState();
	}
#endif
}

void Level3::Unload()
{
	ClearGSComponent();
	player = nullptr;
}

void Level3::Draw()
{
	Engine::GetWindow().Clear(0x3399DAFF);
	GetGSComponent<Background>()->Draw({ 0,0 });
	math::TransformMatrix camera;
	GetGSComponent<CS230::GameObjectManager>()->DrawAll(camera);
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	if (GetGSComponent<Score>() != nullptr) {
		GetGSComponent<Score>()->Draw({ 10, winSize.y - 5 });
	}
	if (GetGSComponent<Gold>() != nullptr) {
		GetGSComponent<Gold>()->Draw({ winSize.x / 2, winSize.y - 5 });
	}
}
