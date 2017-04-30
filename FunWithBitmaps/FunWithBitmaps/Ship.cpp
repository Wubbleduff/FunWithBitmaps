#include "Ship.h"

Ship::Ship() {
	body = new GamePolygon();
	body->color = {255, 127, 0};
	body->numberOfVertices = 7;
	body->vertices = new Point[7];
	body->vertices[0] = {75.0f, 0.0f};
	body->vertices[1] = {25.0f, 50.0f};
	body->vertices[2] = {125.0f, 50.0f};
	body->vertices[3] = {40.0f, 100.0f};
	body->vertices[4] = {110.0f, 100.0f};
	body->vertices[5] = {0.0f, 150.0f};
	body->vertices[6] = {150.0f, 150.0f};
}

void Ship::draw(DrawBufferData *drawBufferData) {
	drawTriangleStrip(drawBufferData, body);
}

void Ship::move(float inX, float inY) {
	for(int i = 0; i < body->numberOfVertices; i++) {
		body->vertices[i].x += inX;
		body->vertices[i].y += inY;
	}
}

void Ship::rotate(float angle) {
	for(int i = 0; i < body->numberOfVertices; i++) {
		body->vertices[i].x += angle;
		body->vertices[i].y += angle;
	}
}