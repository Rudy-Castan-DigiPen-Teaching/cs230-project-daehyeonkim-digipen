/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: HPBar.h
Project: CS230
Author: Daehyeon Kim
Creation date: 06/05/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Texture.h" 
#include "..\Engine\Component.h"

class Level3Object;
enum class Fonts;

class HPBar : public CS230::Component {
public:
    HPBar(int maxHP, math::vec2 scale);
    void UpdateHP(int _hp);
    unsigned int GetHP() { return hp; }
    void Draw(math::TransformMatrix displayMatrix);
private:
    math::vec2 scale;
    unsigned int maxHP;
    unsigned int hp;
    CS230::Texture* HPoutline;
    CS230::Texture* HPfill;
public:
    static constexpr math::vec2 initBarSize{ 52,12 };
};