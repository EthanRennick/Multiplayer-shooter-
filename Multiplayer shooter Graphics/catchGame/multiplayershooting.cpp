// arrays of bullets and arrays of apples with bulletvecelocities array
#include "stdafx.h"

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 
#include <SFML/Audio/SoundBuffer.hpp>
#include<SFML/Audio/Sound.hpp>

int main()
{
	//create Window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Game");

	srand(time(NULL));

	sf::SoundBuffer fireBuffer;
	fireBuffer.loadFromFile("fire.wav");

	sf::Sound fireSound;
	fireSound.setBuffer(fireBuffer);

	sf::SoundBuffer explosionBuffer;
	explosionBuffer.loadFromFile("explosion.wav");
	sf::Sound explodeSound;
	explodeSound.setBuffer(explosionBuffer);


	sf::SoundBuffer musicBuffer;
	musicBuffer.loadFromFile("music.ogg");
	sf::Sound musicSound;
	musicSound.setBuffer(musicBuffer);
	musicSound.play();
	
	sf::Sprite background;
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("background.jfif"));
	{
		// error...
	}
	background.setTexture(backgroundTexture);


	//Multiplayer stuff
	int  health = 3;
	int score = 0;

	int health1 = 3;
	int score1 = 0;

	const int numOfApples = 10;

	//sf::RectangleShape player;
	bool readyToFire = true;
	bool readyToFireTwo = true;
	int waitToFireCounter = 10;
	int waitToFireCounterTwo = 10;
	sf::Vector2f playerVelocity{ 0,0 };
	sf::Vector2f playerVelocityTwo{ 0,0 };
	sf::Vector2f playerLookDirection{ 0,-1 };
	sf::Vector2f playerLookDirectionTwo{ 0,-1 };
	const int numBullets = 10;





	sf::RectangleShape onScreenArea;
	onScreenArea.setSize(sf::Vector2f(800, 600));

	sf::RectangleShape bullets[numBullets];
	for (int i = 0; i < numBullets; i++)
	{
		bullets[i].setSize(sf::Vector2f(10, 10));
		bullets[i].setPosition(-2000, -2000);
		bullets[i].setFillColor(sf::Color::Yellow);
	}

	sf::Vector2f bulletVelocities[numBullets];
	for (int i = 0; i < numBullets; i++)
	{
		bulletVelocities[i].x = 0;
		bulletVelocities[i].y = 0;


	}


	sf::RectangleShape bulletsTwo[numBullets];
	for (int i = 0; i < numBullets; i++)
	{
		bulletsTwo[i].setSize(sf::Vector2f(10, 10));
		bulletsTwo[i].setPosition(-2000, -2000);
		bulletsTwo[i].setFillColor(sf::Color::Yellow);
	}

	sf::Vector2f bulletVelocitiesTwo[numBullets];
	for (int i = 0; i < numBullets; i++)
	{
		bulletVelocitiesTwo[i].x = 0;
		bulletVelocitiesTwo[i].y = 0;


	}


	sf::Texture appleTexture;
	sf::Sprite apples[numOfApples];
	if (!appleTexture.loadFromFile("mace one.png"));
	{
		// error...
	}
	for (int i = 0; i < numOfApples; i++)
	{
		float randomX = rand() % 800;
		float randomY = rand() % 600;
		apples[i].setTexture(appleTexture);
		apples[i].setPosition(randomX, randomY);
	}

	sf::Texture appleTextureTwo;
	sf::Sprite applesTwo[numOfApples];
	if (!appleTextureTwo.loadFromFile("mace two.png"));
	{
		// error...
	}
	for (int i = 0; i < numOfApples; i++)
	{
		float randomX = rand() % 800;
		float randomY = rand() % 600;
		applesTwo[i].setTexture(appleTextureTwo);
		applesTwo[i].setPosition(randomX, randomY);
	}

	/*player.setSize(sf::Vector2f(20, 20));
	player.setFillColor(sf::Color::Red);
	player.setPosition(rand() % 780, rand() % 580);*/

	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	if (!playerTexture.loadFromFile("buffalo.png"))
	{
		// error...
	}
	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(200, window.getSize().y - playerSprite.getGlobalBounds().height);

	sf::Texture playerTwoTexture;
	sf::Sprite playerTwoSprite;
	if (!playerTwoTexture.loadFromFile("moose.png"))
	{
		// error...
	}
	playerTwoSprite.setTexture(playerTwoTexture);
	playerTwoSprite.setPosition(400, window.getSize().y - playerSprite.getGlobalBounds().height);


	playerSprite.setOrigin(40, 33);
	playerTwoSprite.setOrigin(50, 40);



	//ttext stuff
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);

	sf::Text scoreTextTwo;
	scoreTextTwo.setFont(font);
	scoreTextTwo.setPosition(690, 0);
	scoreTextTwo.setString("Score: " + std::to_string(score));
	scoreTextTwo.setCharacterSize(24);
	scoreTextTwo.setFillColor(sf::Color::White);

	sf::Text healthText;
	healthText.setFont(font);
	healthText.setPosition(0, 26);
	healthText.setString("Health: " + std::to_string(health));
	healthText.setCharacterSize(24);
	healthText.setFillColor(sf::Color::White);


	sf::Text healthTextTwo;
	healthTextTwo.setFont(font);
	healthTextTwo.setPosition(690, 26);
	healthTextTwo.setString("Health: " + std::to_string(health));
	healthTextTwo.setCharacterSize(24);
	healthTextTwo.setFillColor(sf::Color::White);

	// set timePerFrame to 1 60th of a second. 60 frames per second
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	// the clock object keeps the time.
	sf::Clock clock;
	clock.restart();

	while (window.isOpen())
	{
		// check if the close window button is clicked on.
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//add to the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a secound
		//only when the time since last update is greater than 1/60 update the world.

		if (timeSinceLastUpdate > timePerFrame)
		{

			playerVelocity.x = 0;
			playerVelocity.y = 0;

			playerVelocityTwo.x = 0;
			playerVelocityTwo.y = 0;


			// get keyboard input.
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				playerVelocity.x = -5;
				playerSprite.setRotation(90);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				playerVelocity.x = 5;
				playerSprite.setRotation(-90);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				playerVelocity.y = -5;
				playerSprite.setRotation(0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				playerVelocity.y = 5;
				playerSprite.setRotation(180);
			}
			if (playerVelocity.x != 0 || playerVelocity.y != 0)
			{
				playerLookDirection = playerVelocity;
			}
			// get keyboard input.
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				playerVelocityTwo.x = -5;
				playerTwoSprite.setRotation(90);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				playerVelocityTwo.x = 5;
				playerTwoSprite.setRotation(-90);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				playerVelocityTwo.y = -5;
				playerTwoSprite.setRotation(0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				playerVelocityTwo.y = 5;
				playerTwoSprite.setRotation(180);
			}
			if (playerVelocityTwo.x != 0 || playerVelocityTwo.y != 0)
			{
				playerLookDirectionTwo = playerVelocityTwo;
			}

			playerSprite.move(playerVelocity);
			playerTwoSprite.move(playerVelocityTwo);

			for (int i = 0; i < numBullets; i++)
			{
				if (bullets[i].getPosition().x != -2000)
				{
					bullets[i].move(bulletVelocities[i]);
					if (onScreenArea.getGlobalBounds().intersects(bullets[i].getGlobalBounds()) == 0)
					{
						bullets[i].setPosition(-2000, -2000);
						bulletVelocities[i].x = 0;
						bulletVelocities[i].y = 0;
					}
				}
			}
			if (readyToFire)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					for (int i = 0; i < numBullets; i++)
					{
						if (bullets[i].getPosition().x == -2000)
						{
							bullets[i].setPosition(playerSprite.getPosition());
							bulletVelocities[i] = playerLookDirection;
							//when the player shoots a bullet

							fireSound.play();

							bulletVelocities[i].x *= 2;
							bulletVelocities[i].y *= 2;
							readyToFire = false;
							waitToFireCounter = 10;
							break;
						}

					}
				}
			}
			else {
				waitToFireCounter--;
				if (waitToFireCounter <= 0)
				{
					readyToFire = true;
				}
			}
			for (int i = 0; i < numBullets; i++)
			{
				if (bulletsTwo[i].getPosition().x != -2000)
				{
					bulletsTwo[i].move(bulletVelocitiesTwo[i]);
					if (onScreenArea.getGlobalBounds().intersects(bulletsTwo[i].getGlobalBounds()) == 0)
					{
						bulletsTwo[i].setPosition(-2000, -2000);
						bulletVelocitiesTwo[i].x = 0;
						bulletVelocitiesTwo[i].y = 0;
					}
				}
			}
			if (readyToFireTwo)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				{
					for (int i = 0; i < numBullets; i++)
					{
						if (bulletsTwo[i].getPosition().x == -2000)
						{
							bulletsTwo[i].setPosition(playerTwoSprite.getPosition());
							bulletVelocitiesTwo[i] = playerLookDirectionTwo;
							//when the player shoots a bullet

							fireSound.play();

							bulletVelocitiesTwo[i].x *= 2;
							bulletVelocitiesTwo[i].y *= 2;
							readyToFireTwo = false;
							waitToFireCounterTwo = 10;
							break;
						}

					}
				}
			}
			else {
				waitToFireCounterTwo--;
				if (waitToFireCounterTwo <= 0)
				{
					readyToFireTwo = true;
				}
			}


			for (int i = 0; i < numOfApples; i++)
			{
				if (apples[i].getPosition().x != -1000)
				{
					apples[i].move(rand() % 7 - 3, rand() % 7 - 3);
				}
			}

			for (int i = 0; i < numOfApples; i++)
			{
				if (applesTwo[i].getPosition().x != -1000)
				{
					applesTwo[i].move(rand() % 7 - 3, rand() % 7 - 3);
				}
			}

			//collision detection
			for (int appleIndex = 0; appleIndex < numOfApples; appleIndex++)
			{
				if (apples[appleIndex].getGlobalBounds().intersects(playerSprite.getGlobalBounds()))
				{
					health--;
					apples[appleIndex].setPosition(-1000, -1000);
					if (health < 0)
					{
						playerSprite.setPosition(-600, -600);
					}
				}
				if (apples[appleIndex].getGlobalBounds().intersects(playerTwoSprite.getGlobalBounds()))
				{
					health1--;
					apples[appleIndex].setPosition(-1000, -1000);
					if (health1 < 0)
					{
						playerSprite.setPosition(-600, -600);
					}
				}
				for (int bulletIndex = 0; bulletIndex < numBullets; bulletIndex++)
				{
					if (apples[appleIndex].getGlobalBounds().intersects(bullets[bulletIndex].getGlobalBounds()))
					{
						explodeSound.play();
						score++;
						bullets[bulletIndex].setPosition(-2000, -2000);
						bulletVelocities[bulletIndex].x = 0;
						bulletVelocities[bulletIndex].y = 0;
						apples[appleIndex].setPosition(-1000, -1000);
						if (score == 6)
						{
							playerTwoSprite.setPosition(-2000, -2000);
						}
					}
				}
			}
			//collision detection
			for (int appleIndex = 0; appleIndex < numOfApples; appleIndex++)
			{
				if (applesTwo[appleIndex].getGlobalBounds().intersects(playerTwoSprite.getGlobalBounds()))
				{
					applesTwo[appleIndex].setPosition(-1000, -1000);
					health1--;
					if (health1 < 0)
					{
						playerTwoSprite.setPosition(-600, -600);
					}
				}
				if (applesTwo[appleIndex].getGlobalBounds().intersects(playerSprite.getGlobalBounds()))
				{
					applesTwo[appleIndex].setPosition(-1000, -1000);
					health--;
					if (health < 0)
					{
						playerSprite.setPosition(-600, -600);
					}
				}
				for (int bulletIndex = 0; bulletIndex < numBullets; bulletIndex++)
				{
					if (applesTwo[appleIndex].getGlobalBounds().intersects(bulletsTwo[bulletIndex].getGlobalBounds()))
					{
						explodeSound.play();
						score1++;
						bulletsTwo[bulletIndex].setPosition(-2000, -2000);
						bulletVelocitiesTwo[bulletIndex].x = 0;
						bulletVelocitiesTwo[bulletIndex].y = 0;
						applesTwo[appleIndex].setPosition(-1000, -1000);
						if (score1 == 6)
						{
							playerSprite.setPosition(-2000, -2000);
						}
					}
				}


			}

				window.clear();

				window.draw(background);

				scoreText.setString("Score: " + std::to_string(score));
				healthText.setString("Health: " + std::to_string(health));
				scoreTextTwo.setString("Score: " + std::to_string(score1));
				healthTextTwo.setString("Health: " + std::to_string(health1));

				for (int i = 0; i < numOfApples; i++)
				{
					window.draw(apples[i]);
				}
				for (int i = 0; i < numOfApples; i++)
				{
					window.draw(applesTwo[i]);
				}
				for (int i = 0; i < numBullets; i++)
				{
					window.draw(bullets[i]);
				}
				for (int i = 0; i < numBullets; i++)
				{
					window.draw(bulletsTwo[i]);
				}
				window.draw(scoreTextTwo);
				window.draw(healthTextTwo);
				window.draw(scoreText);
				window.draw(healthText);
				window.draw(playerSprite);
				window.draw(playerTwoSprite);
				
				window.display();

				// reset the timeSinceLastUpdate to 0 
				timeSinceLastUpdate = sf::Time::Zero;
			}
		}
	
	

	return 0;
}



