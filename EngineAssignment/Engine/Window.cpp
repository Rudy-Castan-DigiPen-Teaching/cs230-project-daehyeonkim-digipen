/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Window.cpp
Project: CS230
Author: Daehyeon Kim
Creation date: 03/08/2021
-----------------------------------------------------------------*/
#include <doodle/window.hpp>
#include "Window.h"

void CS230::Window::Init(std::string windowName) {
    doodle::create_window(windowName, 1440, 810);
}
void CS230::Window::Update() {
    doodle::update_window();
}