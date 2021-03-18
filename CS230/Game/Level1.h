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
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"
#include "Hero.h"
class Level1 : public CS230::GameState {
public:
	static constexpr double floor = 126.0f;

	Level1();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
    void Draw() override;
	
	std::string GetName() override { return "Level 1"; }
private:
	CS230::InputKey levelNext;
	CS230::InputKey levelReload;
	Hero hero;
	CS230::Texture background;
};