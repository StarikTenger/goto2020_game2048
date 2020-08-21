#include "Control.h"
#include "getMilliCount.h"
#include <iostream>
#include <fstream>
#include <sstream>

Control::Control() {
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

	drawSys.cam.scale = 250;
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
		
		// System step
		for (int i = 0; i < 1; i++) {
			sys.step();
		}
		
		// Draw
		drawSys.system = &sys;
		drawSys.draw();
		drawSys.window->display();

		
	}
}
