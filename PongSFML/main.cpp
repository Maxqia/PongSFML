#include <SFML/Graphics.hpp>

#include <iostream>

#include "Object.h"
#include "Paddle.h"
#include "Ball.h"
#include "Screen.h"

const float paddleMoveVelocity = 400;
//const float paddleMoveVelocity = 12000;

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

	// Setup Objects //
	Ball ball;
	ball.size = vec2(5,5);
	ball.position = vec2(width/2, height/2);
	ball.velocity = vec2(-300,-200);
	//ball.velocity = vec2(-6000,-4000);

	std::cout << ball.position.x << std::endl;

	Paddle paddle1, paddle2;

	paddle1.size = vec2(5,20);
	paddle1.position = vec2(100,300);
	paddle2.size = vec2(5,20);
	paddle2.position = vec2(700,300);

	Object top, bottom;
	top.position = vec2(width/2, (-height)/2);
	top.size = vec2((width/2)+5, (height/2)+20);

	bottom.position = vec2(width/2, (3*height)/2);
	bottom.size = vec2(width/2, (height/2)+20);

	Screen left, right;
	left.position = vec2((-width)/2, height/2);
	left.size = vec2(width/2, height/2);

	right.position = vec2((3 * width)/2, height/2);
	right.size = vec2(width/2, height/2);


	// intersections
	paddle1.collideObjects.push_back(&top);
	paddle1.collideObjects.push_back(&bottom);
	paddle2.collideObjects.push_back(&top);
	paddle2.collideObjects.push_back(&bottom);

	// ball moves too slow and sometimes gets stuck in paddles
	paddle1.collideObjects.push_back(&ball);
	paddle2.collideObjects.push_back(&ball);

	ball.collideObjects.push_back(&paddle2);
	ball.collideObjects.push_back(&paddle1);
	ball.collideObjects.push_back(&top);
	ball.collideObjects.push_back(&bottom);
	ball.collideObjects.push_back(&left);
	ball.collideObjects.push_back(&right);

	// Main Loop //
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

		// Apply Movement & Physics //
		paddle1.velocity = vec2();
		paddle2.velocity = vec2();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			paddle1.velocity = vec2(0,-paddleMoveVelocity);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			paddle1.velocity = vec2(0,paddleMoveVelocity);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			paddle2.velocity = vec2(0,-paddleMoveVelocity);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			paddle2.velocity = vec2(0,paddleMoveVelocity);
		}

		bool isColliding = false;

		// ordering the physics system creates many... "interesting" effects....
		isColliding |= ball.doCollision();
		ball.applyVelocity();

		isColliding |= paddle1.doCollision();
		paddle1.applyVelocity();

		isColliding |= paddle2.doCollision();
		paddle2.applyVelocity();


		// Draw Everything //
		window.clear();

		//std::string collidingText = "Colliding : ";
		//collidingText += isColliding ? "True" : "False";
		std::string collidingText = isColliding ? "Pong!" : "";
		sf::Text collidingSFText(collidingText, font, 12);
		collidingSFText.setPosition(100,100);
		window.draw(collidingSFText);

		sf::Text paddle1Score(std::to_string(left.paddleScore), font, 48);
		sf::Text paddle2Score(std::to_string(right.paddleScore), font, 48);
		paddle1Score.setPosition(533,100);
		paddle2Score.setPosition(267,100);
		window.draw(paddle1Score);
		window.draw(paddle2Score);

		window.draw(ball);
		window.draw(paddle1);
		window.draw(paddle2);

		window.draw(top);
		window.draw(bottom);
		window.draw(left);
		window.draw(right);

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