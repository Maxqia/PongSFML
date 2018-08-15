#pragma once

#include "Object.h"
class Paddle : public Object {
public:
	void onCollide(Object& collider, CollideInfo info) override {
		position += info.percent * newPosVector;
		position -= (1.0f - info.percent) * newPosVector; // reflect with the remaining percents
	}

	void onNoCollide() override {
		position += newPosVector;
	}
};