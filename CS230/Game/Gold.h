/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Gold.h
Project: CS230
Author: Daehyeon Kim
Creation date: 06/04/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Texture.h" 
#include "..\Engine\Component.h" 

enum class Fonts;

class Gold : public CS230::Component {
public:
    Gold(int startingGold, Fonts fontToUse);
    void UpdateGold(int gold);
    unsigned int GetGold() { return gold; }
    void Draw(math::ivec2 location);
private:
    void RenderText();

    Fonts fontToUse;
    unsigned int gold;
    CS230::Texture goldTexture;
};