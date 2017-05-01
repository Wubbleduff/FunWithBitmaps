#pragma once
#include "GameData.h"
#include "ShapeRender.h"
#include <math.h>

class Ship {
public:
    Ship(DrawBufferData *inDrawBufferData);	
	void updateAndDraw();
	Point getCenter();
	void moveToCenter();
	void moveForward(float thrust);
	void rotate(float angle);

    GamePolygon *body;
private:
	DrawBufferData *drawBufferData;

	Vector velocity;
};