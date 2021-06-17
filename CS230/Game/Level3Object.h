/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level3Object.h
Project: CS230
Author: Daehyeon Kim
Creation date: 06/05/2021
-----------------------------------------------------------------*/
#pragma once
#include "../Engine/GameObject.h"
class Level3Object : public CS230::GameObject
{
private:
	int hp;
	int identityCode;
	math::vec2 HPBarScale;
public:
	Level3Object(math::vec2 initPos, int hp, math::vec2 HPBarScale, int identityCode);
	void Draw(math::TransformMatrix displayMatrix) override;
	void UpdateHP(int _hp);
	int GetHP();
	bool isDead();
	int GetIdentityID() const { return identityCode; }
};
