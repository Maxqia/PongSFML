#pragma once


#include "Object.h"
class Ball : public Object {
public:
	// returns true if it collided
	bool processIntersection(Object object, float time) {
		bool ret = false;
		vec2 normal;

		float intersection = this->intersectionTest(object, time * velocity, normal);
		if (intersection < 1.0f) {
			ret = true;
			position += intersection * time * velocity;

			// rotate 90 degrees
			velocity = vec2(-velocity.y, velocity.x);
			position += (1.0f - intersection) * time * velocity; // reflect with the remaining percents

		} else position += time * velocity;
		newPosVector = vec2();

		return ret;
	}
};