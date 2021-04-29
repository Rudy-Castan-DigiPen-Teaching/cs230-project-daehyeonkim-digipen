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
#include "../Engine/TransformMatrix.h"

Splash::Splash(){}

void Splash::Load() {
	texturePtr = Engine::GetTextureManager().Load("assets/DigiPen_BLACK_1024px.png");
}
void Splash::Update(double dt) {
	if (timer > splash_time) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	} else
	{
		timer += dt;
	}
}
void Splash::Unload() {
}

void Splash::Draw()
{
	Engine::GetWindow().Clear(0xFFFFFFFF);
	texturePtr->Draw(math::TranslateMatrix(Engine::GetWindow().GetSize() / 2 - texturePtr->GetSize() / 2));
}
