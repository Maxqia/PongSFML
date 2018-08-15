#include <SFML/Graphics.hpp>

#include <iostream>

#include "Object.h"

const int width = 800;
const int height = 600;

int main() {
	sf::RenderWindow window(sf::VideoMode(width,height), "Pong!");


	sf::Font font;
	std::string string = R"(C:\Windows\Fonts\arial.ttf)";
	std::cout << string << std::endl;
	if (!font.loadFromFile(string)) {
		std::cin.get();
		return EXIT_FAILURE;
	}

	Object paddle1, paddle2, ball, screen;

	screen.size = vec2(width/2, height/2);
	screen.position = vec2(width/2, height/2);

	ball.size = vec2(5,5);
	ball.position = vec2(width/2, height/2);
	ball.velocity = vec2(-300,-200);

	std::cout << ball.position.x << std::endl;


	const float paddleMoveVelocity = 400;
	paddle1.size = vec2(5,20);
	paddle1.position = vec2(100,300);
	paddle2.size = vec2(5,20);
	paddle2.position = vec2(700,300);

	sf::Clock clock;
	while (window.isOpen()) {
		sf::Time deltaTime = clock.getElapsedTime();
		clock.restart();

		// Gather All Events
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		// Apply Movement & Physics
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
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
		}*/

		/*float p1int = paddle1.intersectionTest(screen);
		if (p1int < 1.0f) {
			paddle1.position += p1int * paddle1.newPosVector;
		}

		float p2int = paddle1.intersectionTest(screen);
		if (p2int < 1.0f) {
			paddle2.position += p2int * paddle2.newPosVector;
		}*/
		/*paddle1.setYWithinRange(0,height);
		paddle2.setYWithinRange(0,height);

		ball.position += deltaTime.asSeconds() * ball.velocity;

		if (!ball.isWithinYRange(0, height)) {
			ball.velocity.y = -ball.velocity.y;
		}

		if (!ball.isWithinXRange(0, width)) {
			ball.velocity.x = -ball.velocity.x;
		}*/

		bool isColliding = ball.isCollidingWith(paddle1) || ball.isCollidingWith(paddle2);

		/*if (isColliding) {
			ball.velocity.x = -ball.velocity.x;
		}*/

		// Draw Everything
		window.clear();

		std::string collidingText = "Colliding : ";
		collidingText += isColliding ? "True" : "False";
		sf::Text text(collidingText, font, 12);
		text.setPosition(100,100);
		
		window.draw(text);
		window.draw(ball);
		window.draw(paddle1);
		window.draw(paddle2);

		// draw center line
		for(int y = 50; y < (height - 50); y += 40) {
			sf::VertexArray lines(sf::Lines, 2);
			lines[0].position = vec2(width/2, y);
			lines[1].position = vec2(width/2, y+20);
			window.draw(lines);
		}
		window.display();
	}

	return EXIT_SUCCESS;
}