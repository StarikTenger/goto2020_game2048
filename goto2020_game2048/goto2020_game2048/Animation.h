#pragma once
#include "Vec2.h"
#include "Color.h"
#include "Bubble.h"
#include <string>

class Animation {
	Vec2 pos;
	
	Color colorBegin = {};
	Color colorEnd = {};
	Color color = {};

	double sizeBegin = 0;
	double sizeEnd = 0;
	double size = 0;

	double alpha = 1;

	double timer = 0;
	double period = 0;

	int val = 0;

	Bubble* bubble;

	std::string image = "";
public:
	Animation();
	Animation(Vec2 _pos, double _sizeBegin, double _sizeEnd, int _val, std::string _image, double _timer, Bubble* _bubble);
	void step(double dt);

	std::string get_image();
	Vec2 get_pos();
	double get_size();
	double get_timer();
	double get_alpha();
	int get_val();
};

