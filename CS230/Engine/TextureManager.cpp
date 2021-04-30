/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TextureManager.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/19/2021
-----------------------------------------------------------------*/
#include "TextureManager.h"
#include "Engine.h"
#include "Texture.h"
#include <doodle/color.hpp>
CS230::Texture* CS230::TextureManager::Load(const std::filesystem::path& filePath)
{
	if(pathToTexture.find(filePath) == pathToTexture.end())
	{
		pathToTexture[filePath] = new Texture(filePath);
	}
	return pathToTexture[filePath];
}

void CS230::TextureManager::Unload()
{
	Engine::GetLogger().LogEvent("Clear Textures!");
	for(std::map<std::filesystem::path, Texture*>::iterator iter = pathToTexture.begin(); iter != pathToTexture.end(); iter++)
	{
		delete iter->second;
	}
	pathToTexture.clear();
}

