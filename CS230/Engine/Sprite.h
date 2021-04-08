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
#include "Vec2.h"
#include "Texture.h"

namespace CS230 {
    class Sprite {
    public:
        Sprite();
        void Load(const std::filesystem::path& texturePath, std::initializer_list<math::ivec2> hotspots);
        void Draw(math::TransformMatrix displayMatrix);
        math::ivec2 GetTextureSize();
        math::ivec2 GetHotSpot(int index);
    private:
        Texture texture;
        std::vector<math::ivec2> hotSpotList;
    };
}
