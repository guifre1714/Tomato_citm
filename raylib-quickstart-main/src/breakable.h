#pragma once
#include <collider.h>

class Breakable : public Collider {
public:
	Breakable(Vector2 position);
	~Breakable();
};