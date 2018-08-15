#pragma once

#include "Object.h"
class Paddle : public Object {
public:
	// returns true if it collided
	bool processIntersection(Object object) {
		bool ret = false;

		float intersection = this->intersectionTest(object, newPosVector);
		if (intersection < 1.0f) {
			ret = true;
			position += intersection * newPosVector;
			position -= (1.0f - intersection) * newPosVector; // reflect with the remaining percents
		} else position += newPosVector;
		newPosVector = vec2();

		return ret;
	}
};