#include "System.h"
#include "geometry.h"
#include "random.h"

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace geom;
using namespace random;
using namespace std;

System::System() {
	
}

System::~System() {
}


void System::step() {

	time += dt;
}