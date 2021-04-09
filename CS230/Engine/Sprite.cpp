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
#include "TransformMatrix.h"
#include "../Engine/Engine.h"
CS230::Sprite::Sprite()
= default;


void CS230::Sprite::Load(const std::filesystem::path& texturePath, std::initializer_list<math::ivec2> hotspots)
{
	texture.Load(texturePath);
	hotSpotList = hotspots;
}

void CS230::Sprite::Draw(math::TransformMatrix displayMatrix) {
	texture.Draw(displayMatrix * math::TranslateMatrix(-GetHotSpot(0)));
}

math::ivec2 CS230::Sprite::GetTextureSize()
{
	return texture.GetSize();
}

math::ivec2 CS230::Sprite::GetHotSpot(int index)
{
	if(static_cast<size_t>(index) >= hotSpotList.size())
	{
		Engine::GetLogger().LogError("Error: No hotspot in that index!");
	}
	return hotSpotList[index];
}
