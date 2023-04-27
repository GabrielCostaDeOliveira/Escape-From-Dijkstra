#include "../include/Header.hpp"


Header::Header(){

    if (!font.loadFromFile("./media/arial.ttf"))
       std::cout << "Não foi possível carregar a fonte arial";

    text.setFont(font); // font is a sf::Font;

    // set the string to display
    text.setString("0 mortes");

    // set the character size
    text.setCharacterSize(15); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::White);

    // set the text style
    //text.setStyle(sf::Text::Bold | sf::Text::Underlined);

}
