#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <list>
#include "Laser.h"

class Player
{
private:
		sf::Sprite sprite;
		sf::Texture textureM;
		sf::Vector2f velocity;
		sf::RectangleShape walls[4];
		std::list<Laser> missiles;
		bool alive;
		int shootTimer;
		float moveSpeed;
		void moveright();
		void moveleft();
		void moveDown();
		void moveUp();
		void shoot();
public:
	Player(sf::Texture &t_player);
	Player(int posx, int posy, float moveSpeed, sf::Texture &t_player);
	bool isAlive();
	void setAlive(bool);
	float getmoveSpeed();
	sf::Sprite getSprite();
	void setWalls(const sf::RectangleShape walls[4]);
	void updatePlayer(sf::Sound &);
	std::list<Laser> & getMissiles();
	~Player();
};

