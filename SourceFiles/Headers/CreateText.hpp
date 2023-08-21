//
// Created by Isabela Spinelli on 15/08/2023.
//
#pragma once

#include <string>


//rendering a window for our text using SFML
void createText(bool i_black, unsigned short i_x, unsigned short i_y,
                const std::string& i_text, sf::RenderWindow& i_window);
