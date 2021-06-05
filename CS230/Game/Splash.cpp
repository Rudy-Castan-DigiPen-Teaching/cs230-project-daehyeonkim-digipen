/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Splash.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#include <filesystem>
#include "../Engine/Engine.h"	//GetGameStateManager	GetTextureManager
#include "../Engine/Texture.h"
#include "../Engine/TransformMatrix.h"
#include "Screens.h"
#include "Splash.h"

Splash::Splash() {}

void Splash::Load() {
	texturePtr = Engine::GetTextureManager().Load("assets/DigiPen_BLACK_1024px.png");
	timer = 0;
}

void Splash::Update(double dt) {
	timer += dt;
	if (timer >= DISPLAY_TIME) {
		Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
}

void Splash::Unload() {
}
void Splash::Draw() {
	Engine::GetWindow().Clear(0xFFFFFFFF);

	texturePtr->Draw(math::TranslateMatrix({ (Engine::GetWindow().GetSize() - texturePtr->GetSize()) / 2.0 }));
}