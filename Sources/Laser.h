#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Laser
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f velocity;

public:
	Laser(sf::Vector2f pos);
	~Laser();
	sf::Sprite &getSprite();
	sf::Vector2f getVel();
};

