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
	if (downKey.IsKeyReleased() == true && selectedIndex < static_cast<int>(Options::Quit))
	{
		RenderOption(optionsData[selectedIndex], false);
		selectedIndex++;
	}
	if (upKey.IsKeyReleased() == true && selectedIndex > static_cast<int>(Options::Level1))
	{
		RenderOption(optionsData[selectedIndex], false);
		selectedIndex--;
	}
	if (selectKey.IsKeyReleased() == true)
	{
		if(selectedIndex == static_cast<int>(Options::Quit))
		{
			Engine::GetGameStateManager().Shutdown();
		} else
		{
			Engine::GetGameStateManager().SetNextState(2 + selectedIndex);
		}
	}
	RenderOption(optionsData[selectedIndex], true);
}

void MainMenu::Unload()
{
}

void MainMenu::Draw()
{
	Engine::GetWindow().Clear(0x3399DAFF);
	title.Draw(math::TransformMatrix() * math::TranslateMatrix(math::vec2{ Engine::GetWindow().GetSize().x / 2 - title.GetSize().x/2.0, Engine::GetWindow().GetSize().y / 2.0}) * math::ScaleMatrix({2,2}));
	optionsData[static_cast<int>(Options::Level1)].texture.Draw(math::TransformMatrix() * math::TranslateMatrix(math::vec2{ Engine::GetWindow().GetSize().x / 2 - title.GetSize().x / 2.0, Engine::GetWindow().GetSize().y / 3.0 }));
	optionsData[static_cast<int>(Options::Level2)].texture.Draw(math::TransformMatrix() * math::TranslateMatrix(math::vec2{ Engine::GetWindow().GetSize().x / 2 - optionsData[static_cast<int>(Options::Level1)].texture.GetSize().x / 2.0, Engine::GetWindow().GetSize().y / 4.0 }));
	optionsData[static_cast<int>(Options::Quit)].texture.Draw(math::TransformMatrix() * math::TranslateMatrix(math::vec2{ Engine::GetWindow().GetSize().x / 2 - optionsData[static_cast<int>(Options::Level2)].texture.GetSize().x / 2.0, Engine::GetWindow().GetSize().y / 5.0 }));
}

void MainMenu::RenderOption(OptionData& data, bool isHighlighted)
{
	data.texture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(data.text, (isHighlighted == true) ? MainMenu::onColor : MainMenu::offColor, true);
}
