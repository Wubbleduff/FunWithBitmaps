#include "ShapeRender.h"

void drawTriangle(DrawBufferData *drawBufferData, Point p1, Point p2, Point p3, Color color) {
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
void drawPolygon(DrawBufferData *drawBufferData, GamePolygon *polygon) {
	if(polygon->numberOfVertices < 3) return;

	int i = 1;
	while(i + 1 <= polygon->numberOfVertices - 1) {
		// Draw a triangle between the first vertex, i, and i + 1 until you have drawn a triangle between all vertices
		drawTriangle(drawBufferData, polygon->vertices[0], polygon->vertices[i], polygon->vertices[i + 1], polygon->color);
		i++;
	}
}

// Draws a polygon by drawing each new triangle between the 2 previous points and a new point
void drawTriangleStrip(DrawBufferData *drawBufferData, GamePolygon *polygon) {
	if(polygon->numberOfVertices < 3) return;

	drawTriangle(drawBufferData, polygon->vertices[0], polygon->vertices[1], polygon->vertices[2], polygon->color);
	int i = 2;
	while(i < polygon->numberOfVertices - 1) {
		drawTriangle(drawBufferData, polygon->vertices[i - 1], polygon->vertices[i], polygon->vertices[i + 1], polygon->color);
		i++;
	}
}
