/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level3.h
Project: CS230
Author: Daehyeon Kim
Creation date: 06/04/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"
#include "Background.h"
#include "..\Engine\texture.h"
class Horde;
class Alliance;

class Level3 : public CS230::GameState {
public:

	Level3();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Level 3"; }
private:
	static constexpr double floor = 130.0f;

	Alliance* player;
	Horde* enemy;
	CS230::InputKey levelReload;
	CS230::InputKey mainMenu;
};
