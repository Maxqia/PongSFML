#pragma once
#include <SFML/System.hpp>
#include <vector>
#include <unordered_set>

#include "Vector.h"

extern sf::Time deltaTime;

// For the most part, it's a AABB
class Object : public sf::Drawable {
public:
	/* position, centered on the object */
	vec2 position;
	vec2 size;

	vec2 velocity;

	// Objects that can collide with this Object
	std::vector<Object*> collideObjects = {};

	// Objects currently colliding with this Object
	std::unordered_set<Object*> objColliding = {};

	virtual void onCollisionEnter(Object& obj, vec2 normal) {};
	virtual void onCollision(Object& obj, vec2 normal, bool first) {};
	virtual void onCollisionExit(Object& obj, vec2 normal) {};
	virtual void onCollided(Object& collider) {};

	void applyVelocity() {
		position += velocity * deltaTime.asSeconds();
	}

	bool doCollision() {
		for(Object* obj : collideObjects) {
			if (isCollidingWith(obj)) {
				vec2 normal = collisionGetNormal(obj);

				bool first = objColliding.find(obj) == objColliding.end();
				if (first) {
					onCollisionEnter(*obj, normal);
				}
				onCollision(*obj, normal, first);
				obj->onCollided(*this);

				objColliding.insert(obj);
			} else {
				size_t erasedObjects = objColliding.erase(obj);
				if (erasedObjects > 0) {
					// on collision exit, but too lazy to impl
				}
			}
		}
		return !objColliding.empty();
	}

	bool isCollidingWith(const Object* collider) const {
		bool collisionX1 = this->topLeftCorner().x > collider->bottomRightCorner().x;
		bool collisionX2 = this->bottomRightCorner().x < collider->topLeftCorner().x;
		bool collisionY1 = this->topLeftCorner().y > collider->bottomRightCorner().y;
		bool collisionY2 = this->bottomRightCorner().y < collider->topLeftCorner().y;
		return collisionX1 && collisionX2 && collisionY1 && collisionY2;
	}

	// lots of edge cases, but whatever 
	vec2 collisionGetNormal(const Object* collider) const {
		// thinking done on paper :)
		float leastOf = std::numeric_limits<float>::max();
		vec2 normal = vec2(0,0);
		float test;

		// case : to the bottom
		test = this->bottomRightCorner().y - collider->topLeftCorner().y;
		if (abs(test) < leastOf) {
			leastOf = abs(test);
			normal = vec2(0,1);
		}

		// case : to the top
		test = collider->bottomRightCorner().y - this->topLeftCorner().y;
		if (abs(test) < leastOf) {
			leastOf = abs(test);
			normal = vec2(0,-1);
		}

		// case : to the right
		test = this->topLeftCorner().x - collider->bottomRightCorner().x;
		if (abs(test) < leastOf) {
			leastOf = abs(test);
			normal = vec2(1,0);
		}

		// case : to the left
		test = collider->topLeftCorner().x - this->bottomRightCorner().x;
		if (abs(test) < leastOf) {
			leastOf = abs(test);
			normal = vec2(-1,0);
		}


		if (normal == vec2(0,0)) {
			throw std::runtime_error("didn't find normal!");
		}
		return normal;
	}

	void setYWithinRange(float min, float max) {
		if (position.y < min) {
			position.y = min;
		}

		if (position.y > max) {
			position.y = max;
		}
	}

	bool isAboveX(float test) const {
		return position.x + size.x > test;
	}
	bool isAboveY(float test) const {
		return position.y + size.y > test;
	}
	bool isBelowX(float test) const {
		return position.x - size.x < test;
	}
	bool isBelowY(float test) const {
		return position.y - size.y < test;
	}

	bool isWithinYRange(float min,float max) const {
		return !(isAboveY(max) || isBelowY(min));
	}

	bool isWithinXRange(float min,float max) const {
		return !(isAboveX(max) || isBelowX(min));
	}

	vec2 topLeftCorner() const {
		return position + size;
	}

	vec2 bottomRightCorner() const {
		return position - size;
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		//sf::VertexArray quad(sf::Quads, 4);
		sf::VertexArray quad(sf::LineStrip, 5);

		quad[0] = position + size;
		quad[1] = vec2(position.x - size.x, position.y + size.y);
		quad[2] = position - size;
		quad[3] = vec2(position.x + size.x, position.y - size.y);
		quad[4] = position + size;


		target.draw(quad);
	}
};

