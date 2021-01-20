#include "Player.h"



Player::Player(sf::Texture& t_player)
{
	this->sprite.setTexture(t_player);
	this->sprite.setScale(sf::Vector2f(0.4, 0.4));
	this->sprite.setPosition(sf::Vector2f(635.f, 490.f));
	this->velocity = sf::Vector2f(sf::Vector2f(0, 0));
	this->moveSpeed = 10.f;
	this->shootTimer = 20;
	this->alive = true;
}

Player::Player(int x, int y, float moveSpeed,sf::Texture &t_player)
{
	this->sprite.setTexture(t_player);
	this->sprite.setScale(sf::Vector2f(0.4, 0.4));
	this->sprite.setPosition(sf::Vector2f(x, y));
	this->velocity = sf::Vector2f(sf::Vector2f(0, 0));
	this->moveSpeed = moveSpeed;
	this->shootTimer = 20;
	this->alive = true;
}

bool Player::isAlive() {
	return this->alive;
}
void Player::setAlive(bool b) {
	this->alive = b;
}

void Player::updatePlayer(sf::Sound &s)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !this->sprite.getGlobalBounds().intersects(this->walls[0].getGlobalBounds()))
		this->moveright();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !this->sprite.getGlobalBounds().intersects(this->walls[1].getGlobalBounds()))
		this->moveleft();
	else
		velocity.x = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !this->sprite.getGlobalBounds().intersects(this->walls[2].getGlobalBounds()))
		this->moveUp();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !this->sprite.getGlobalBounds().intersects(this->walls[3].getGlobalBounds()))
		this->moveDown();
	else
		this->velocity.y = 0;

	if (this->shootTimer < 20)
		++this->shootTimer;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (shootTimer == 20) {
			s.play();
			this->shoot();
			shootTimer = 0;
		}
	}
	
	auto it = missiles.begin();
	while(it != missiles.end())
	{
		it->getSprite().move(it->getVel());
		if (it->getSprite().getPosition().y <= 0)
		{
			it = missiles.erase(it);
		}
		else
			++it;
	}
	sprite.move(velocity);
}


sf::Sprite Player::getSprite() 
{
	return this->sprite;
}
void Player::moveright()
{
	this->velocity.x = this->moveSpeed;
}

void Player::moveleft()
{
	this->velocity.x = -this->moveSpeed;
}

void Player::moveDown()
{
	this->velocity.y = this->moveSpeed;
}

void Player::moveUp()
{
	this->velocity.y = -this->moveSpeed;
}
void Player::shoot() 
{
	this->missiles.push_back(Laser(sf::Vector2f(this->sprite.getPosition().x + this->sprite.getTexture()->getSize().x*0.4/2, this->sprite.getPosition().y - 30)));
}


float Player::getmoveSpeed()
{
	return this->moveSpeed;
}

void Player::setWalls(const sf::RectangleShape walls[4]) 
{
	for (int i = 0; i < 4; i++) {
		this->walls[i] = walls[i];
	}
}

std::list<Laser> &Player::getMissiles() 
{
	return this->missiles;
}

Player::~Player()
{
}
