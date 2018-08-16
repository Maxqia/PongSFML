#pragma once


#include "Object.h"
class Ball : public Object {
public:
	void onCollide(Object& collider, CollideInfo info, float time) override {

		position += info.percent * time * velocity;

		/*// rotate 90 degrees
		velocity = vec2(-velocity.y, velocity.x);*/

		// reflect across normal
		velocity = reflect(velocity, info.normal);
		position += (1.0f - info.percent) * time * velocity; // reflect with the remaining percents
	}

	void onNoCollide(float time) override {
		position += time * velocity;
	}

	void onCollisionEnter(Object& obj, vec2 normal) override {
		std::cout << "ball collision enter!" << std::endl;
		velocity = reflect(velocity, normal);
	}
};