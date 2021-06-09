/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: HPBar.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 06/05/2021
-----------------------------------------------------------------*/
#pragma once
#include "HPBar.h" 
#include "Level3Object.h"
#include "../Engine/Engine.h"
#include "../Engine/TransformMatrix.h"

HPBar::HPBar(int maxHP, math::vec2 scale) : maxHP(maxHP), hp(maxHP), scale(scale)
{
	HPoutline = Engine::GetTextureManager().Load("assets/LEVEL3/HPBar_Outline.png");
	HPfill = Engine::GetTextureManager().Load("assets/LEVEL3/HPBar_Fill.png");
}

void HPBar::UpdateHP(int _hp)
{
	hp += _hp;
	if(hp <= 0)
	{
		hp = 0;
	}
}

void HPBar::Draw(math::TransformMatrix displayMatrix)
{
	math::TransformMatrix barMatrix = displayMatrix  * math::ScaleMatrix(scale);
	math::TransformMatrix barGap = math::TranslateMatrix(math::vec2{ 1,1 });
	HPoutline->Draw(barMatrix);
	HPfill->Draw(barMatrix * math::ScaleMatrix({ static_cast<double>(hp) / maxHP, 1 }) * barGap);
}
