/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 03/16/2021
-----------------------------------------------------------------*/
#include "Sprite.h"

CS230::Sprite::Sprite()
= default;

void CS230::Sprite::Load(const std::filesystem::path& texturePath)
{
	texture.Load(texturePath);
	hotSpot = { texture.GetSize()/2};
}

void CS230::Sprite::Load(const std::filesystem::path& texturePath, math::ivec2 hotSpotPosition)
{
	texture.Load(texturePath);
	hotSpot = hotSpotPosition;
}

void CS230::Sprite::Draw(math::vec2 position)
{
	texture.Draw(position - hotSpot);
}

math::ivec2 CS230::Sprite::GetTextureSize()
{
	return texture.GetSize();
}
