#include "Bubble.h"

Bubble::Bubble() {}

Bubble::Bubble(Vec2 _pos, double _mass, double _r, int _value, int _type) {
	pos = _pos;
	mass = _mass;
	radius = _r;
	value = _value;
	type = _type;
}

void Bubble::step(double dt) {
	time += dt;
}

Vec2 Bubble::get_pos() {
	return pos;
}
Vec2 Bubble::get_vel() {
	return vel;
}
Vec2 Bubble::get_velPrev() {
	return velPrev;
}
double Bubble::get_mass() {
	return mass;
}
double Bubble::get_radius() {
	double r = radius;
	double t = 0.05; // Grow time
	if (time < t && value == 0)
		r = radius * time / t;
	return r;
}
double Bubble::get_time() {
	return time;
}
int Bubble::get_value() {
	return value;
}
bool Bubble::get_isAlive() {
	return isAlive;
}

int Bubble::get_type() {
	return type;
}

void Bubble::set_pos(Vec2 _pos) {
	pos = _pos;
}
void Bubble::set_vel(Vec2 _vel) {
	vel = _vel;
}
void Bubble::set_velPrev(Vec2 _vel) {
	velPrev = _vel;
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
void Bubble::set_isAlive(bool val) {
	isAlive = val;
}