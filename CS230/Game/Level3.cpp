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
#include "Background.h"
#include "Floor.h"
#include "Horde.h"
#include "Score.h"
#include "Fonts.h"
#include "GameParticles.h"
#include "Gold.h"
#include "Gravity.h"
#include "Screens.h"
#include "UnitAmount.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/ShowCollision.h"

Level3::Level3() : levelReload(CS230::InputKey::Keyboard::R), mainMenu(CS230::InputKey::Keyboard::Escape), addGold(CS230::InputKey::Keyboard::Enter),player(nullptr), enemy(nullptr), timer(0) {}

void Level3::Load()
{
	AddGSComponent(new Gravity(1000));
#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif
	AddGSComponent(new Score(0, Fonts::Font1));
	AddGSComponent(new Gold(0, Fonts::Font1));
	AddGSComponent(new UnitAmount(0, 0, Fonts::Font2));
	Background* bgPtr = new Background();
	AddGSComponent(bgPtr);
	bgPtr->Add("assets/map.png", 1);
	CS230::GameObjectManager* gom = new CS230::GameObjectManager();
	AddGSComponent(gom);
	constexpr double baseSize = 50.;
	player = new Alliance(math::vec2{ baseSize, floor }, 2000, math::vec2{ 1.5,1.5 }, 25,1,math::vec2{500, 0});
	enemy = new Horde({ Engine::GetWindow().GetSize().x - baseSize, floor }, 2000, { 1.5,1.5 });
	gom->Add(player);
	gom->Add(enemy);
	gom->Add(new Floor(math::irect2{{ 0, 0 }, { Engine::GetWindow().GetSize().x, static_cast<int>(Level3::floor) }}));
	AddGSComponent(new ShootCannonEmitter());
	AddGSComponent(new BombBoomEmitter());
	AddGSComponent(new UnitHurtEmitter());
	CS230::SpriteFont& font = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2));
	winTexture = font.DrawTextToTexture("Win!!", 0xFFFFFFFF, true);
	loseTexture = font.DrawTextToTexture("Lose...", 0xFFFFFFFF, true);
}

void Level3::Update(double dt)
{
	UpdateGSComponents(dt);
	if(player->GetHP() <= 0)
	{
		timer += dt;
	} else if(enemy->GetHP() <= 0)
	{
		timer += dt;
	}
	if (mainMenu.IsKeyReleased() == true || timer > 2) {
		timer = 0;
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
#ifdef _DEBUG
	if (levelReload.IsKeyReleased() == true) {
		Engine::GetGameStateManager().ReloadState();
	}
	if (addGold.IsKeyReleased() == true)
	{
		GetGSComponent<Gold>()->UpdateGold(1000);
	}
#endif
}

void Level3::Unload()
{
	ClearGSComponent();
	player = nullptr;
	enemy = nullptr;
}

void Level3::Draw()
{
	Engine::GetWindow().Clear(0x3399DAFF);
	GetGSComponent<Background>()->Draw({ 0,0 });
	math::TransformMatrix camera;
	GetGSComponent<CS230::GameObjectManager>()->DrawAll(camera);
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	if (GetGSComponent<Score>() != nullptr) 
	{
		GetGSComponent<Score>()->Draw({ 10, winSize.y - 5 });
	}
	if (GetGSComponent<Gold>() != nullptr) 
	{
		GetGSComponent<Gold>()->Draw({ winSize.x / 2, winSize.y - 5 });
	}
	if (GetGSComponent<UnitAmount>() != nullptr)
	{
		GetGSComponent<UnitAmount>()->Draw({0, static_cast<int>(winSize.y * 0.24)});
	}
	constexpr int scaleSize = 3;
	if (player->GetHP() <= 0)
	{
		loseTexture.Draw(math::TranslateMatrix(winSize / 2 - scaleSize * loseTexture.GetSize() / 2) * math::ScaleMatrix({ scaleSize, scaleSize }));
	}
	else if (enemy->GetHP() <= 0)
	{
		winTexture.Draw(math::TranslateMatrix(winSize / 2 - scaleSize * winTexture.GetSize() / 2) * math::ScaleMatrix({ scaleSize, scaleSize }));
	}
}
