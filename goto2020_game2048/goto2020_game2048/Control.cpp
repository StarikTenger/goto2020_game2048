#include "Control.h"
#include "getMilliCount.h"
#include <iostream>
#include <fstream>
#include <sstream>

Control::Control() {
	// Configuring keys
	for (int i = 0; i < 100; i++) {
		keyMatches.push_back({});
	}
	std::ifstream keys("keys.conf");
	while (keys) {
		std::string key;
		keys >> key;
		while (keys) {
			std::string key1;
			keys >> key1;
			if (key1 == "END")
				break;
			keyMatches[getKey(key1)].push_back(getKey(key));

		}
	}
}

Control::~Control() {

}

Vec2 Control::getCursorPos() {
	return geom::rotate((mouse.pos - drawSys.cam.border/2) / drawSys.cam.scale, drawSys.cam.angle);
}

void Control::loadConfig() {
	
}


void Control::saveConfig() {
	
}

void Control::step() {
	int timeMs = getMilliCount();
	if (timeMs - timePrev > dt) {
		// Counting fps
		timePrev = timeMs;

		// Sys events (keys, mouse, etc)
		events();
		drawSys.mouse = mouse;
		
		// Check keys
		double gravityValue = 1;
		Vec2 gravity; // initial value 0
		if (keys[Commands::W])
			gravity.y -= gravityValue;
		if (keys[Commands::A])
			gravity.x -= gravityValue;
		if (keys[Commands::S])
			gravity.y += gravityValue;
		if (keys[Commands::D])
			gravity.x += gravityValue;
		
		sys.set_gravity(gravity);

		// System step
		for (int i = 0; i < 10; i++) {
			sys.step();
		}
		
		// Draw
		drawSys.system = &sys;
		drawSys.draw();
		drawSys.window->display();

		
	}
}
