//
// Created by Isabela Spinelli on 15/08/2023.
//

#include <vector>

//including our header archives using their addresses
#include "Headers/Square.hpp"
#include "Headers/GetSquare.hpp"
#include "Headers/BaseConfig.hpp"

Square::Square(unsigned char i_x, unsigned char i_y) :
        adjacentMines(0),
        x(i_x),
        y(i_y)
{
    //using the existent reset function as I am creating an object
    reset();
}

//referencing the function getFlagged() that returns a boolean
//from the header file Square.hpp
bool Square::getFlagged()
{
    //Return whether the cell is flagged or not
    return isFlagged;
}

//referencing the function getHasMine() that returns a boolean
//from the header file Square.hpp
bool Square::getHasMine()
{
    //Return whether the cell has a mine or not
    return hasMine;
}

//referencing the function getOpen() that returns a boolean
//from the header file Square.hpp
bool Square::getOpen()
{
    //Return whether the cell is open or not
    return isOpen;
}

bool Square::open(std::vector<Square>& i_square)
{
    //checking if the square is already open before trying to open it
    if (0 == isOpen)
    {
        isOpen = 1;

        //establishing that all adjacent squares should be automatically opened if:
        //the square has no mine, and is not surrounded by any.
        if (0 == hasMine && 0 == adjacentMines)
        {
            for (char a = -1; a < 2; a++)
            {
                for (char b = -1; b < 2; b++)
                {
                    //making sure we only analyse within the size of our board
                    if ((0 == a && 0 == b) || (0 > a + x || 0 > b + y || col == a + x || lines == b + y))
                    {
                        continue;
                    }

                    //opening all adjacent squares, since they are bomb free
                    getSquare(a + x, b + y, i_square)->open(i_square);
                }
            }
        }

        //running the effect in case the square being analysed has a mine
        effectTimer -= hasMine;

        //Return if the square has a mine or not, using the boolean hasMine
        return hasMine;
    }
    return 0;
}


bool Square::updateEffectTimer()
{
    //Is the effect timer over?
    if (effectTimer > 0)
    {
        //decrement it until it is over
        effectTimer--;

        //
        if (0 == effectTimer)
        {
            //this shows that the timer ended
            return 1;
        }
    }
    return 0;
}

//referencing the function getEffectTimer() from the header file Square.hpp
//to return the effectTimer state, the same will happen down, with other functions.
unsigned char Square::getEffectTimer()
{
    return effectTimer;
}
unsigned char Square::getAdjacentMines()
{
    return adjacentMines;
}

unsigned char Square::getMouseState()
{

    return mouseState;
}

void Square::countAdjacentMines(std::vector<Square>& i_squares)
{
    //We start counting from 0
    adjacentMines = 0;

    //If this cell has a mine, we don't need to check for mines around it
    if (0 == hasMine)
    {
        for (char a = -1; a < 2; a++)
        {
            for (char b = -1; b < 2; b++)
            {
                if ((0 == a && 0 == b) || (0 > a + x || 0 > b + y || col == a + x || lines == b + y))
                {
                    continue;
                }

                //add a mine to the count in case one is present in adjacent position
                if (1 == getSquare(a + x, b + y, i_squares)->getHasMine())
                {
                    adjacentMines++;
                }
            }
        }
    }
}

void Square::flag()
{
    //establishing that an open square can't be flagged
    if (0 == isOpen)
    {
        !isFlagged;
    }
}

void Square::reset()
{
    //Setting square related variables to 0
    isFlagged = 0;
    hasMine = 0;
    isOpen= 0;
    mouseState = 0;
    //except the effect
    effectTimer = effectDuration;

}

void Square::setEffectTimer(unsigned char i_effectTimer)
{
    effectTimer= i_effectTimer;

}

void Square::setMine()
{
    hasMine = 1;
}

void Square::setMouseState(unsigned char i_mouseState)
{
    mouseState = i_mouseState;
}