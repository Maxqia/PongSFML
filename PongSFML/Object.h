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