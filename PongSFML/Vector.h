#pragma once
#include <SFML/System/Vector2.hpp>

#define vec sf::Vector2
#define vec2 vec<float>

/*template <typename T>
class vec : public sf::Vector2<T> {
public:
	vec() : sf::Vector2<T>() {};
	vec(T x, T y) : sf::Vector2<T>(x, y) {};

	static T cross(vec<T> v, vec<T> w) {
		return (v.x * w.y) - (v.y * w.x);
	};
};

template <typename T>
vec<T> operator+(const vec<T> lhs, const vec<T> rhs) {
	return vec<T>(lhs.x + rhs.x, lhs.x + rhs.x);
}

template <typename T>
vec<T> operator-(const vec<T> lhs, const vec<T> rhs) {
	return vec<T>(lhs.x - rhs.x, lhs.x - rhs.x);
}

template <typename T>
vec<T> operator*(const T lhs, const vec<T> rhs) {
	return vec<T>(lhs * rhs.x, lhs * rhs.y);
}*/

template <typename T>
T cross(vec<T> v, vec<T> w) {
	return (v.x * w.y) - (v.y * w.x);
};

template <typename T>
T dot(vec<T> v, vec<T> w) {
	return (v.x * w.x) + (v.y * w.y);
};