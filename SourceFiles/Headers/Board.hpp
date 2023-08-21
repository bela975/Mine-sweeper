//
// Created by Isabela Spinelli on 15/08/2023.
//
#pragma once

class Board
{

    bool firstClick;
    char gameOver;

    //setting our random number generator from the c++ standard library
    std::default_random_engine random_engine;

    //setting a random number generator from c++ std lib
    //for if we don't have a device that can generate them
    //differently for each time a piece of data is entered
    std::random_device random_device;

    //Creating a board using vector of vectors
    std::vector<Square> squares;

//initializing public functions
public:
    Board();

    bool endEffect();

    char getGameOver();

    unsigned short getFlags();

    //function responsible for showing our board by
    //rendering a window using SFML.
    void draw(sf::RenderWindow& i_window);

    //functions that establish coordinates structure for
    //2 of our square types
    void flagSquare(unsigned char i_x, unsigned char i_y);
    void openSquare(unsigned char i_x, unsigned char i_y);

    //function that enables the player to play again
    void restart();

    void setMouseState(unsigned char i_mouse_state,
                          unsigned char i_x, unsigned char i_y);
};