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
#include "Ball.h"
#include "Bunny.h"
#include "Exit.h"
#include "Floor.h"
#include "Fonts.h"
#include "GameParticles.h"
#include "Gravity.h"
#include "Score.h"
#include "Timer.h"
#include "TreeStump.h"
#include "../Engine/Camera.h"
#include "../Engine/ShowCollision.h"

Level1::Level1() : heroPtr(nullptr), gameObjectManager(nullptr), levelReload(CS230::InputKey::Keyboard::R), mainMenu(CS230::InputKey::Keyboard::Escape), lives(3)
{
}
void Level1::Load() {
#if _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif

	AddGSComponent(new CS230::GameObjectManager());
	AddGSComponent(new Background());
	gameObjectManager = GetGSComponent<CS230::GameObjectManager>();
	AddGSComponent(new Score(0, Fonts::Font1));
	AddGSComponent(new Timer(60));
	AddGSComponent(new Gravity(2000));
	std::string livesString = "Lives: " + std::to_string(lives);
	livesTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(livesString, 0xFFFFFFFF, true);
	gameObjectManager->Add(new Ball({ 600, Level1::floor }));
	gameObjectManager->Add(new Ball({ 2700, Level1::floor }));
	gameObjectManager->Add(new Ball({ 4800, Level1::floor }));
	gameObjectManager->Add(new TreeStump({ 300, Level1::floor }, 3));
	gameObjectManager->Add(new TreeStump({ 1200, Level1::floor }, 2));
	gameObjectManager->Add(new TreeStump({ 2200, Level1::floor }, 1));
	gameObjectManager->Add(new TreeStump({ 2800, Level1::floor }, 5));
	gameObjectManager->Add(new TreeStump({ 5100, Level1::floor }, 5));
	gameObjectManager->Add(new Floor({ {0, 0}, {1471, static_cast<int>(Level1::floor)} }));
	gameObjectManager->Add(new Floor({ {1602, 0}, {4262, static_cast<int>(Level1::floor)} }));
	gameObjectManager->Add(new Floor({ {4551, 0}, {5760, static_cast<int>(Level1::floor)} }));
	gameObjectManager->Add(new Exit({ {5550, static_cast<int>(Level1::floor)}, {5760, 683} }));
	heroPtr = new Hero({ 100, Level1::floor - 1 });
	gameObjectManager->Add(new Bunny({ 1000, floor }, { 674, 1132 }, heroPtr));
	gameObjectManager->Add(new Bunny({ 2000, floor }, { 1635, 2135 }, heroPtr));
	gameObjectManager->Add(new Bunny({ 3200, floor }, { 2860, 4250 }, heroPtr));
	gameObjectManager->Add(new Bunny({ 3800, floor }, { 2860, 4250 }, heroPtr));
	gameObjectManager->Add(heroPtr);
	AddGSComponent(new SmokeEmitter());
	GetGSComponent<Background>()->Add("assets/clouds.png", 4);
	GetGSComponent<Background>()->Add("assets/mountains.png", 2);
	GetGSComponent<Background>()->Add("assets/foreground.png", 1);
	CS230::Camera* cameraPtr = new CS230::Camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, {0.35 * Engine::GetWindow().GetSize().x, 0 } });
	AddGSComponent(cameraPtr);
	cameraPtr->SetExtent({ { 0,0 }, { GetGSComponent<Background>()->Size() - Engine::GetWindow().GetSize() } });
}
void Level1::Update(double dt) {
	if(GetGSComponent<Timer>()->hasEnded() == true || heroPtr->IsDead() == true)
	{
		lives--;
		if(lives == 0)
		{
			lives = 3;
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
		} else
		{
			Engine::GetGameStateManager().ReloadState();
		}
	}
	gameObjectManager->Update(dt);
	GetGSComponent<CS230::Camera>()->Update(heroPtr->GetPosition());
	if (mainMenu.IsKeyReleased() == true) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
#if _DEBUG
	if(levelReload.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().ReloadState();
	}
	GetGSComponent<ShowCollision>()->Update(dt);
#endif
	GetGSComponent<Timer>()->Update(dt);
}
void Level1::Unload() {
	ClearGSComponent();
	heroPtr = nullptr;
}

void Level1::Draw()
{
	Engine::GetWindow().Clear(0x3399DAFF);
	CS230::Camera* cameraPtr = GetGSComponent<CS230::Camera>();
	GetGSComponent<Background>()->Draw(*cameraPtr);
	
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	GetGSComponent<Score>()->Draw(math::ivec2{ 10, winSize.y});
	GetGSComponent<Timer>()->Draw(math::ivec2{ winSize.x , winSize.y});
	livesTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - livesTexture.GetSize().x / 2, winSize.y - livesTexture.GetSize().y - 5 }));

	math::TransformMatrix cameraMatrix = cameraPtr->GetMatrix();
	gameObjectManager->DrawAll(cameraMatrix);
}
