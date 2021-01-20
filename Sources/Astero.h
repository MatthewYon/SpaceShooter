#pragma once
#include "Laser.h"
#include <math.h>
#include <list>
class Astero
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f velocity;
	float rotateSpeed;
	bool destroy;
public:
	Astero(sf::Texture &t);
	~Astero();
	sf::Sprite & getSprite();
	bool touch(std::list<Laser> missiles);
	void update();
};

