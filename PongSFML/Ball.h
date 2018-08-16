#pragma once


#include "Object.h"
class Ball : public Object {
public:
	void onCollisionEnter(Object& obj, vec2 normal) override {
		std::cout << "ball collision enter!" << std::endl;
		velocity = reflect(velocity, normal);
	}
};