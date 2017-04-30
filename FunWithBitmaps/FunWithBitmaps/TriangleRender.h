#pragma once

#include "GameData.h"

void drawTriangle(DrawBufferData *drawBufferData, Point p1, Point p2, Point p3, Color color);
void drawPolygon(DrawBufferData *drawBufferData, GamePolygon *polygon);
void drawTriangleStrip(DrawBufferData *drawBufferData, GamePolygon *polygon);