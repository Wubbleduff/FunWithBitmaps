#include "Render.h"
#include <string.h>
#include <math.h>

Render::Render(uint32 *inPDrawBuffer, int inDrawBufferWidth, int inDrawBufferHeight) {
	drawBufferData = new DrawBufferData();
	drawBufferData->buffer = inPDrawBuffer;
	drawBufferData->width = inDrawBufferWidth;
	drawBufferData->height = inDrawBufferHeight;
	//changeDrawBufferDimensions(inPDrawBuffer, inDrawBufferWidth, inDrawBufferHeight);

	ship = new Ship();
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

	// Triangle
	/*
	spinAngle += 0.001f;
	Point Ap1, Ap2, Ap3;
	Point center = {600, 340};
	Point p13 = {400, 500};
	Point p14 = {1200, 950};
	Point p15 = {950, 1350};
	Color color = {255, 255, 0};
	spinPoint(p13, center, spinAngle, &Ap1);
	spinPoint(p14, center, spinAngle, &Ap2);
	spinPoint(p15, center, spinAngle, &Ap3);
	drawTriangle(Ap1, Ap2, Ap3, color);
	*/

	/*
#define NV 200
	GamePolygon p = {};
	p.color = {0, 0, 255};
	p.numberOfVertices = NV;
	Point vertices[NV] = {};
	p.vertices = vertices;
	Point centerOfP = {900, 500};
	int radius = 400;
	float t = 0;
	for(int i = 0; i < p.numberOfVertices; i++) {
		Point vertex;
		vertex.x = cos(t) * radius + centerOfP.x;
		vertex.y = -sin(t) * radius + centerOfP.y;
		p.vertices[i] = vertex;
		t += (2.0f * PI) / (float)p.numberOfVertices;
	}
	drawPolygon(p);
	*/
	if(input.leftDown) {
		ship->rotate(-0.1f);
	}
	if(input.rightDown) {
		ship->rotate(0.1f);
	}
	if(input.upDown) {
		ship->move(0, -1);
	}
	if(input.downDown) {
		ship->move(0, 1);
	}

	ship->draw(drawBufferData);

	/*
#define BLOB_SIZE (6)
#define BLOB_DIAMETER (500)
	GamePolygon blob = {};
	blob.color = {0, 255, 0};
	blob.numberOfVertices = BLOB_SIZE;
	Point blobVertices[BLOB_SIZE] = {};
	blob.vertices = blobVertices;
	for(int i = 0; i < BLOB_SIZE; i++) {
		blob.vertices[i] = {rand() % BLOB_DIAMETER, rand() % BLOB_DIAMETER};
	}
	drawTriangleStrip(blob);
	*/
}

