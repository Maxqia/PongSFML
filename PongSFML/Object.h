#pragma once
#include <SFML/System.hpp>

#include "Vector.h"

class Object : public sf::Drawable {
public:
	/* position, centered on the object */
	vec2 position;
	vec2 size;

	vec2 velocity;
	vec2 newPosVector;

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

	vec2 topLeftCorner() {
		return position + size;
	}

	vec2 bottomRightCorner() {
		return position - size;
	}


	// r is newposvector
	// s is other object's size
	float intersectionTest(Object b) {
		vec2 p = position;
		vec2 r = newPosVector;

		float side1 = lineIntTest(p, r, b.topLeftCorner(), vec2((2.0f * b.size).x, 0));
		float side2 = lineIntTest(p, r, b.topLeftCorner(), vec2(0, -(2.0f * b.size).y));
		float side3 = lineIntTest(p, r, b.bottomRightCorner(), vec2(-(2.0f * b.size).x, 0));
		float side4 = lineIntTest(p, r, b.bottomRightCorner(), vec2(0, (2.0f * b.size).y));

		float nearestIntersection = side1;
		if (nearestIntersection < side2) nearestIntersection = side2;
		if (nearestIntersection < side3) nearestIntersection = side3;
		if (nearestIntersection < side4) nearestIntersection = side4;
		return nearestIntersection;
	}

	// p + zr = q + us
	static float lineIntTest(vec2 p, vec2 r, vec2 q, vec2 s) {
		float rxs = vec2::cross(r,s);
		vec2 qp = q - p;
		float qps = vec2::cross(qp, s);
		
		if (rxs == 0.0f) {
			if (qps != 0.0f) {
				return std::numeric_limits<float>::max(); // parallel case
			} else { 
				return 0.0f; // collinear case
			}
		} 

		float qpr = vec2::cross(qp, r);
		float z = qps / rxs;
		float u = qpr / rxs;
		
		if (z <= 1.0f && z >= 0.0f && u <= 1.0f && u >= 0.0f) {
			return z;
		} else {
			return std::numeric_limits<float>::max();
		}
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