#pragma once

#include "Object.h"
class Paddle : public Object {
public:
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