//
// Created by Isabela Spinelli on 18/08/2023.
//
#include <random>
#include <SFML/Graphics.hpp>


#include "Headers/Square.hpp"
#include "Headers/Board.hpp"
#include "Headers/GetSquare.hpp"
#include "Headers/BaseConfig.hpp"

Board ::Board() :

//starting game
        gameOver(1),
        //calling our random number generator, making it so
        //that this can happen properly in all devices
        random_engine(random_device())
{
    //making the matrix, aka our game-board
    //adding lines and columns until our board is at desired size
    for(unsigned char a = 0; a < lines; a++)
    {
        for(unsigned b = 0; b < col; b++)
        {
            squares.push_back(Square(b, a));
        }
    }

    restart();
}

bool Board::endEffect()
{
    for(Square& square : squares)
    {
        if(0 < square.getEffectTimer())
        {
            return 0;

        }

    }
    //when all cells are effectless
    return 1;
}

char Board::getGameOver()
{
    return gameOver;
}


unsigned short Board::getFlags()
{
    unsigned short flagTotal = 0;

    //looking for flags, to then count them
    for(Square& square : squares)
    {
        flagTotal += square.getFlagged();

    }

    return flagTotal;
}

//calling show function to show our items in our board!!!!!!!
void Board::draw(sf::RenderWindow &i_window)
{
    //drawing our cells
    sf::RectangleShape squareShape(sf::Vector2f(pixelBySquare -1, pixelBySquare -1));

    //making another object to be able to create our image
    sf::Sprite iconSprite;
    //creating a texture for it and pulling it from its archive
    sf::Texture iconsTexture;

    iconsTexture.loadFromFile("Resources/Images/Icons" + std::to_string(pixelBySquare) + ".png");

    iconSprite.setTexture(iconsTexture);

    //applying it to every square in our board, using loops
    for (unsigned char a = 0; a < col; a++)
    {
        for (unsigned char b = 0; b < lines; b++)
        {
            //positioning our shapes correctly
            squareShape.setPosition(static_cast<float>(pixelBySquare * a), static_cast<float>(pixelBySquare * b));

            //If the current cell is open
            if (1 == getSquare(a, b, squares)->getOpen())
            {
                //getting number of mines adjacent to it
                unsigned char adjacentMines = getSquare(a, b, squares)->getAdjacentMines();

                squareShape.setFillColor(sf::Color(146, 182, 255));

                //drawing the cell
                i_window.draw(squareShape);

                //If the cell has at least one mine around it
                if (0 < adjacentMines)
                {
                    //getting the number corresponding to the icon texture to draw it
                    iconSprite.setPosition(static_cast<float>(pixelBySquare * a), static_cast<float>(pixelBySquare * b));
                    iconSprite.setTextureRect(sf::IntRect(pixelBySquare * adjacentMines, 0, pixelBySquare, pixelBySquare));

                    i_window.draw(iconSprite);
                }
            }
            else //If the cell is still closed
            {
                squareShape.setFillColor(sf::Color(0, 73, 255));

                //changing square colors to match the event happening in game
                //using the mouse as an input font
                if (0 == gameOver)
                {
                    if (1 == getSquare(a, b, squares)->getMouseState())
                    {
                        squareShape.setFillColor(sf::Color(36, 109, 255));
                    }
                    else if (2 == getSquare(a, b, squares)->getMouseState())
                    {
                        squareShape.setFillColor(sf::Color(0, 36, 255));
                    }
                }

                i_window.draw(squareShape);

                //If the square is flagged
                if (1 == getSquare(a, b, squares)->getFlagged())
                {
                    //drawing/showing image of the square with a flag
                    iconSprite.setPosition(static_cast<float>(pixelBySquare * a), static_cast<float>(pixelBySquare * b));
                    iconSprite.setTextureRect(sf::IntRect(0, 0, pixelBySquare, pixelBySquare));
                    i_window.draw(iconSprite);
                }
            }

//Restart the mouse state in each square
            getSquare(a, b, squares)->setMouseState(0);


            //We don't draw the effect if the game is not over or the cell effect timer hasn't yet started.
            if (0 != gameOver && effectDuration > getSquare(a, b, squares)->getEffectTimer())
            {
                //calculating the size of the effect
                unsigned char effectSize = static_cast<unsigned char>(2 * round(0.5f * pixelBySquare * ((effectDuration - getSquare(a, b, squares)->getEffectTimer()) / static_cast<float>(effectDuration))));

                //setting a random duration for the effect timer on each square
                std::uniform_int_distribution<unsigned short> effectDurationDistribution(1, effectDuration - 1);

                //drawing effects based on the shape of the cells of the board
                squareShape.setPosition(floor(pixelBySquare * (0.5f + a) - 0.5f * effectSize), floor(pixelBySquare * (0.5f + b) - 0.5f * effectSize));
                squareShape.setSize(sf::Vector2f(effectSize, effectSize));

                //establishing what color goes on what effect based on the game status
                if (-1 == gameOver)
                {
                    squareShape.setFillColor(sf::Color(255, 36, 0));
                }
                else
                {
                    squareShape.setFillColor(sf::Color(255, 255, 255));
                }

                //making a window for the effect to show up
                i_window.draw(squareShape);

                //We reset the cell shape's size
                squareShape.setSize(sf::Vector2f(pixelBySquare - 1, pixelBySquare - 1));

                //If the effect timer is over
                if (1 == getSquare(a, b, squares)->updateEffectTimer())
                {
                    //starting the effect timer for the adjacent Squares
                    if (0 <= a - 1 && effectDuration == getSquare(a - 1, b, squares)->getEffectTimer())
                    {
                        getSquare(a - 1, b, squares)->setEffectTimer(static_cast<unsigned char>(effectDurationDistribution(random_engine)));
                    }

                    if (0 <= b - 1 && effectDuration == getSquare(a, b - 1, squares)->getEffectTimer())
                    {
                        getSquare(a, b - 1, squares)->setEffectTimer(static_cast<unsigned char>(effectDurationDistribution(random_engine)));
                    }

                    if (col > 1 + a && effectDuration == getSquare(1 + a, b, squares)->getEffectTimer())
                    {
                        getSquare(1 + a, b, squares)->setEffectTimer(static_cast<unsigned char>(effectDurationDistribution(random_engine)));
                    }

                    if (lines > 1 + b && effectDuration == getSquare(a, 1 + b, squares)->getEffectTimer())
                    {
                        getSquare(a, 1 + b, squares)->setEffectTimer(static_cast<unsigned char>(effectDurationDistribution(random_engine)));
                    }
                }
            }
        }
    }
}

