#pragma once

#include "Object.h"
class Screen : public Object {
public:

	int paddle1Score, paddle2Score;

	// only the ball will call this
	void onCollided(Object& collider, CollideInfo info) override {
		std::cout << info.normal.x << std::endl;
		std::cout << info.normal.y << std::endl;
		if (info.normal == vec2(-1,0)) {
			paddle1Score++;
		}
		if (info.normal == vec2(1,0)) {
			paddle2Score++;
		}
	}
};