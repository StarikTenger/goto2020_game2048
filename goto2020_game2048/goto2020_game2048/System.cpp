#include "System.h"
#include "geometry.h"
#include "random.h"

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace geom;
using namespace random;
using namespace std;

System::System() {
	set_bubble(Vec2(50, 100), 0);
	set_bubble(Vec2(270, 160), 0);
}

System::~System() {}

std::vector<Bubble> System::get_bubbles() {
	return bubbles;
}

double System::get_cellSize() {
	return cellSize;
}
Vec2 System::get_borders() {
	return borders;
}

void System::set_gravity(Vec2 g) {
	gravity = g;
}

void System::set_bubble(Vec2 pos, int value) {
	double m = 1.0 + value; // Mass
	double r = cellSize * 0.47; // Radius
	Bubble bubble(pos, m, r, value);
	bubblesToAdd.push_back(bubble);
}

void System::add_all() {
	// Add bubbles
	for (auto& bubble : bubblesToAdd)
		bubbles.push_back(bubble);
	// Clean bubblesToAdd
	bubblesToAdd = {};
}

void System::step() {
	//// Physics ////
	// Gravity
	for (auto& bubble : bubbles) {
		bubble.force(gravity * bubble.get_mass() * dt);
	}

	// Collision
	for (auto& bubble : bubbles) {
		if (bubble.get_pos().x < 0)
			bubble.force(Vec2(10, 0));
		if (bubble.get_pos().y < 0)
			bubble.force(Vec2(0, 10));
		if (bubble.get_pos().x > 600)
			bubble.force(Vec2(-10, 0));
		if (bubble.get_pos().y > 600)
			bubble.force(Vec2(0, -10));
	}

	// wth obj
	for (auto& bubble : bubbles) {
		for (auto& bubble1 : bubbles) {
			if (&bubble == &bubble1)
				continue;
			if(geom::distance(bubble.get_pos(), bubble1.get_pos()) < bubble.get_radius() * 2)
				bubble.force(geom::direction(bubble.get_pos(), bubble1.get_pos()) * (10));
		}
	}


	// Moving
	for (auto& bubble : bubbles) {
		bubble.move(bubble.get_vel() * dt);
	}

	// Adding newborn bubbles to bubbles array
	add_all();
	time += dt;
}