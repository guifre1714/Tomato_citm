#pragma once
#include <raylib.h>
#include <vector>
#include <iostream>
using namespace std;

class Collider {
public:
	Collider();
	~Collider();

	bool breakable;
	Rectangle col;
};