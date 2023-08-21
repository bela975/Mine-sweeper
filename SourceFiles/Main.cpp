//
// Created by Isabela Spinelli on 18/08/2023.
//
#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>

#include "Headers/BaseConfig.hpp"
#include "Headers/CreateText.hpp"
#include "Headers/Square.hpp"
#include "Headers/GetSquare.hpp"
#include "Headers/Board.hpp"

int main()
{
    //Used to make the game work well no matter the framerate chosen
    unsigned lag = 0;

    //adjusting animation states of our emoji face
    //0) Idle
    //1) Opening a square
    //2) game over, and you lost
    //3) game over and you won!
    unsigned char emojiState = 0;

    //represents a point in time.
    //stores a value indicating the time interval from the start of the Clock's epoch
    //to a certain point.
    std::chrono::time_point<std::chrono::steady_clock> previous_time;

    //SFML to store the game events
    sf::Event event;

    //using SFML to render our game window
    sf::RenderWindow window(sf::VideoMode( * col * resizeCam, resizeCam * (fontHeight + PixelBySquare * col)),
                            "Minesweeper", sf::Style::Close);
    //Resizing window
    window.setView(sf::View(sf::FloatRect(0, 0, PixelBySquare * col, fontHeight + PixelBySquare * line)));

    //using SFML to reference a sprite class
    sf::Sprite Emoji;

    //using SFML to reference a Texture class and enable
    //a drawable representation of the EmojiTexture's texture, with all of its properties
    sf::Texture EmojiTexture;
    //Getting the texture from a PNG file
    EmojiTexture.loadFromFile("Resources/Images/Emoji.png");

    //placing emoji in the bottom right corner
    Emoji.setPosition(static_cast<float>(pixelBySquare * col - EmojiTexture.getSize().y), pixelBySquare * line);
    Emoji.setTexture(EmojiTexture);

    //Board object called "board"
    Board board;

    //Get the current time and store it in a variable using std lib
    previousTime = std::chrono::steady_clock::now();

    while (1 == window.isOpen())
    {
        //calculating lag based on time variation between events in game
        unsigned deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previousTime).count();

        //adding the time variation calculated to the lag count
        lag += deltaTime;

        //making sure our game knows time has passed,
        //adding microseconds to the previous time stamp
        // for that we referenced the chrono part of out std lib
        previousTime += std::chrono::microseconds(deltaTime);

        //while lag lasts longer than the current frame duration
        while (FrameDuration <= lag)
        {
            //We get the coordinates of the cell under the cursor
            unsigned char mouseCellX = std::clamp(static_cast<int>(floor(sf::Mouse::getPosition(window).x / static_cast<float>
            (PixelBySquare * resizeCam))), 0, col - 1);
            unsigned char mouseCellY = std::clamp(static_cast<int>(floor(sf::Mouse::getPosition(window).y / static_cast<float>
            (PixelBySquare * resizeCam))), 0, line - 1);


            lag -= FrameDuration;

            //creating a switch case to manage user interactions/events and
            //assign adequate responses to each event type
            while (1 == window.pollEvent(event))
            {
                switch (event.type)
                {

                    case sf::Event::Closed:
                    {

                        window.close();

                        break;
                    }
                    case sf::Event::KeyReleased:
                    {
                        switch (event.key.code)
                        {
                            case sf::Keyboard::Enter:
                            {

                                board.restart();
                            }
                        }

                        break;
                    }
                    case sf::Event::MouseButtonReleased:
                    {
                        switch (event.mouseButton.button)
                        {
                            //setting opening a square mechanism
                            case sf::Mouse::Left:
                            {
                                //We open the square under the cursor
                                board.openSquare(mouseCellX, mouseCellY);

                                break;
                            }
                                //setting flagging mechanism
                            case sf::Mouse::Right:
                            {
                                //We flag the square under the cursor
                                board.flagSquare(mouseCellX, mouseCellY);
                            }
                        }
                    }
                }
            }

            //establishing when each emoji animation state is activated
            if (1 == sf::Mouse::isButtonPressed(sf::Mouse::Left) || 1 == sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                //open mouth emoji when opening a square
                emojiState = 1;

                //We also change the mouse state of the square( let go )
                board.detectMouseState(2, mouseCellX, mouseCellY);
            }
                //Otherwise
            else
            {
                //emoji stays in idle position
                emojiState = 0;

                board.detectMouseState(1, mouseCellX, mouseCellY);
            }

            //If the game is lost
            if (-1 == board.detectGameOver())
            {
                //sad emoji when a bomb is clicked
                emojiState = 2;
            }
                //If you won
            else if (1 == board.detectGameOver())
            {
                //happy emoji is activated
                emojiState = 3;
            }

            //creating and showing the board in game
            if (frameDuration > lag)
            {
                //First we clear the window
                window.clear();

                //Then we create and show the game field
                board.show(window);

                //if the end effect is activated, display message corresponding
                //to game status, winning or losing
                if (1 == board.endEffect())
                {
                    if (1 == board.detectGameOver())
                    {
                        createText(1, static_cast<unsigned short>(round(0.5f * (pixelsBySquare * col - 8 * fontWidth))), static_cast<unsigned short>(round(0.5f * (pixelsBySquare * line - fontHeight))), "You won! :)", window);
                    }
                    else
                    {
                        createText(1, static_cast<unsigned short>(round(0.5f * (pixelsBySquare * col - 4 * fontWidth))), static_cast<unsigned short>(round(0.5f * (pixelsBySquare * line - 2 * fontHeight))), "GAME\nOVER :(", window);
                    }
                }

                //showing how many mines are left through text
                createText(0, 0, pixelBySquare * line, "Mines left:" + std::to_string(MINES - board.detectFlags()), window);

                //setting mechanism to choose the emoji's expression and
                //the associated texture
                Emoji.setTextureRect(sf::IntRect(emojiState * EmojiTexture.getSize().y, 0, EmojiTexture.getSize().y, EmojiTexture.getSize().y));

                //Finally displaying alexander
                window.show(Emoji);
                window.display();
            }
        }
    }
}