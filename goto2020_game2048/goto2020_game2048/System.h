#pragma once
#include <vector>
#include "Vec2.h"

class System {
public:
	double dt = 0.02;
	double time = 0.3;

	System();
	~System();

	void step();
};
                                                                                                                                                                                                                                                                                       