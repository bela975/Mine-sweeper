//
// Created by Isabela Spinelli on 18/08/2023.
//
#include <vector>

#include "Headers/Square.hpp"
#include "Headers/GetSquare.hpp"
#include "Headers/BaseConfig.hpp"

//establishing a pointer be able to navigate our board and look for specific squares
Square* getSquare(unsigned char i_x, unsigned char i_y, std::vector<Square>& i_square)
{
    return &i_square[i_x + col * i_y];
}