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

	w = window->getSize().x;
	h = window->getSize().y;
	/*
	cam.border = { w, h };
	sf::View view(sf::FloatRect(
		sf::Vector2f(cam.pos.x - w * 1 / cam.scale / 2, cam.pos.y - h * 1 / cam.scale / 2),
		sf::Vector2f(w * 1 / cam.scale, h * 1 / cam.scale)
	));
	view.setRotation(0);
	window->setView(view);*/
	
}

void DrawSystem::drawInterface() {
	
}

void DrawSystem::draw() {
	System& sys = *system;
	//window->clear();

	drawScene();
	
	drawInterface();
}
