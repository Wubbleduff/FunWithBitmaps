#pragma once

typedef unsigned char uint8;
typedef unsigned int uint32;

#define PI 3.14159265359f

typedef struct {
	uint32 *buffer;
	int width;
	int height;
} DrawBufferData;

typedef struct {
	int cursorX;
	int cursorY;
	bool spaceDown;
	bool leftDown;
	bool rightDown;
	bool upDown;
	bool downDown;
} GameInput;

typedef struct {
	uint8 r;	
	uint8 g;	
	uint8 b;	
} Color;

typedef struct {
	float x;
	float y;
} Point;

typedef struct {
	int numberOfVertices;
	Point *vertices;
	Color color;
} GamePolygon;

typedef struct {
	float x;
	float y;
} Vector;