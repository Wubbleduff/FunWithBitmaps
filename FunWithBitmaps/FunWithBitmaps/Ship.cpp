#include "Ship.h"

Ship::Ship(DrawBufferData *inDrawBufferData) {
	body = new GamePolygon();
	body->color = {255, 127, 0};
	body->numberOfVertices = 7;
	body->vertices = new Point[7];
	/*
	body->vertices[0] = {75.0f, 0.0f};
	body->vertices[1] = {45.0f, 50.0f};
	body->vertices[2] = {105.0f, 50.0f};
	body->vertices[3] = {60.0f, 100.0f};
	body->vertices[4] = {90.0f, 100.0f};
	body->vertices[5] = {20.0f, 150.0f};
	body->vertices[6] = {130.0f, 150.0f};
	*/
	body->vertices[0] = {75.0f, 0.0f};
	body->vertices[1] = {55.0f, 40.0f};
	body->vertices[2] = {95.0f, 40.0f};
	body->vertices[3] = {70.0f, 60.0f};
	body->vertices[4] = {80.0f, 60.0f};
	body->vertices[5] = {40.0f, 90.0f};
	body->vertices[6] = {110.0f, 90.0f};

	velocity = {0.0f, 0.0f};

	drawBufferData = inDrawBufferData;
}

void Ship::updateAndDraw() {
	for(int i = 0; i < body->numberOfVertices; i++) {
		body->vertices[i].x += velocity.x;
		body->vertices[i].y += velocity.y;
	}

	drawTriangleStrip(drawBufferData, body);
}

Point Ship::getCenter() {
	float xSum = 0.0f;
	float ySum = 0.0f;
	for(int i = 0; i < body->numberOfVertices; i++) {
		xSum += body->vertices[i].x;
		ySum += body->vertices[i].y;
	}
	Point center;
	center.x = xSum / body->numberOfVertices;
	center.y = ySum / body->numberOfVertices;

	return center;
}

void Ship::moveToCenter() {
	Point centerOfScreen;
	centerOfScreen.x = (float)drawBufferData->width / 2.0f;
	centerOfScreen.y = (float)drawBufferData->height / 2.0f;
	Point centerOfShip = getCenter();

	for(int i = 0; i < body->numberOfVertices; i++) {
		body->vertices[i].x = centerOfScreen.x + (centerOfShip.x - body->vertices[i].x);
		body->vertices[i].y = centerOfScreen.y + (centerOfShip.y - body->vertices[i].y);
	}

	velocity.x = 0.0f;
	velocity.y = 0.0f;
}

void Ship::moveForward(float thrust) {
	Point center = getCenter();
	Vector forwardVector;
	forwardVector.x = body->vertices[0].x - center.x;
	forwardVector.y = body->vertices[0].y - center.y;
	float distance = sqrt((forwardVector.x * forwardVector.x) + (forwardVector.y * forwardVector.y));
	Vector unitVector;
	unitVector.x = forwardVector.x / distance;
	unitVector.y = forwardVector.y / distance;

	velocity.x += unitVector.x * thrust;
	velocity.y += unitVector.y * thrust;
	/*
	for(int i = 0; i < body->numberOfVertices; i++) {
		body->vertices[i].x += thrust * unitVector.x;
		body->vertices[i].y += thrust * unitVector.y;
	}
	*/
}

void Ship::rotate(float angle) {
	Point center = getCenter();

	for(int i = 0; i < body->numberOfVertices; i++) {
		body->vertices[i].x -= center.x;
		body->vertices[i].y -= center.y;

		float tempX = cos(angle) * body->vertices[i].x + sin(angle) * body->vertices[i].y;
		float tempY = -sin(angle) * body->vertices[i].x + cos(angle) * body->vertices[i].y;
		body->vertices[i].x = tempX + center.x;
		body->vertices[i].y = tempY + center.y;
	}
}