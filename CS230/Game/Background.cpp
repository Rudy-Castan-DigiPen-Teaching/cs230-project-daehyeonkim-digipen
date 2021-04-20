/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Background.cpp
Project: CS230
Author: Dawhyeon Kim
Creation date: 3/30/2021
-----------------------------------------------------------------*/
#include "Background.h"
#include "../Engine/Camera.h"
#include "../Engine/Engine.h"
#include "../Engine/TransformMatrix.h"
void Background::Add(const std::filesystem::path& texturePath, int level)
{
	backgrounds.push_back({ Engine::GetTextureManager().Load(texturePath), level });
}

void Background::Unload()
{
	backgrounds.clear();
}

void Background::Draw(const CS230::Camera& camera)
{
	for(unsigned int i = 0; i < backgrounds.size(); i++)
	{
		backgrounds[i].texturePtr->Draw(math::TranslateMatrix{ math::vec2{-camera.GetPosition().x / backgrounds[i].level, 0} });
	}

}

math::ivec2 Background::Size()
{
	math::ivec2 getSize;
	for(size_t i = 0; i < backgrounds.size(); i++)
	{
		if(backgrounds[i].level == 1)
		{
			getSize = backgrounds[i].texturePtr->GetSize();
			break;
		}
	}
	return getSize;
}
