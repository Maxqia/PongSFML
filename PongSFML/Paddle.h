#pragma once

#include "Object.h"
class Paddle : public Object {
public:
	void onCollide(Object& collider, CollideInfo info, float time) override {
		position += velocity * time;
		velocity = vec2(0,0);
	}

	void onNoCollide(float time) override {
		position += velocity * time;
	}
};