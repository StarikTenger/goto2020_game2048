#include "Animation.h"

Animation::Animation(){}

Animation::Animation(Vec2 _pos, double _sizeBegin, double _sizeEnd, int _val, std::string _image, double _timer, Bubble* _bubble) {
	pos = _pos;
	sizeBegin = _sizeBegin;
	sizeEnd = _sizeEnd;
	val = _val;
	image = _image;
	timer = _timer;
	period = timer;
	bubble = _bubble;
}

void Animation::step(double dt) {
	size = sizeEnd + (sizeBegin - sizeEnd) * (timer) / period;
	color = colorEnd + (colorBegin - colorEnd) * (timer) / period;
	alpha = (timer) / period;
	if (bubble)
		pos = bubble->get_pos();
	timer -= dt;
}

std::string Animation::get_image() {
	return image;
}
Vec2 Animation::get_pos() {
	return pos;
}
double Animation::get_size() {
	return size;
}
double Animation::get_timer() {
	return timer;
}
double Animation::get_alpha() {
	return alpha;
}
int Animation::get_val() {
	return val;
}