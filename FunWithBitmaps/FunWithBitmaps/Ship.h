#pragma once
#include "GameData.h"
#include "TriangleRender.h"
#include <math.h>

class Ship {
public:
    Ship();	
	void draw(DrawBufferData *drawBufferData);
	void move(float x, float y);
	void rotate(float angle);

    GamePolygon *body;
private:
};