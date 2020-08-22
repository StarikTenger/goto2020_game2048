#pragma once
#include "Vec2.h"

class Bubble {
	Vec2 pos; // Position
	Vec2 vel; // Velocity
	double mass = 0; // Mass
	double radius = 1; // Radius
	int value = 0; // 2048-value

public:
	Bubble();
	Bubble(Vec2 _pos, double _mass, double _r, int _value);
	// Functions to interact with parameters
	Vec2 get_pos();
	Vec2 get_vel();
	double get_mass();
	double get_radius();
	int get_value();

	void set_pos(Vec2 _pos);
	void set_vel(Vec2 _vel);
	void set_mass(double _mass);
	void set_radius(double _radius);
	void set_value(int _value);

	void force(Vec2 f); // Applies force
	void move(Vec2 shift); // Changes pos
};

