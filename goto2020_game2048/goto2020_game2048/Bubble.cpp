#include "Bubble.h"

Bubble::Bubble() {}

Bubble::Bubble(Vec2 _pos, double _mass, double _r, int _value) {
	pos = _pos;
	mass = _mass;
	radius = _r;
	value = _value;
}

Vec2 Bubble::get_pos() {
	return pos;
}
Vec2 Bubble::get_vel() {
	return vel;
}
double Bubble::get_mass() {
	return mass;
}
double Bubble::get_radius() {
	return radius;
}
int Bubble::get_value() {
	return value;
}

void Bubble::set_pos(Vec2 _pos) {
	pos = _pos;
}
void Bubble::set_vel(Vec2 _vel) {
	vel = _vel;
}
void Bubble::set_mass(double _mass) {
	mass = _mass;
}
void Bubble::set_radius(double _radius) {
	radius = _radius;
}
void Bubble::set_value(int _value) {
	value = _value;
}

void Bubble::force(Vec2 f) {
	vel += f / mass;
}

void Bubble::move(Vec2 shift) {
	pos += shift;
}