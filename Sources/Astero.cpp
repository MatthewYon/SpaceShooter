#include "Astero.h"



Astero::Astero(sf::Texture &t)
{
	this->sprite.setTexture(t);
	this->sprite.setPosition(sf::Vector2f(rand() %1600 + 30, -30));
	this->sprite.setOrigin(sf::Vector2f(this->sprite.getTexture()->getSize().x/2,this->sprite.getTexture()->getSize().y/2));
	this->velocity = sf::Vector2f(0, rand() % 5 + 5);
	this->rotateSpeed = rand() % 4 + 1;
	this->destroy = false;
}


Astero::~Astero()
{
}


void Astero::update() {
	this->sprite.rotate(this->rotateSpeed);
	this->sprite.move(velocity);
}


sf::Sprite & Astero::getSprite() {
	return this->sprite;
}

bool Astero::touch(std::list<Laser> missiles) {
	
	return false;
}
