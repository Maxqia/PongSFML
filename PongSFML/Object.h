#pragma once
#include <SFML/System.hpp>

#define vec2 sf::Vector2f
class Object : public sf::Drawable {
public:
	/* position, centered on the object */
	vec2 position;
	vec2 size;

	vec2 velocity;

	bool isCollidingWith(Object collider) {
		bool collisionX = position.x + size.x >= collider.position.x - size.x
			&& collider.position.x + size.x >= position.x - size.x;
		bool collisionY = collider.position.y + size.y >= position.y - size.y
			&& position.y + size.y >= collider.position.y - size.y;
		return collisionX && collisionY;
	}

	void setYWithinRange(float min, float max) {
		if (position.y < min) {
			position.y = min;
		}

		if (position.y > max) {
			position.y = max;
		}
	}

	bool isAboveX(float test) {
		return position.x + size.x > test;
	}
	bool isAboveY(float test) {
		return position.y + size.y > test;
	}
	bool isBelowX(float test) {
		return position.x - size.x < test;
	}
	bool isBelowY(float test) {
		return position.y - size.y < test;
	}

	bool isWithinYRange(float min,float max) {
		return !(isAboveY(max) || isBelowY(min));
	}

	bool isWithinXRange(float min,float max) {
		return !(isAboveX(max) || isBelowX(min));
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		sf::VertexArray quad(sf::Quads, 4);

		quad[0] = position + size;
		quad[1] = vec2(position.x - size.x, position.y + size.y);
		quad[2] = position - size;
		quad[3] = vec2(position.x + size.x, position.y - size.y);


		target.draw(quad);
	}
};