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
}

System::~System() {}

std::vector<Bubble> System::get_bubbles() {
	return bubbles;
}

double System::get_gravityValue() {
	return gravityValue;
}

double System::get_cellSize() {
	return cellSize;
}
Vec2 System::get_borders() {
	return borders;
}
int System::get_score() {
	return score;
}

void System::set_gravity(Vec2 g) {
	gravity = g;
}

void System::set_bubble(Vec2 pos, Vec2 vel, int value, int type) {
	double m = initialMass * pow(1.2, value); // Mass
	double r = cellSize * initialRadius * pow(1.2, value); // Radius
	Bubble bubble(pos, m, r, value, type);
	bubble.set_vel(vel);
	bubblesToAdd.push_back(bubble);
}

void System::add_all() {
	// Add bubbles
	for (auto& bubble : bubblesToAdd)
		bubbles.push_back(bubble);
	// Clean bubblesToAdd
	bubblesToAdd = {};
}

void System::collision(Bubble& bubble, std::pair<Vec2, Vec2> wall) {
	double dist = geom::distance(bubble.get_pos(), wall.first, wall.second); // Distance between bubble & wall
	if (dist > bubble.get_radius()) // Bubble is too far from the wall
		return;
	// Check move direction
	double coeff = 1;
	if (geom::distance(bubble.get_pos() + bubble.get_vel() * dt, wall.first, wall.second) > dist) // Distance increases
		coeff = collisionK;

	// Force is proportional to dist
	coeff *= -(dist - bubble.get_radius()) * 0.01;

	// Check side of the wall
	if (geom::cross(bubble.get_pos() - wall.first, wall.second - wall.first) > 0) {
		bubble.force(geom::direction(Vec2(), geom::rotate(wall.first - wall.second, M_PI / 2)) * (-collisionForce) * coeff);
	}
	else {
		bubble.force(geom::direction(Vec2(), geom::rotate(wall.first - wall.second, M_PI / 2)) * (collisionForce) * coeff);
	}
}

void System::step() {
	for (auto& b : bubbles) {
		b.set_velPrev(b.get_vel());
	}

	// Gravity
	for (auto& bubble : bubbles) {
		bubble.force(gravity * bubble.get_mass() * dt);
	}

	//// Collision ////

	// Walls
	for (auto& bubble : bubbles) {
		collision(bubble, {Vec2(0, cellSize * cellNumber), Vec2(cellSize * cellNumber, cellSize * cellNumber)});
		collision(bubble, { Vec2(cellSize * cellNumber, 0), Vec2(cellSize * cellNumber, cellSize * cellNumber) });
		collision(bubble, { Vec2(0, cellSize * cellNumber), Vec2(0, 0) });
		collision(bubble, { Vec2(cellSize * cellNumber, 0), Vec2(0, 0) });
	}

	// Other bubbles
	for (auto& bubble : bubbles) {
		for (auto& bubble1 : bubbles) {
			if (&bubble == &bubble1 || bubble.get_value() == bubble1.get_value() && bubble.get_type() == bubble1.get_type())
				continue;
			double dist = geom::distance(bubble.get_pos(), bubble1.get_pos());
			double coeff = 1;
			// Checking move direction
			if(geom::distance(bubble.get_pos() + bubble.get_vel() * dt, bubble1.get_pos() + bubble1.get_vel() * dt) > dist)
				coeff = collisionK;
			// Dist
			coeff *= -(dist - bubble.get_radius() - bubble1.get_radius()) * 0.01;
			if(dist < bubble.get_radius() + bubble1.get_radius())
				bubble.force(geom::direction(bubble.get_pos(), bubble1.get_pos()) * (collisionForce)
					* coeff
				);
		}
	}

	//// Moving ////
	for (auto& bubble : bubbles) {
		bubble.move(bubble.get_vel() * dt);
	}

	// Friction
	for (auto& bubble : bubbles) {
		bubble.force(bubble.get_vel() * -dt * viscousFrictionK);
	}


	//// Grouping ////
	for (auto& bubbleA : bubbles) {
		for (auto& bubbleB : bubbles) {
			if (&bubbleA == &bubbleB)
				continue;
			if (bubbleA.get_type() != bubbleB.get_type())
				continue;
			if (!bubbleA.get_isAlive() || !bubbleB.get_isAlive())
				continue;
			if (geom::distance(bubbleA.get_pos(), bubbleB.get_pos()) > bubbleA.get_radius() + bubbleB.get_radius())
				continue;
			if (bubbleA.get_value() != bubbleB.get_value())
				continue;
			if (geom::distance(bubbleA.get_pos(), bubbleB.get_pos()) < 10) { // grouping
				set_bubble((bubbleA.get_pos() + bubbleB.get_pos()) / 2, (bubbleA.get_vel() + bubbleB.get_vel()) / 2, bubbleA.get_value() + 1, bubbleA.get_type());
				bubbleA.set_isAlive(0);
				bubbleB.set_isAlive(0);
				score += (int)pow(2, bubbleA.get_value());
			}
			else { // force
				double k = -0.001;
				bubbleA.force(geom::direction(bubbleA.get_pos(), bubbleB.get_pos()) * (collisionForce)  * k);
				bubbleB.force(geom::direction(bubbleB.get_pos(), bubbleA.get_pos()) * (collisionForce)  * k);
			}
		}
	}

	// Spawning
	if (geom::distance(gravity, gravityPrev) > EPS && time - spawnLast > spawnPeriod) {
		for (int i = 0; i < 10; i++) {
			double r = initialRadius * cellSize / 2;
			Vec2 pos = Vec2(
				random::intRandom(r * 2, cellSize * cellNumber - r*2),
				random::intRandom(r * 2, cellSize * cellNumber - r*2));
			// Check for collision
			int coll = 0;
			for (auto& bubble : bubbles) {
				if (geom::distance(bubble.get_pos(), pos) < r*1.1 + bubble.get_radius()) {
					coll = 1;
					break;
				}
			}
			// Spawn
			if (!coll) {
				set_bubble(pos, Vec2(0, 0), 0, random::intRandom(1, typeNumber));
				spawnLast = time;
				break;
			}

		}
	}

	// Removing
	for (int i = 0; i < bubbles.size(); i++) {
		if (!bubbles[i].get_isAlive()) {
			bubbles.erase(bubbles.begin() + i);
			i--;
			std::cout << i << "\n";
		}
	}

	// Adding newborn bubbles to bubbles array
	add_all();

	// Timer
	time += dt;

	// Prev values
	gravityPrev = gravity;
	
}