/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: MainMenu.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 04/27/2021
-----------------------------------------------------------------*/
#include "MainMenu.h"
#include "Fonts.h"
#include "../Engine/Engine.h"
#include "../Engine/TransformMatrix.h"

MainMenu::OptionData MainMenu::optionsData[static_cast<int>(MainMenu::Options::Count)] = {
	{"Side Scroller", {0.5, 0.45}, {} },
	{"Space Shooter", {0.5, 0.35}, {} },
	{"Quit", {0.5, 0.25}, {} },
};

MainMenu::MainMenu() : upKey(CS230::InputKey::Keyboard::Up), downKey(CS230::InputKey::Keyboard::Down), selectKey(CS230::InputKey::Keyboard::Enter)
{
	
}

void MainMenu::Load()
{
	title = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("CS230 Project", 0xFFFFFFFF, true);
	for (OptionData& data : optionsData) {
		RenderOption(data, false);
	}
	selectedIndex = static_cast<int>(Options::Level1);
	RenderOption(optionsData[selectedIndex], true);
}

void MainMenu::Update([[maybe_unused]]double dt)
{
	constexpr int enumGap = 2;
	switch(selectedIndex)
	{
		case static_cast<int>(Options::Level1) :
			if (downKey.IsKeyReleased() == true)
			{
				RenderOption(optionsData[selectedIndex], false);
				selectedIndex++;
			}
			if (selectKey.IsKeyReleased() == true)
			{
				Engine::GetGameStateManager().SetNextState(enumGap + selectedIndex);
			}
			break;
		case static_cast<int>(Options::Level2) :
			if (downKey.IsKeyReleased() == true)
			{
				RenderOption(optionsData[selectedIndex], false);
				selectedIndex++;
			}
			if (upKey.IsKeyReleased() == true)
			{
				RenderOption(optionsData[selectedIndex], false);
				selectedIndex--;
			}
			if (selectKey.IsKeyReleased() == true)
			{
				Engine::GetGameStateManager().SetNextState(enumGap + selectedIndex);
			}
			break;
		case static_cast<int>(Options::Quit) :
			if (upKey.IsKeyReleased() == true)
			{
				RenderOption(optionsData[selectedIndex], false);
				selectedIndex--;
			}
			if (selectKey.IsKeyReleased() == true)
			{
				Engine::GetGameStateManager().Shutdown();
			}
			break;
	}
	RenderOption(optionsData[selectedIndex], true);
}

void MainMenu::Unload()
{
}

void MainMenu::Draw()
{
	Engine::GetWindow().Clear(0x3399DAFF);
	title.Draw(math::TransformMatrix() * math::TranslateMatrix(math::vec2{ Engine::GetWindow().GetSize().x / 2 - static_cast<double>(title.GetSize().x), Engine::GetWindow().GetSize().y * 0.6}) * math::ScaleMatrix({2,2}));
	optionsData[static_cast<int>(Options::Level1)].texture.Draw(math::TransformMatrix() * math::TranslateMatrix(math::vec2{ Engine::GetWindow().GetSize().x / 2 - optionsData[static_cast<int>(Options::Level1)].texture.GetSize().x / 2.0, Engine::GetWindow().GetSize().y * 0.4 }));
	optionsData[static_cast<int>(Options::Level2)].texture.Draw(math::TransformMatrix() * math::TranslateMatrix(math::vec2{ Engine::GetWindow().GetSize().x / 2 - optionsData[static_cast<int>(Options::Level2)].texture.GetSize().x / 2.0, Engine::GetWindow().GetSize().y * 0.3 }));
	optionsData[static_cast<int>(Options::Quit)].texture.Draw(math::TransformMatrix() * math::TranslateMatrix(math::vec2{ Engine::GetWindow().GetSize().x / 2 - optionsData[static_cast<int>(Options::Quit)].texture.GetSize().x / 2.0, Engine::GetWindow().GetSize().y * 0.2 }));
}

void MainMenu::RenderOption(OptionData& data, bool isHighlighted)
{
	data.texture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(data.text, (isHighlighted == true) ? MainMenu::onColor : MainMenu::offColor, true);
}
