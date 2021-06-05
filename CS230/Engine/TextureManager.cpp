/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TextureManager.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/19/2021
-----------------------------------------------------------------*/
#include "Engine.h"
#include "Texture.h"
#include "TextureManager.h"


CS230::Texture* CS230::TextureManager::Load(const std::filesystem::path& filePath) {
    if (pathToTexture.find(filePath) == pathToTexture.end()) {
        pathToTexture[filePath] = new Texture(filePath);
    }
    return pathToTexture[filePath];
}

void CS230::TextureManager::Unload() {
    Engine::GetLogger().LogEvent("Clear Textures");
    for (std::pair<std::filesystem::path, Texture*> pathTexturePair : pathToTexture) {
        delete pathTexturePair.second;
    }
    pathToTexture.clear();
}