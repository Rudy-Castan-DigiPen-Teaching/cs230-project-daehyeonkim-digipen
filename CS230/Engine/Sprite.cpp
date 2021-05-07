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
#include "Collision.h"
#include "GameObject.h"
#include "TransformMatrix.h"
#include "../Engine/Engine.h"
CS230::Sprite::Sprite(const std::filesystem::path& spriteInfoFile, GameObject* object)
{
	Load(spriteInfoFile, object);
}

CS230::Sprite::~Sprite() {
	for (Animation* anim : animations) {
		delete anim;
	}
	animations.clear();
}

void CS230::Sprite::Load(const std::filesystem::path & spriteInfoFile, GameObject* object) {
	hotSpotList.clear();
	frameTexel.clear();

	if (spriteInfoFile.extension() != ".spt") {
		throw std::runtime_error("Bad Filetype.  " + spriteInfoFile.generic_string() + " not a sprite info file (.spt)");
	}
	std::ifstream inFile(spriteInfoFile);

	if (inFile.is_open() == false) {
		throw std::runtime_error("Failed to load " + spriteInfoFile.generic_string());
	}

	std::string text;
	inFile >> text;
	texturePtr = Engine::GetTextureManager().Load(text);
	frameSize = texturePtr->GetSize();

	inFile >> text;
	while (inFile.eof() == false) {
		if (text == "FrameSize") {
			inFile >> frameSize.x;
			inFile >> frameSize.y;
		}
		else if (text == "NumFrames") {
			int numFrames;
			inFile >> numFrames;
			for (int i = 0; i < numFrames; i++) {
				frameTexel.push_back({ frameSize.x * i, 0 });
			}
		}
		else if (text == "Frame") {
			int frameLocationX, frameLocationY;
			inFile >> frameLocationX;
			inFile >> frameLocationY;
			frameTexel.push_back({ frameLocationX, frameLocationY });
		}
		else if (text == "HotSpot") {
			int hotSpotX, hotSpotY;
			inFile >> hotSpotX;
			inFile >> hotSpotY;
			hotSpotList.push_back({ hotSpotX, hotSpotY });
		}
		else if (text == "Anim")
		{
			std::filesystem::path path;
			inFile >> path;
			
			animations.push_back(new Animation(path));
		}
		else if (text == "CollisionRect") 
		{
			math::irect2 rect;
			inFile >> rect.point1.x >> rect.point1.y >> rect.point2.x >> rect.point2.y;
			if (object == nullptr) {
				Engine::GetLogger().LogError("Trying to add collision to a nullobject");
			}
			else {
				object->AddGOComponent(new RectCollision(rect, object));
			}
		}
		else if (text == "CollisionCircle") 
		{
			double radius;
			inFile >> radius;
			if (object == nullptr) {
				Engine::GetLogger().LogError("Trying to add collision to a nullobject");
			}
			else {
				object->AddGOComponent(new CircleCollision(radius, object));
			}
		}
		else 
		{
			Engine::GetLogger().LogError("Unknown spt command " + text);
		}
		inFile >> text;
	}
	if (frameTexel.empty() == true) {
		frameTexel.push_back({ 0,0 });
	}
	if (animations.empty() == true)
	{
		animations.push_back(new Animation());
	}
}

void CS230::Sprite::Draw(math::TransformMatrix displayMatrix) {
	texturePtr->Draw(displayMatrix * math::TranslateMatrix(-GetHotSpot(0)), frameTexel[animations[currAnim]->GetDisplayFrame()], frameSize);
}


math::ivec2 CS230::Sprite::GetFrameSize() const
{
	return frameSize;
}

void CS230::Sprite::PlayAnimation(int anim)
{
	if(static_cast<size_t>(anim) >= animations.size())
	{
		Engine::GetLogger().LogError("Error: Animation has nothing for that input!");
		anim = 0;
	}
	currAnim = anim;
	animations[currAnim]->ResetAnimation();
}

void CS230::Sprite::Update(double dt)
{
	animations[currAnim]->Update(dt);
}

bool CS230::Sprite::IsAnimationDone()
{
	return animations[currAnim]->IsAnimationDone() == true;
}

math::ivec2 CS230::Sprite::GetFrameTexel(int frameNum) const
{
	if (static_cast<size_t>(frameNum) >= frameTexel.size())
	{
		return { 0,0 };
	}
	return frameTexel[frameNum];
}

math::ivec2 CS230::Sprite::GetHotSpot(int index)
{
	if(static_cast<size_t>(index) >= hotSpotList.size())
	{
		Engine::GetLogger().LogError("Error: No hotspot in that index!");
		return { 0,0 };
	}
	return hotSpotList[index];
}