void Board::flagSquare(unsigned char i_x, unsigned char i_y)
{
    //making players unable to flag mines after the game is over

    if (0 == gameOver)
    {
        getSquare(i_x, i_y, squares)->flag();
    }
}
//board being created
void Board::openSquare(unsigned char i_x, unsigned char i_y)
{
    //if we open our first Square
    if (0 == firstClick)
    {
        //We declare coordinate distributions
        std::uniform_int_distribution<unsigned short> x_distribution(0, col - 1);
        std::uniform_int_distribution<unsigned short> y_distribution(0, lines - 1);

        firstClick = 1;

        //Then we generate mines
        for (unsigned short a = 0; a < MINES; a++)
        {
            unsigned char mine_x = static_cast<unsigned char>(x_distribution(random_engine));
            unsigned char mine_y = static_cast<unsigned char>(y_distribution(random_engine));

            //checking if the Square the player tried to open is or not mined
            //and if it isn't, we set a mine somewhere else
            if (1 == getSquare(mine_x, mine_y, squares)->getHasMine() || (i_x == mine_x && i_y == mine_y))
            {
                //We try again
                a--;
            }
            else
            {

                getSquare(mine_x, mine_y, squares)->setMine();
            }
        }

        //making each square calculate how many mines surround it, then
        //show the corresponding number
        for (Square& square : squares)
        {
           square.countAdjacentMines(squares);
        }
    }

    //setting cases where cells can't be opened
    if (0 == gameOver && 0 == getSquare(i_x, i_y, squares)->getFlagged())
    {

        if (1 == getSquare(i_x, i_y, squares)->open(squares))
        {
            //setting game status to -1, game over in case player opens a mine
            gameOver = -1;
        }
        else
        {
            //seeing how many more squares are closed so that we can detect
            //when the player wins
            unsigned short totalClosedSquares = 0;


            for (Square& square : squares)
            {
                totalClosedSquares += 1 - square.getOpen();
            }

            //establishing condition for victory
            if (MINES == totalClosedSquares)
            {
                //change the game over status to one, which means a win
                gameOver = 1;

                //setting winning effect
                getSquare(i_x, i_y, squares)->setEffectTimer(effectDuration - 1);
            }
        }
    }
}

//Establishing conditions and enabling for the game to be played again
void Board::restart()
{
    //If gameOver status != 0,
    //meaning, game is no longer active
    if (0 != gameOver)
    {
        firstClick = 0;

        gameOver = 0;

        for (Square& square : squares)
        {
            square.reset();
        }
    }
}

//Since we can't call the cell's function directly, we must use this function
void Board::setMouseState(unsigned char i_mouse_state, unsigned char i_x, unsigned char i_y)
{

    getSquare(i_x, i_y, squares)->setMouseState(i_mouse_state);
}








