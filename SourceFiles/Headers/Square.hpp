//
// Created by Isabela Spinelli on 15/08/2023.
//
#pragma once

class Square
{
    bool isFlagged;
    bool hasMine;
    bool isOpen;

    unsigned char effectTimer;
    unsigned char adjacentMines;
    unsigned char mouseState;
    unsigned char x;
    unsigned char y;

public:
    Square(unsigned char i_x, unsigned char i_y);

    bool getFlagged();
    bool getHasMine();
    //identify what squares are open
    bool getOpen();
    //identify if a square is open
    bool open(std::vector<Square>& squares);
    bool updateEffectTimer();

    unsigned char getEffectTimer();
    unsigned char getAdjacentMines();
    unsigned char getMouseState();

    void countAdjacentMines(std::vector<Square>& i_squares);
    void flag();
    void reset();
    void setEffectTimer(unsigned char i_effectTimer);
    void setMine();
    void setMouseState(unsigned char i_mouseState);
};