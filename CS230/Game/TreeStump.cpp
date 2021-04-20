/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: TreeStump.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/15/2021
-----------------------------------------------------------------*/

#include "TreeStump.h"

TreeStump::TreeStump(math::vec2 pos, int size) : GameObject(pos) {
	switch (size) {
	case 1:
		sprite.Load("assets/treeStump1.spt");
		break;
	case 2:
		sprite.Load("assets/treeStump2.spt");
		break;
	case 3:
		sprite.Load("assets/treeStump3.spt");
		break;
	case 5:
		sprite.Load("assets/treeStump5.spt");
		break;
	}
}