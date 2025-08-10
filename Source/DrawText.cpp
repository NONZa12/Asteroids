#include <SFML/Graphics.hpp>
#include <iostream>

#include "Headers/Drawtext.hpp"

void draw_text(const std::string& i_text, sf::RenderWindow& i_window)
{
	sf::Font pixelzone;
	if (!pixelzone.openFromFile("Source/Resources/Fonts/Pixelzone.ttf"))
	{
		std::cerr << "Error loading pixelzone font" << std::endl;
	}

	sf::Text text(pixelzone, i_text);

	text.setCharacterSize(30);
	text.setStyle(sf::Text::Regular);
	text.setFillColor(sf::Color::White);

	i_window.draw(text);
}