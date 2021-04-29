/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level2.h
Project: CS230
Author: Daehyeon Kim
Creation date: 03/08/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"
#include "../Engine/GameObjectManager.h"
#include "Ship.h"
class Level2 : public CS230::GameState {
public:
	Level2();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;
	std::string GetName() override { return "Level 2"; }
private:
	int score;
	CS230::Texture scoreTexture;
	
	CS230::InputKey mainMenu;
	CS230::InputKey levelReload;
	CS230::GameObjectManager gameObjectManager;
	math::TransformMatrix noCamera;
};
