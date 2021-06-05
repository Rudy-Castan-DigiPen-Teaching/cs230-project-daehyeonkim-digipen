/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Background.h
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"
#include "../Engine/Camera.h"
#include "../Engine/Texture.h"
#include "../Engine/TransformMatrix.h"
#include "Background.h"

void Background::Add(const std::filesystem::path& texturePath, int level) {
    backgrounds.push_back({ Engine::GetTextureManager().Load(texturePath), level });
}

math::ivec2 Background::Size() {
    for (ParallaxInfo& levelInfo : backgrounds) {
        if (levelInfo.level == 1) {
            return levelInfo.texturePtr->GetSize();
        }
    }
    return { 0,0 };
}

void Background::Unload() {
    backgrounds.clear();
}

void Background::Draw(const CS230::Camera &camera) {
    for (ParallaxInfo& levelInfo : backgrounds) {
        levelInfo.texturePtr->Draw(math::TranslateMatrix(-math::vec2{ camera.GetPosition().x / levelInfo.level, camera.GetPosition().y }));
    }
}

void Background::Draw(math::ivec2 initPos) {
    for (ParallaxInfo& levelInfo : backgrounds) {
        levelInfo.texturePtr->Draw(math::TranslateMatrix(initPos));
    }
}