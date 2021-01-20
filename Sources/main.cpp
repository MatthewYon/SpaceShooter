#include "Player.h"
#include "Astero.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <climits>
#include <time.h>
#include <Windows.h>
#include <random>



int main()
{
	srand(time(NULL));

	//Creating window and event and settings framerateLimit to 60 fps
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Title", sf::Style::Fullscreen, settings);
	sf::Event event;
	window.setFramerateLimit(60);

	sf::Music startMusic;
	sf::Music music;
	sf::Music endMusic;
	sf::SoundBuffer laserSFX;
	sf::SoundBuffer AstExploBuff;
	sf::SoundBuffer PlayerExploBuff;
	if (!startMusic.openFromFile("sounds/Brave Pilots.ogg"))
		std::cout << "Cannot load 'Brave Pilots.ogg'" << std::endl;
	if (!music.openFromFile("sounds/Battle in the Stars.ogg"))
		std::cout << "Cannot load 'Battle in the Stars.ogg'" << std::endl;
	if (!endMusic.openFromFile("sounds/Defeated.ogg"))
		std::cout << "Cannot load 'Defeated.ogg'" << std::endl;
	if (!laserSFX.loadFromFile("sounds/laser.wav"))
		std::cout << "Cannot load 'laser.wav'" << std::endl;
	if (!AstExploBuff.loadFromFile("sounds/AstExplo.wav"))
		std::cout << "Cannot load 'AstExplo.wav'" << std::endl;
	if (!PlayerExploBuff.loadFromFile("sounds/PlayerExplo.wav"))
		std::cout << "Cannot load 'PlayerExplo.wav'" << std::endl;
	
	//Declaring textures;
	sf::Texture t_laser;
	sf::Texture t_player;
	sf::Texture t_background;
	sf::Texture t_ast;
	sf::Texture t_ast_explo;

	//Initiate textures
	if(!t_player.loadFromFile("textures/ship7.png"))
		std::cout << "Cannot load 'ship7.png" << std::endl;

	if(!t_background.loadFromFile("textures/Space.jpg"))
		std::cout << "Cannot load 'Space.jpg" << std::endl;

	if(!t_ast.loadFromFile("textures/asteroid.png"))
		std::cout << "Cannot load 'asteroid.png" << std::endl;

	if(!t_ast_explo.loadFromFile("textures/explosion.png"))
		std::cout << "Cannot load 'explosion.png" << std::endl;

	//Creating font and text to show fps on the screen
	sf::Font font;
	font.loadFromFile("fonts/ArialCE.ttf");

	sf::Text text_FPS("FPS: ", font);
	sf::Text text_score("SCORE: ", font);
	sf::Text text_GameOver("GAME OVER", font);
	sf::Text text_toStart("Press Enter to start !", font);
	text_FPS.setFillColor(sf::Color::White);
	text_FPS.setPosition(sf::Vector2f(10, 30));

	text_score.setFillColor(sf::Color::White);
	text_score.setPosition(sf::Vector2f(1800, 30));

	text_GameOver.setFillColor(sf::Color::White);

	text_toStart.setFillColor(sf::Color::White);
	text_toStart.setPosition(sf::Vector2f((window.getSize().x / 2 - 150), (window.getSize().y / 2 - 100)));


	//Creating Background, player and empty asteroid list
	sf::Sprite background(t_background);
	sf::Clock clock;	
	Player player(t_player);
	std::list<Astero> asteros;

	//Creating Screen Walls
	sf::RectangleShape walls[4];
	walls[0] = sf::RectangleShape(sf::Vector2f(30.f, window.getSize().y));
	walls[0].setPosition(sf::Vector2f(window.getSize().x-30.f, 0.f));
	walls[1] = sf::RectangleShape(sf::Vector2f(30.f, window.getSize().y));
	walls[1].setPosition(sf::Vector2f(0.f, 0.f));
	walls[2] = sf::RectangleShape(sf::Vector2f(window.getSize().x, 30.f));
	walls[2].setPosition(sf::Vector2f(0.f, -30.f));
	walls[3] = sf::RectangleShape(sf::Vector2f(window.getSize().x, 30.f));
	walls[3].setPosition(sf::Vector2f(0.f, window.getSize().y));

	for (int i = 0; i < 4; i++) {
		walls[i].setFillColor(sf::Color::Green);
	}
	player.setWalls(walls);

	//Asteroid CD initial spawning value
	int asteroCD = 200;
	int asteroCurrCD = asteroCD;

	//Average for fps and a counter for the delay
	unsigned int average=0;
	int cpt = 0;

	int score = 0;

	int counterExplosion = 0;

	sf::Sound shoot;
	sf::Sound AstExplo;
	sf::Sound PlayerExplo;
	startMusic.setVolume(5.f);
	startMusic.setLoop(true);
	startMusic.play();
	music.setVolume(5.f);
	music.setLoop(true);
	endMusic.setVolume(5.f);
	endMusic.setLoop(true);
	shoot.setBuffer(laserSFX);
	shoot.setVolume(20.f);
	AstExplo.setBuffer(AstExploBuff);
	AstExplo.setVolume(10.f);
	PlayerExplo.setBuffer(PlayerExploBuff);
	PlayerExplo.setVolume(20.f);
	bool endMusicPlaying = false;
	bool pressKeytoStart = false;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}
		
		

		//Clearing window
		window.clear(sf::Color::White);
		window.draw(background);

		if (!pressKeytoStart) {
			window.draw(text_toStart);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				startMusic.stop();
				music.play();
				pressKeytoStart = true;
			}			
		}
		else if (player.isAlive()) {
			//Spawning Asteroids every asteroCD frame
			if (asteroCurrCD == asteroCD) {
				asteros.push_back(Astero(t_ast));
				asteroCD = rand() % 150 + 50;
				asteroCurrCD = 0;
			}
			++asteroCurrCD;

			//Updating Player
			player.updatePlayer(shoot);

			//Updating asteroids
			auto it = asteros.begin();
			bool isErase = false;

			while (it != asteros.end()) {
				it->update();
				if (it->getSprite().getPosition().y > window.getSize().y) {
					it = asteros.erase(it);
					score -= 5;
				}
				else if (it->getSprite().getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) {
					PlayerExplo.play();
					player.setAlive(false);
					it = asteros.erase(it);
				}
				else
				{
					auto it2 = player.getMissiles().begin();
					while (it2 != player.getMissiles().end())
					{
						if (it->getSprite().getGlobalBounds().intersects(it2->getSprite().getGlobalBounds())) {
							AstExplo.play();
							it2 = player.getMissiles().erase(it2);
							it = asteros.erase(it);
							isErase = true;
							score += 10;
							break;
						}
						else {
							++it2;
						}
					}
					if (!isErase)
						++it;
				}
				isErase = false;
			}

			for (auto it_ast = asteros.begin(); it_ast != asteros.end();++it_ast) {
				window.draw(it_ast->getSprite());
			}

			//Updating Missiles
			for (auto it = player.getMissiles().begin(); it != player.getMissiles().end(); ++it)
			{
				window.draw(it->getSprite());
			}


			//Drawing player
			window.draw(player.getSprite());

			//Display Score
			text_score.setString(std::to_string(score));
			window.draw(text_score);
		}
		else {
			music.stop();
			if (!endMusicPlaying) {
				endMusic.play();
				endMusicPlaying = true;
			}
			text_GameOver.setString("GAME OVER\n\nYour score is : " + std::to_string(score) + "\n\nPress Escape to exit");
			text_GameOver.setPosition(sf::Vector2f((window.getSize().x / 2 - 150), (window.getSize().y / 2 - 100)));
			window.draw(text_GameOver);
		}
		

		//Calculate and display fps
		sf::Time elapsed1 = clock.getElapsedTime();
		average = average + (1 / elapsed1.asSeconds());
		if (cpt == 60) {
			text_FPS.setString("FPS: " + std::to_string(average/60));
			average = 0;
			cpt = 0;
		}
		++cpt;
		clock.restart();
		window.draw(text_FPS);
		window.display();
	}
	return 0;
}