/*
void Render::drawTriangle(Point p1, Point p2, Point p3, Color color) {
	Point topPoint = p1;
	Point midPoint = p2;
	Point bottomPoint = p3;

	// Order the points top to bottom
	if(midPoint.y < topPoint.y) {
		Point tempPoint = topPoint;
		topPoint = midPoint;
		midPoint = tempPoint;
	}
	if(bottomPoint.y < topPoint.y) {
		Point tempPoint = topPoint;
		topPoint = bottomPoint;
		bottomPoint = tempPoint;
	}
	if(bottomPoint.y < midPoint.y) {
		Point tempPoint = bottomPoint;
		bottomPoint = midPoint;
		midPoint = tempPoint;
	}

	// Now, after we have ordered points, ensure that if the top and mid
	// have same y value, the top point is always the left one.
	if((topPoint.y == midPoint.y) && (topPoint.x > midPoint.x)) {
		Point tempPoint = topPoint;
		topPoint = midPoint;
		midPoint = tempPoint;
	}

	// Nothing to draw
	if( bottomPoint.y < (topPoint.y+1.0f) ) {
		return;
	}

	float leftX, rightX;
	uint32 *pixel = drawBufferData->buffer;
	uint32 colorToSet = (color.r << 16) | (color.g << 8) | color.b;

	// Draw the top half of the triangle
	float invLeftSlope, invRightSlope;
    if( (int)topPoint.y < (int)midPoint.y ) {
		invLeftSlope = (float)((int)midPoint.x - (int)topPoint.x) / (float)((int)midPoint.y - (int)topPoint.y);
		invRightSlope = (float)((int)bottomPoint.x - (int)topPoint.x) / (float)((int)bottomPoint.y - (int)topPoint.y);

		if( invRightSlope < invLeftSlope ) {
			float tmpSlope = invRightSlope;
			invRightSlope = invLeftSlope;
			invLeftSlope = tmpSlope;
		}

		leftX = topPoint.x;
		rightX = topPoint.x;

		for(int y = topPoint.y; y < midPoint.y; y++) {
			// Draw a line between the points
			if( (y >= 0) && (y < drawBufferData->height)) {
				for(int x = leftX; x < rightX; x++) {
					if( (x >= 0) && (x < drawBufferData->width) ) {
						pixel[y * drawBufferData->width + x] = colorToSet;	
					}
				}
			}
			leftX += invLeftSlope ;
			rightX += invRightSlope;
		}
	}

	// Draw the bottom half of the triangle
	if( (int)midPoint.y < (int)bottomPoint.y ) {
		invLeftSlope = (float)((int)bottomPoint.x - (int)midPoint.x) / (float)((int)bottomPoint.y - (int)midPoint.y);
		invRightSlope = (float)((int)bottomPoint.x - (int)topPoint.x) / (float)((int)bottomPoint.y - (int)topPoint.y);

		leftX = midPoint.x;
		// For some reason, we have to add one to rightX because the calculation is off by 1 (I think)
		// I don't know if this is the correct fix or not
		rightX = (int)(((int)midPoint.y - (int)topPoint.y)*invRightSlope  + (int)topPoint.x);
		rightX++;

		if( rightX < leftX ) {
			leftX = rightX;
			rightX = midPoint.x;
			float tmpSlope = invLeftSlope;
			invLeftSlope = invRightSlope;
			invRightSlope = tmpSlope;
		}

		for(int y = midPoint.y; y < bottomPoint.y; y++) {
			// Draw a line between the points
			if( (y >= 0) && (y < drawBufferData->height)) {
				for(int x = leftX; x < rightX; x++) {
					if( (x >= 0) && (x < drawBufferData->width) ) {
						pixel[y * drawBufferData->width + x] = colorToSet;	
					}
				}
			}
			leftX += invLeftSlope;
			rightX += invRightSlope;
		}
	}
}

// Draws a polygon by picking a point and having all triangles in the polygon converge on that point
void Render::drawPolygon(GamePolygon *polygon) {
	if(polygon->numberOfVertices < 3) return;

	int i = 1;
	while(i + 1 <= polygon->numberOfVertices - 1) {
		// Draw a triangle between the first vertex, i, and i + 1 until you have drawn a triangle between all vertices
		drawTriangle(polygon->vertices[0], polygon->vertices[i], polygon->vertices[i + 1], polygon->color);
		i++;
	}
}

// Draws a polygon by drawing each new triangle between the 2 previous points and a new point
void Render::drawTriangleStrip(GamePolygon *polygon) {
	if(polygon->numberOfVertices < 3) return;

	drawTriangle(polygon->vertices[0], polygon->vertices[1], polygon->vertices[2], polygon->color);
	int i = 2;
	while(i < polygon->numberOfVertices - 1) {
		drawTriangle(polygon->vertices[i - 1], polygon->vertices[i], polygon->vertices[i + 1], polygon->color);
		i++;
	}
}

void Render::drawCircle(Point center, float radius) {
	for(int y = 0; y < radius * 2; y++) {
		for(int x = 0; x < radius * 2; x++) {

		}
	}
}
*/