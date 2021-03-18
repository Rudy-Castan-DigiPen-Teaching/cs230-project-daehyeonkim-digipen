/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.h
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once
#include <string>
#include "Vec2.h"
#include "Texture.h"

namespace CS230 {
    class Sprite {
    public:
        Sprite();
        void Load(const std::filesystem::path& texturePath);
        void Load(const std::filesystem::path& texturePath, math::ivec2 hotSpotPosition);
        void Draw(math::vec2 position);
        math::ivec2 GetTextureSize();
    private:
        Texture texture;
        math::ivec2 hotSpot;
    };
}
