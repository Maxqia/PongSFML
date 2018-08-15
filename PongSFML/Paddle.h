#pragma once

#include "Object.h"
class Paddle : public Object {
	void processIntersection(Object object) {
		float intersection = this->intersectionTest(object);
		if (intersection < 1.0f) {
			position += intersection * newPosVector;
			position -= (1.0f - intersection) * newPosVector; // reflect with the remaining percents
		} else position += newPosVector;
		newPosVector = vec2();
	}
};