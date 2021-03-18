/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Window_Doodle.cpp
Purpose: Interface between doodle and our engine
Project: CS230
Author: Daehyeon Kim
Creation date: 03/16/2021
-----------------------------------------------------------------*/
#include <doodle/window.hpp>
#include "Engine.h"
void on_window_resized(int new_width, int new_height) {
	Engine::GetWindow().Resize(new_width, new_height);
	Engine::GetLogger().LogEvent("Window Resized");
}