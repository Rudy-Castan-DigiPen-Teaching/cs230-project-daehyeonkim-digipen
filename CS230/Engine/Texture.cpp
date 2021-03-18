
/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Texture.cpp
Purpose: Wrapper class for doodle::Image
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#include <doodle/drawing.hpp>	//draw_image
#include "Texture.h"

CS230::Texture::Texture() {}

void CS230::Texture::Load(const std::filesystem::path& filePath) {
	image = doodle::Image{ filePath };
}

void CS230::Texture::Draw(math::vec2 location) {
	doodle::draw_image(image, location.x, location.y);
}

math::ivec2 CS230::Texture::GetSize()
{
	return {image.GetWidth(), image.GetHeight()};
}