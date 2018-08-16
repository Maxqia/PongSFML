#pragma once

#include "Object.h"
class Paddle : public Object {
public:
	void onCollide(Object& collider, CollideInfo info, float time) override {
		position += info.percent * velocity * time;
		velocity *= -1.0f;
		position += (1.0f - info.percent) * velocity * time; // reflect with the remaining percents
	}

	void onNoCollide(float time) override {
		position += velocity * time;
		velocity = vec2(0,0);
	}

	void onCollisionEnter(Object& obj, vec2 normal) override {
		std::cout << "paddle collision enter!" << std::endl;
		//velocity *= -1.0f;
	}

	// we're stuck!
 	void onCollision(Object& obj, vec2 normal, bool first) override {
		std::cout << "paddle collision!" << std::endl;
		//velocity *= -1.0f;
		
		// don't you dare move the paddle along the x
		velocity.y = 400.0f * normal.y;
	}
};