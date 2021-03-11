/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Splash.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "Screens.h"
#include "Splash.h"

Splash::Splash() : levelNext(CS230::InputKey::Keyboard::Enter) {}

void Splash::Load() {
}
void Splash::Update() {
	if (levelNext.IsKeyReleased()) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Level1));
	}
}
void Splash::Unload() {
}