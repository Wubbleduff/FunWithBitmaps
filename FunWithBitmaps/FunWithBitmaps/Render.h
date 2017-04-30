#pragma once

#include "Ship.h"
#include "GameData.h"

class Render {
public:
	Render(uint32 *inPDrawBuffer, int inDrawBufferWidth, int inDrawBufferHeight);
	void changeDrawBufferDimensions(uint32 *inPDrawBuffer, int inDrawBufferWidth, int inDrawBufferHeight);
	void draw(GameInput input);
	void drawTriangle(Point p1, Point p2, Point p3, Color color);
	void drawPolygon(GamePolygon *polygon);
	void drawTriangleStrip(GamePolygon *polygon);
	void drawCircle(Point point, float radius);
private:
	DrawBufferData *drawBufferData;

	Ship *ship = 0;

	double spinAngle = 0.0;
	double maxRightX = 0.0;
};