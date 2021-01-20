#include "Laser.h"



Laser::Laser(sf::Vector2f pos)
{
	texture.create(3, 30);
	texture.setSmooth(true);
	sf::Uint8* pixels = new sf::Uint8[2 * 30 * 4];
	texture.update(pixels);
	this->sprite.setTexture(texture);
	this->sprite.setColor(sf::Color::Red);
	this->sprite.setPosition(pos);
	this->velocity = sf::Vector2f(0.f, -20.f);
	delete(pixels);
}


Laser::~Laser()
{
}

sf::Sprite &Laser::getSprite() {
	return this->sprite;
}

sf::Vector2f Laser::getVel() {
	return this->velocity;
}
