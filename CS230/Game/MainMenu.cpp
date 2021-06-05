/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: MainMenu.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/16/2021
-----------------------------------------------------------------*/
#include <doodle/drawing.hpp>
#include "../Engine/Engine.h"	//GetGameStateManager GetSpriteFont
#include "../Engine/TransformMatrix.h"
#include "Screens.h"
#include "MainMenu.h"
#include "Fonts.h"



MainMenu::OptionData MainMenu::optionsData[static_cast<int>(MainMenu::Options::Count)] = {
	{"Side Scroller", {0.5, 0.45}, {} },
	{"Space Shooter", {0.5, 0.35}, {} },
	{"Knight vs Monster", {0.5,0.25}, {}},
	{"Quit", {0.5, 0.15}, {} },
};

MainMenu::MainMenu() : selectedIndex(0), upKey(CS230::InputKey::Keyboard::Up),
							downKey(CS230::InputKey::Keyboard::Down), selectKey(CS230::InputKey::Keyboard::Enter) {
}

void MainMenu::Load() {
	title = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("CS230 Project", 0xFFFFFFFF, true);
	for (OptionData& data : optionsData) {
		RenderOption(data, false);
	}
	selectedIndex = static_cast<int>(Options::Level1);
	RenderOption(optionsData[selectedIndex], true);
}

void MainMenu::Update(double) {
	if (upKey.IsKeyReleased() == true) {
		RenderOption(optionsData[selectedIndex], false);
		if (selectedIndex != 0) {
			selectedIndex--;
		}
		RenderOption(optionsData[selectedIndex], true);
	}
	if (downKey.IsKeyReleased() == true) {
		RenderOption(optionsData[selectedIndex], false);
		if (selectedIndex != static_cast<int>(Options::Count) -1) {
			selectedIndex++;
		}
		RenderOption(optionsData[selectedIndex], true);
	}
	if (selectKey.IsKeyReleased() == true) {
		switch (static_cast<Options>(selectedIndex)) {
		case Options::Level1:
			Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::Level1));
			break;
		case Options::Level2:
			Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::Level2));
			break;
		case Options::Level3:
			Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::Level3));
			break;
		case Options::Quit:
			Engine::GetGameStateManager().Shutdown();
			break;
		}
	}
}

void MainMenu::Unload() {}

void MainMenu::Draw() {
	Engine::GetWindow().Clear(0x3399DAFF);
	math::ivec2 winSize = Engine::GetWindow().GetSize();

	math::ivec2 position = math::ivec2{ winSize.x / 2 - title.GetSize().x, winSize.y / 2 + 130 };
	title.Draw(math::TranslateMatrix(position) * math::ScaleMatrix({ 2,2 }));

	for (OptionData& data : optionsData) {
		position = { static_cast<int>(winSize.x * data.positionPercent.x),
						static_cast<int>(winSize.y * data.positionPercent.y) };
		data.texture.Draw(math::TranslateMatrix(position - data.texture.GetSize() / 2));
	}
}

void MainMenu::RenderOption(OptionData& data, bool isHighlighted) {
	data.texture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(
								data.text, (isHighlighted == true) ? MainMenu::onColor : MainMenu::offColor, true);
}