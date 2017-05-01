#include "Render.h"
#include <string.h>
#include <math.h>

Render::Render(uint32 *inPDrawBuffer, int inDrawBufferWidth, int inDrawBufferHeight) {
	drawBufferData = new DrawBufferData();
	drawBufferData->buffer = inPDrawBuffer;
	drawBufferData->width = inDrawBufferWidth;
	drawBufferData->height = inDrawBufferHeight;
	//changeDrawBufferDimensions(inPDrawBuffer, inDrawBufferWidth, inDrawBufferHeight);

	ship = new Ship(drawBufferData);
}

/*
void Render::changeDrawBufferDimensions(uint32 *inPDrawBuffer, int inDrawBufferWidth, int inDrawBufferHeight) {
	drawBufferData->buffer = inPDrawBuffer;
	drawBufferData->width = inDrawBufferWidth;
	drawBufferData->height = inDrawBufferHeight;
}
*/

void spinPoint( Point pt, Point center, float angle, Point * outPt ) {
	float  x = pt.x - center.x;
	float y = pt.y - center.y;

	outPt->x =  cos(angle)*x + sin(angle)*y;
	outPt->y = -sin(angle)*x + cos(angle)*y;
	outPt->x += center.x;
	outPt->y += center.y;
}

void Render::draw(GameInput input) {
	memset(drawBufferData->buffer, 0, drawBufferData->width * drawBufferData->height * 4);

	float turnAmount = 0.5f;
	if(input.leftDown) {
		ship->rotate(PI / 180.0f * turnAmount);
	}
	if(input.rightDown) {
		ship->rotate(PI / 180.0f * -turnAmount);
	}
	if(input.upDown) {
		ship->moveForward(0.01f);
	}
	if(input.downDown) {
		ship->moveForward(-0.01f);
	}
	if(input.spaceDown) {
		ship->moveToCenter();
	}

	ship->updateAndDraw();
}