/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Splash.h
Project: CS230
Author: Daehyeon Kim
Creation date: 03/08/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"

class Splash : public CS230::GameState {
public:
	Splash();
	void Load() override;
	void Update() override;
	void Unload() override;

	std::string GetName() override { return "Splash"; }
private:
	CS230::InputKey levelNext;
};