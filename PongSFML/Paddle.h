#pragma once

#include "Object.h"
class Paddle : public Object {
public:
	// returns true if it collided
	bool processIntersection(Object object) {
		bool ret = false;
		vec2 normal;

		float intersection = this->intersectionTest(object, newPosVector, normal);
		if (intersection < 1.0f) {
			ret = true;

		} else position += newPosVector;
		newPosVector = vec2();

		return ret;
	}

	void onCollide(Object collider, CollideInfo info) override {
		position += info.percent * newPosVector;
		position -= (1.0f - info.percent) * newPosVector; // reflect with the remaining percents
	}

	void onNoCollide() override {
		position += newPosVector;
	}
};