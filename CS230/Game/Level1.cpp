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
#include "../Engine/TransformMatrix.h"

Level1::Level1() : camera(math::rect2{ math::vec2{Engine::GetWindow().GetSize().x * 0.15, 0}, math::vec2{ Engine::GetWindow().GetSize().x * 0.35, static_cast<double>(Engine::GetWindow().GetSize().y) } }), levelNext(CS230::InputKey::Keyboard::Enter), levelReload(CS230::InputKey::Keyboard::R), hero({ Engine::GetWindow().GetSize().x / 2.0, floor }, camera), ball1({ 600, floor }), ball2({ 2700, floor }), ball3({ 4800, floor })
{}

void Level1::Load() {
	background.Add("assets/clouds.png", 4);
	background.Add("assets/Mountains.png", 2);
	background.Add("assets/foreground.png", 1);
	camera.SetPosition({0, 0});
	camera.SetExtent({ {0, 0},{background.Size().x - Engine::GetWindow().GetSize().x, background.Size().y } });
	hero.Load();
	ball1.Load();
	ball2.Load();
	ball3.Load();
}
void Level1::Update(double dt) {
	hero.Update(dt);
	ball1.Update(dt);
	ball2.Update(dt);
	ball3.Update(dt);
	camera.Update(hero.GetPosition());
	Engine::GetLogger().LogDebug(std::to_string(camera.GetPosition().x));
	if (levelNext.IsKeyReleased() == true) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Level2));
	}
#if _DEBUG
	if(levelReload.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().ReloadState();
	}
#endif
}
void Level1::Unload() {
	background.Unload();
}

void Level1::Draw()
{
	Engine::GetWindow().Clear(0x3399DAFF);
	background.Draw(camera);
	math::TransformMatrix cameraMatrix = camera.GetMatrix();
	hero.Draw(cameraMatrix);
	ball1.Draw(cameraMatrix);
	ball2.Draw(cameraMatrix);
	ball3.Draw(cameraMatrix);
}
