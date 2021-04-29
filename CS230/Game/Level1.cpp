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
#include "Fonts.h"
#include "TreeStump.h"

Level1::Level1() : lives(3), camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, {0.35 * Engine::GetWindow().GetSize().x, 0 } }),
                   levelReload(CS230::InputKey::Keyboard::R), mainMenu(CS230::InputKey::Keyboard::Escape) {}

void Level1::Load() {
	timer = 5;
	score = 0;
	std::string scoreString = "Score: " + std::to_string(score / 100) + std::to_string((score % 100) / 10) + std::to_string(score % 10);
	scoreTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);
	std::string livesString = "Lives: " + std::to_string(lives);
	livesTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(livesString, 0xFFFFFFFF, true);
	std::string timerString = "Time: " + std::to_string(timer);
	timerTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(timerString, 0xFFFFFFFF, true);
	heroPtr = new Hero({ 150, Level1::floor }, camera);
	gameObjectManager.Add(heroPtr);
	gameObjectManager.Add(new Ball({ 600, Level1::floor }));
	gameObjectManager.Add(new Ball({ 2700, Level1::floor }));
	gameObjectManager.Add(new Ball({ 4800, Level1::floor }));
	gameObjectManager.Add(new Bunny({ 1000, Level1::floor }));
	gameObjectManager.Add(new Bunny({ 2000, Level1::floor }));
	gameObjectManager.Add(new Bunny({ 3200, Level1::floor }));
	gameObjectManager.Add(new Bunny({ 3800, Level1::floor }));
	gameObjectManager.Add(new TreeStump({ 300, Level1::floor }, 3));
	gameObjectManager.Add(new TreeStump({ 1200, Level1::floor }, 2));
	gameObjectManager.Add(new TreeStump({ 2200, Level1::floor }, 1));
	gameObjectManager.Add(new TreeStump({ 2800, Level1::floor }, 5));
	gameObjectManager.Add(new TreeStump({ 5100, Level1::floor }, 5));

	background.Add("assets/clouds.png", 4);
	background.Add("assets/mountains.png", 2);
	background.Add("assets/foreground.png", 1);

	camera.SetPosition({ 0,0 });
	camera.SetExtent({ { 0,0 }, { background.Size() - Engine::GetWindow().GetSize() } });
}
void Level1::Update(double dt) {
	std::string timerString = "Time: " + std::to_string(std::floor(timer));
	timerTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(timerString, 0xFFFFFFFF, true);
	if(timer <= 0)
	{
		lives--;
		Engine::GetGameStateManager().ReloadState();
		if(lives == 0)
		{
			lives = 3;
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
		} else
		{
			Engine::GetGameStateManager().ReloadState();
		}
	}
	gameObjectManager.UpdateAll(dt);
	camera.Update(heroPtr->GetPosition());
	if (mainMenu.IsKeyReleased() == true) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
#if _DEBUG
	if(levelReload.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().ReloadState();
	}
#endif
	timer-=dt;
}
void Level1::Unload() {
	background.Unload();
	gameObjectManager.Unload();
	heroPtr = nullptr;
}

void Level1::Draw()
{
	Engine::GetWindow().Clear(0x3399DAFF);
	background.Draw(camera);
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	scoreTexture.Draw(math::TranslateMatrix(math::ivec2{ 10, winSize.y - scoreTexture.GetSize().y - 5 }));
	livesTexture.Draw(math::TranslateMatrix(math::ivec2{ 400, winSize.y - scoreTexture.GetSize().y - 5 }));
	timerTexture.Draw(math::TranslateMatrix(math::ivec2{ 800, winSize.y - scoreTexture.GetSize().y - 5 }));
	math::TransformMatrix cameraMatrix = camera.GetMatrix();
	gameObjectManager.DrawAll(cameraMatrix);
}
