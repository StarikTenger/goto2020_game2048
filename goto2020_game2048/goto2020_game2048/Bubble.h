#pragma once
#include "Vec2.h"

class Bubble {
	Vec2 pos; // Position
	Vec2 vel; // Velocity
	Vec2 velPrev; // Velocity prev
	double mass = 0; // Mass
	double radius = 1; // Radius
	double time = 0; // Time from birth
	int value = 0; // 2048-value
	int type = 0; 
	bool isAlive = 1;

public:
	Bubble();
	Bubble(Vec2 _pos, double _mass, double _r, int _value, int _type);

	void step(double dt);

	// Functions to interact with parameters
	Vec2 get_pos();
	Vec2 get_vel();
	Vec2 get_velPrev();
	double get_mass();
	double get_radius();
	double get_time();
	int get_value();
	bool get_isAlive();
	int get_type();

	void set_pos(Vec2 _pos);
	void set_vel(Vec2 _vel);
	void set_velPrev(Vec2 _vel);
	void set_mass(double _mass);
	void set_radius(double _radius);
	void set_value(int _value);
	void set_isAlive(bool val);

	void force(Vec2 f); // Applies force
	void move(Vec2 shift); // Changes pos
};

