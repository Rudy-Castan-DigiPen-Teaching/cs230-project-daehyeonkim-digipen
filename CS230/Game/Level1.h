/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.h
Project: CS230
Author: Daehyeon Kim
Creation date: 03/08/2021
-----------------------------------------------------------------*/
#pragma once
#include "Background.h"
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"
#include "Hero.h"
#include "../Engine/Camera.h"
#include "../Engine/GameObjectManager.h"

class Level1 : public CS230::GameState {
public:
	static constexpr double floor = 126.0f;
	static constexpr math::vec2 gravity{ 0, 2000 };

	Level1();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
    void Draw() override;
	
	std::string GetName() override { return "Level 1"; }
private:
	int score;
	int lives;
	double timer;
	CS230::Texture scoreTexture;
	CS230::Texture livesTexture;
	CS230::Texture timerTexture;
	
	CS230::InputKey mainMenu;
	CS230::InputKey levelReload;
	CS230::Camera camera;
	CS230::GameObjectManager gameObjectManager;
	Hero* heroPtr;
	Background background;

};
