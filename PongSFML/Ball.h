#pragma once


#include "Object.h"
class Ball : public Object {
public:
	void onCollide(Object& collider, CollideInfo info, float time) override {

		position += time * velocity;

		/*// rotate 90 degrees
		velocity = vec2(-velocity.y, velocity.x);*/

		// reflect across normal
		velocity = reflect(velocity, info.normal);
		//position += (1.0f - info.percent) * deltaTime.asSeconds() * velocity; // reflect with the remaining percents
	}

	void onNoCollide(float time) override {
		position += time * velocity;
	}
};