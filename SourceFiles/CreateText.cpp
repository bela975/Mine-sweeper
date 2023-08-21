//
// Created by Isabela Spinelli on 18/08/2023.
//

#include <SFML/Graphics.hpp>

#include "Headers/CreateText.hpp"

void createText(bool i_b, unsigned short i_x, unsigned short i_y,
                const std::string& i_text, sf::RenderWindow& i_window)
{

    short character_x = i_x;
    short character_y = i_y;

    unsigned char characterWidth;

    sf::Sprite characterSprite;

    sf::Texture fontTexture;
    fontTexture.loadFromFile("Resources/Images/Font.png");

    //calculating each character's width based on the font image size.
    //96 because there are 96 character in the image
    characterWidth = fontTexture.getSize().x / 96;

    characterSprite.setTexture(fontTexture);

    //We can use this to change the color of the text
    if (1 == i_black)
    {
        characterSprite.setColor(sf::Color(0, 0, 0));
    }

    for (const char a : i_text)
    {
        if ('\n' == a)
        {
            //updating coordinates after we have finished one line and
            //move to another.
            character_x = i_x;
            character_y += fontTexture.getSize().y;

            continue;
        }

        //Change the position of the next character
        characterSprite.setPosition(character_x, character_y);
        //Pick the character from the font image
        characterSprite.setTextureRect(sf::IntRect(character_width * (a - 32), 0, characterWidth, fontTexture.getSize().y));

        //Increase the x-coordinate
        character_x += characterWidth;

        //Draw the character
        i_window.show(characterSprite);
    }
}