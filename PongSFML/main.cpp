#include <SFML/Graphics.hpp>

#include <iostream>

#include "Object.h"
#include "Paddle.h"
#include "Ball.h"

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

	Object screen;
	screen.size = vec2(width/2, height/2);
	screen.position = vec2(width/2, height/2);

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

		isColliding |= paddle1.processIntersection(screen);
		isColliding |= paddle2.processIntersection(screen);
		//float p1int = Object::lineIntTest(paddle1.position, paddle1.newPosVector, vec2(0,0), vec2(width,0));
		/*float p1int = paddle1.intersectionTest(screen);
		if (p1int < 1.0f) {
			isColliding |= true;
			paddle1.position += p1int * paddle1.newPosVector;
			paddle1.position += (-1.0f + p1int) * paddle1.newPosVector;
		} else paddle1.position += paddle1.newPosVector;
		paddle1.newPosVector = vec2();*/

		/*float p2int = paddle2.intersectionTest(screen);
		if (p2int < 1.0f) {
			isColliding |= true;
			paddle2.position += p2int * paddle2.newPosVector;
		} else paddle2.position += paddle2.newPosVector;
		paddle2.newPosVector = vec2();*/
		/*paddle1.setYWithinRange(0,height);
		paddle2.setYWithinRange(0,height);*/

		ball.newPosVector += deltaTime.asSeconds() * ball.velocity;

		float intr = ball.intersectionTest(screen, ball.newPosVector);
		float int2 = ball.intersectionTest(paddle1, ball.newPosVector);
		float int3 = ball.intersectionTest(paddle2, ball.newPosVector);
		if (int2 < intr) intr = int2;
		if (int3 < intr) intr = int3;

		if (intr < 1.0f) {
			isColliding |= true;
			ball.position += intr * deltaTime.asSeconds() * ball.velocity;

			// rotate 90 degrees
			ball.velocity = vec2(-ball.velocity.y, ball.velocity.x);
			ball.position += (1.0f - intr) * deltaTime.asSeconds() * ball.velocity; // reflect with the remaining percents

		} else ball.position += deltaTime.asSeconds() * ball.velocity;
		ball.newPosVector = vec2();


		/*if (!ball.isWithinYRange(0, height)) {
			ball.velocity.y = -ball.velocity.y;
		}

		if (!ball.isWithinXRange(0, width)) {
			ball.velocity.x = -ball.velocity.x;
		}

		bool ballIsColliding = ball.isCollidingWith(paddle1) || ball.isCollidingWith(paddle2);*/

		/*if (ballIsColliding) {
			ball.velocity.x = -ball.velocity.x;
		}*/
		//isColliding |= ballIsColliding;

		/*float bInt = ball.intersectionTest(paddle1);
		if (bInt < 1.0f) {
			std::cout << ball.intersectionTest(paddle1) << std::endl;
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