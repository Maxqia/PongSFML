#pragma once


#include "Object.h"
class Ball : public Object {
public:
	void onCollide(Object& collider, CollideInfo info) override {

		position += info.percent * deltaTime.asSeconds() * velocity;

		/*// rotate 90 degrees
		velocity = vec2(-velocity.y, velocity.x);*/

		// reflect across normal
		velocity = reflect(velocity, info.normal);
		position += (1.0f - info.percent) * deltaTime.asSeconds() * velocity; // reflect with the remaining percents
	}

	void onNoCollide() override {
		position += deltaTime.asSeconds() * velocity;
	}
};