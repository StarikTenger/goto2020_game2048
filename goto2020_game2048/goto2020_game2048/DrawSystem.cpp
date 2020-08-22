#include "DrawSystem.h"
#include "getMilliCount.h"
#include <math.h>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>



DrawSystem::DrawSystem(){
	window = new sf::RenderWindow(sf::VideoMode(600, 600), "Biba & Boba");
	loadTextures();
}

DrawSystem::~DrawSystem(){}

void DrawSystem::drawScene() {
	System& sys = *system;

	// Width & Height
	w = window->getSize().x;
	h = window->getSize().y;
	
	// Configuring camera
	if (0) { // We don't use it in this project
		cam.border = { w, h };
		sf::View view(sf::FloatRect(
			sf::Vector2f(cam.pos.x - w * 1 / cam.scale / 2, cam.pos.y - h * 1 / cam.scale / 2),
			sf::Vector2f(w * 1 / cam.scale, h * 1 / cam.scale)
		));
		view.setRotation(0);
		window->setView(view);
	}
	
	// Clean scene
	fillRect(0, 0, 10000, 10000, Color(0, 0, 0)); // Temporary solution

	// Getting object array
	auto bubbles = sys.get_bubbles();
	for (auto& bubble : bubbles) {
		fillCircle(bubble.get_pos(), Vec2(), bubble.get_radius(), Color(25, 167, 189));
	}
	
}

void DrawSystem::drawInterface() {
	
}

void DrawSystem::draw() {
	System& sys = *system;
	//window->clear();

	drawScene();
	
	drawInterface();
}
