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
	//fillRect(0, 0, 10000, 10000, Color(128, 128, 128, 100)); // Temporary solution
	image("background", w/2, h/2, w, h, 0, Color(255, 255, 255, 200));


	// Getting object array
	auto bubbles = sys.get_bubbles();

	// Shadows
	for (auto& bubble : bubbles) {
		std::vector<Color> colors = {
			Color(95, 92, 255),
			Color(84, 255, 93),
			Color(229, 255, 84),
			Color(255, 189, 84),
			Color(255, 84, 84),
			Color(255, 84, 232),
		};
		auto col = colors[bubble.get_value() % colors.size()];


		if (bubble.get_type() == 1)
			col = Color(0, 0, 0);
		if (bubble.get_type() == 2)
			col = Color(255, 255, 255);

		if (bubble.get_type() == 1)
			image("black", bubble.get_pos(), Vec2(bubble.get_radius(), bubble.get_radius()) * 3.2, 0, col);
		if (bubble.get_type() == 2)
			image("white", bubble.get_pos(), Vec2(bubble.get_radius(), bubble.get_radius()) * 2.6, 0, col);

	}

	for (auto& bubble : bubbles) {
		std::vector<Color> colors = {
			Color(95, 92, 255),
			Color(84, 255, 93),
			Color(229, 255, 84),
			Color(255, 189, 84),
			Color(255, 84, 84),
			Color(255, 84, 232),
		};
		auto col = colors[bubble.get_value() % colors.size()];
		

		col = colors[bubble.get_value() % colors.size()];
		fillCircle(bubble.get_pos(), Vec2(), bubble.get_radius(), col);

		if(bubble.get_type() == 1)
			fillCircle(bubble.get_pos(), Vec2(), bubble.get_radius() * 0.5, Color(0, 0, 0));
		if(bubble.get_type() == 2)
			fillRect(bubble.get_pos(), Vec2(bubble.get_radius() , bubble.get_radius() ), Color(0, 0, 0));

		// Packs
		std::vector<std::string> pack1 = {
			"Felix",
			"Sveta",
			"Igor",
			"Rost",
			"Dima",
			"Fedor",
			"Alena"
		};

		std::vector<std::string> pack2 = {
			"1",
			"Vlad",
			"Gosha",
			"Oleg",
			"Ella",
			"Valentin",
			"Nicolay"
		};

		// Image
		auto img = pack1[bubble.get_value()];
		if(bubble.get_type() == 2)
			img = pack2[bubble.get_value()];

		col = Color(255, 255, 255);
		double scale_x = 1.0 - std::max(abs(bubble.get_velPrev().x - bubble.get_vel().x), 0.2) * 0.003;
		double scale_y = 1.0 - std::max(abs(bubble.get_velPrev().y - bubble.get_vel().y), 0.2) * 0.003;
		image(img, bubble.get_pos(), Vec2(bubble.get_radius() * scale_x, bubble.get_radius() * scale_y) * 2 * 0.9, 0, col);
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
