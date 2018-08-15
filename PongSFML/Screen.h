#pragma once

#include "Object.h"
class Screen : public Object {
public:

	int paddleScore = 0;

	// only the ball will call this
	void onCollided(Object& collider, CollideInfo info) override {
		paddleScore++;
	}
};