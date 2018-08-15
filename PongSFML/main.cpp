#include <SFML/Graphics.hpp>

#include <iostream>

#include "Object.h"
#include "Paddle.h"
#include "Ball.h"
#include "Screen.h"

const int width = 800;
const int height = 600;
sf::Time deltaTime;

int main() {
	sf::RenderWindow window(sf::VideoMode(width,height), "Pong!");


	sf::Font font;
	std::string string = R"(C:\Windows\Fonts\arial.ttf)";
	std::cout << string << std::endl;
	if (!font.loadFromFile(string)) {
		std::cin.get();
		return EXIT_FAILURE;
	}

	Ball ball;
	ball.size = vec2(5,5);
	ball.position = vec2(width/2, height/2);
	ball.velocity = vec2(-300,-200);

	std::cout << ball.position.x << std::endl;

	Paddle paddle1, paddle2;
	const float paddleMoveVelocity = 400;
	paddle1.size = vec2(5,20);
	paddle1.position = vec2(100,300);
	paddle2.size = vec2(5,20);
	paddle2.position = vec2(700,300);

	Screen screen;
	screen.size = vec2(width/2, height/2);
	screen.size.x += 2.0f * ball.size.x; // hide the ball behind the screen when scoring
	screen.position = vec2(width/2, height/2);
	screen.paddle1Score = 0;
	screen.paddle2Score = 0;

	// intersections
	paddle1.collideObjects.push_back(&screen);
	paddle2.collideObjects.push_back(&screen);

	ball.collideObjects.push_back(&paddle2);
	ball.collideObjects.push_back(&screen);
	ball.collideObjects.push_back(&paddle1);


	sf::Clock clock;
	while (window.isOpen()) {
		deltaTime = clock.getElapsedTime();
		clock.restart();

		// Gather All Events
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		// Apply Movement & Physics
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			paddle1.newPosVector += deltaTime.asSeconds() * vec2(0,-paddleMoveVelocity);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			paddle1.newPosVector += deltaTime.asSeconds() * vec2(0,paddleMoveVelocity);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			paddle2.newPosVector += deltaTime.asSeconds() * vec2(0,-paddleMoveVelocity);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			paddle2.newPosVector += deltaTime.asSeconds() * vec2(0,paddleMoveVelocity);
		}

		bool isColliding = false;
		isColliding |= paddle1.processCollisions();
		isColliding |= paddle2.processCollisions();

		ball.newPosVector += deltaTime.asSeconds() * ball.velocity;
		isColliding |= ball.processCollisions();


		// Draw Everything
		window.clear();

		//std::string collidingText = "Colliding : ";
		//collidingText += isColliding ? "True" : "False";
		std::string collidingText = isColliding ? "Pong!" : "";
		sf::Text collidingSFText(collidingText, font, 12);
		collidingSFText.setPosition(100,100);
		window.draw(collidingSFText);

		sf::Text paddle1Score(std::to_string(screen.paddle1Score), font, 48);
		sf::Text paddle2Score(std::to_string(screen.paddle2Score), font, 48);
		paddle1Score.setPosition(267,100);
		paddle2Score.setPosition(533,100);
		window.draw(paddle1Score);
		window.draw(paddle2Score);


		window.draw(ball);
		window.draw(paddle1);
		window.draw(paddle2);
		//window.draw(screen);

		// draw center line
		for(int y = 50; y < (height - 50); y += 40) {
			sf::VertexArray lines(sf::Lines, 2);
			lines[0].position = vec2(width/2.0f, y);
			lines[1].position = vec2(width/2.0f, y+20);
			window.draw(lines);
		}
		window.display();
	}

	return EXIT_SUCCESS;
}