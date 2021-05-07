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
#include "Animation.h"
#include <filesystem>
#include "Component.h"
namespace CS230 {
	class GameObject;
	class Texture;
    class Animation;
}

namespace CS230 {
    class Sprite : public Component {
    public:
        Sprite(const std::filesystem::path& spriteInfoFile, GameObject* object);
        ~Sprite();
        void Load(const std::filesystem::path& spriteInfoFile, GameObject* object);
        void Draw(math::TransformMatrix displayMatrix);
        math::ivec2 GetHotSpot(int index);
        math::ivec2 GetFrameSize() const;
        void PlayAnimation(int anim);
        void Update(double dt) override;
        bool IsAnimationDone();
    private:
        math::ivec2 GetFrameTexel(int frameNum) const;
        Texture* texturePtr;
        math::ivec2 frameSize;
        std::vector<math::ivec2> frameTexel;
        std::vector<math::ivec2> hotSpotList;
        int currAnim;
        std::vector<Animation*> animations;
    };
}
