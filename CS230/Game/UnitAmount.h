/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: UnitAmount.h
Project: CS230
Author: Daehyeon Kim
Creation date: 06/17/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Texture.h" 
#include "..\Engine\Component.h" 

enum class Fonts;

class UnitAmount : public CS230::Component {
public:
    UnitAmount(int playerUnitAmount, int enemyUnitAmount,  Fonts fontToUse);
    void UpdateUnitAmount(int playerUpdate, int enemyUpdate);
    int GetPlayerUnitAmount() { return playerUnitAmount; }
    int GetEnemyUnitAmount() { return enemyUnitAmount; }
    void Draw(math::ivec2 location);
	static constexpr int unitLimit = 20;
private:
    void RenderText();

    Fonts fontToUse;
    int playerUnitAmount;
    int enemyUnitAmount;
    CS230::Texture playerUnitAmountTexture;
    CS230::Texture enemyUnitAmountTexture;
};