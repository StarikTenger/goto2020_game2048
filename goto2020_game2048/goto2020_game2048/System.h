#pragma once
#include <vector>
#include "Vec2.h"
#include "Bubble.h"

class System {

	double dt = 0.002; // Time change per step
	double time = 0; // Current in-sys time
	double viscousFrictionK = 0.0; // Friction koefficient

	int cellNumber = 4; // Number of cells vertically and horizontally
	double cellSize = 150; // Side of single cells

	Vec2 borders = Vec2(cellSize, cellSize) * cellNumber; // Size of whole game field
	Vec2 gravity; // Global gravity
	std::vector<Bubble> bubbles; // Bubbles array
	std::vector<Bubble> bubblesToAdd; // Bubbles that should be added to bubbles array

public:
	// Functions to interact with parameters
	std::vector<Bubble> get_bubbles(); // Returns copy of bubbles array
	double get_cellSize();
	Vec2 get_borders();

	void set_gravity(Vec2 g);
	void set_bubble(Vec2 pos, int value);
	void add_all(); // Adds everything from bubblesToAdd

	System();
	~System();

	void step();
};
                                                                                                                                                                                                                                                                                       