// Previous, Terrible Collision Code
/*
struct CollideInfo {
	float percent;
	vec2 normal;
};

	// returns true if it collided
	bool processCollisions() {
		bool ret = false;
		std::vector<struct CollideInfo> collideInfos(collideObjects.size());

		float percentLeft = 1.0f;
		float totalTime = deltaTime.asSeconds();
		while(percentLeft >= QZERO) {
			bool didCollide = false;
			int smallestIndex = -1;
			for(size_t i = 0; i < collideObjects.size(); i++) {
				struct CollideInfo newInfo = {};
				newInfo.percent = this->intersectionTest(*collideObjects[i], totalTime, newInfo.normal);
				collideInfos[i] = newInfo;


				if ((smallestIndex < 0 && newInfo.percent <= 1.0f) 
					|| (smallestIndex >= 0  && newInfo.percent < collideInfos[smallestIndex].percent)) {
					smallestIndex = i;
					didCollide = true;
					ret = true;
				}
			}
		
			if (didCollide) {
				float lastPercent = percentLeft;
				percentLeft = percentLeft * collideInfos[smallestIndex].percent;
				float percentUsed = lastPercent - percentLeft;
				//percentLeft -= percentUsed;
				onCollide(*collideObjects[smallestIndex], collideInfos[smallestIndex], percentUsed * totalTime);
				collideObjects[smallestIndex]->onCollided(*this, collideInfos[smallestIndex]);
			} else {
				onNoCollide(percentLeft * totalTime);
				break;
			}
		}
		//velocity = vec2();
		//newPosVector = vec2();

		return ret;
	}

	virtual void onCollide(Object& collider, CollideInfo info, float time) {};
	virtual void onNoCollide(float time) {};
	virtual void onCollided(Object& collider, CollideInfo info) {};

	// r is newposvector
	// s is other object's size
	float intersectionTest(Object& diff, float totalTime, vec2& normal) const {
		//Object b = minkowskiDifference(diff);
		Object b = diff.minkowskiDifference(*this);
		vec2 p(0,0);

		vec2 r = totalTime * (velocity - diff.velocity);
		//vec2 p = position;
		//vec2 r = newPosVector;

		float side1 = lineIntTest(p, r, b.topLeftCorner(), vec2(-(2.0f * b.size).x, 0));
		float side2 = lineIntTest(p, r, b.topLeftCorner(), vec2(0, -(2.0f * b.size).y));
		float side3 = lineIntTest(p, r, b.bottomRightCorner(), vec2((2.0f * b.size).x, 0));
		float side4 = lineIntTest(p, r, b.bottomRightCorner(), vec2(0, (2.0f * b.size).y));

		float nearestIntersection = std::numeric_limits<float>::max();
		normal = vec2(0,0);

		if (nearestIntersection > side1) {
			nearestIntersection = side1;
			normal = vec2(0,1);
		}

		if (nearestIntersection > side2) {
			nearestIntersection = side2;
			normal = vec2(-1,0);
		}

		if (nearestIntersection > side3) {
			nearestIntersection = side3;
			normal = vec2(0,-1);
		}

		if (nearestIntersection > side4) {
			nearestIntersection = side4;
			normal = vec2(1,0);
		}
		return nearestIntersection;
	}

	// p + zr = q + us
	static float lineIntTest(vec2 p, vec2 r, vec2 q, vec2 s) {
		float rxs = cross(r,s);
		vec2 qp = q - p;
		float qps = cross(qp, s);
		
		if (rxs == 0.0f) {
			if (qps != 0.0f) {
				return std::numeric_limits<float>::max(); // parallel case
			} else { 
				return 0.0f; // collinear case
			}
		} 

		float qpr = cross(qp, r);
		float z = qps / rxs;
		float u = qpr / rxs;
		
		if (z <= 1.0f && z >= QZERO && u <= 1.0f && u >= QZERO) {
			return z;
		} else {
			return std::numeric_limits<float>::max();
		}
	}

	Object minkowskiDifference(const Object copy) const {
		vec2 topLeft = this->bottomRightCorner() - copy.topLeftCorner();
		vec2 fullSize = (2.0f * this->size) + (2.0f * copy.size);

		Object ret;
		ret.position = vec2(topLeft + (fullSize / 2.0f));
		ret.size = fullSize / 2.0f;
		return ret;
	}
*/