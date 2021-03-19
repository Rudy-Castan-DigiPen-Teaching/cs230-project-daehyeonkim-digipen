/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Splash.h
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
---------------------------------- -------------------------------*/
#pragma once
#include "..\Engine\Texture.h"
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"

class Splash : public CS230::GameState {
public:
	Splash();
	void Load() override;
	void Update(double) override;
	void Unload() override;
	void Draw() override;
	std::string GetName() override { return "Splash"; }
private:
	double timer = 0;
	static constexpr double splash_time = 3.0;
	CS230::Texture texture;
};