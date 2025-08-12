#include <SFML/Graphics.hpp>
#include <iostream>

#include "Headers/Drawtext.hpp"

void draw_text(sf::Vector2f i_position, const std::string& i_text, sf::RenderWindow& i_window)
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

	sf::Rect<float> bounds = text.getLocalBounds();
	text.setOrigin({ bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f });

	text.setPosition(i_position);

	i_window.draw(text);
}