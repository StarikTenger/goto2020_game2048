#pragma once
#include <vector>
#include "Vec2.h"
#include "Bubble.h"

class System {

	double dt = 0.0002; // Time change per step
	double time = 0; // Current in-sys time
	double spawnPeriod = 0.3; // Time between bubble spawns
	double spawnLast = 0; // Time of the last spawn
	double viscousFrictionK = 0.05; // Friction coefficient
	double collisionForce = 5000; // Collison force
	double gravityValue = 10000;
	double collisionK = 0.3; // Collision energy loss
	double initialRadius = 0.3; // Radius of 0-value bubble
	double initialMass = 1; // Mass of 0-value bubble
	
	int score = 0;
	int typeNumber = 2; // Number of types
	int cellNumber = 4; // Number of cells vertically and horizontally
	double cellSize = 150; // Side of single cells

	Vec2 borders = Vec2(cellSize, cellSize) * cellNumber; // Size of whole game field
	Vec2 gravity; // Global gravity
	Vec2 gravityPrev; // Previous-step lobal gravity
	std::vector<Bubble> bubbles; // Bubbles array
	std::vector<Bubble> bubblesToAdd; // Bubbles that should be added to bubbles array

	void collision(Bubble& bubble, std::pair<Vec2, Vec2> wall);

public:
	// Functions to interact with parameters
	std::vector<Bubble> get_bubbles(); // Returns copy of bubbles array
	double get_cellSize();
	double get_gravityValue();
	Vec2 get_borders();
	int get_score();


	void set_gravity(Vec2 g);
	void set_bubble(Vec2 pos, Vec2 vel, int value, int type);
	void add_all(); // Adds everything from bubblesToAdd

	System();
	~System();

	void step();
};
                                                                                                                                                                                                                                                                                       