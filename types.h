#ifndef TYPE_H_
#define TYPE_H_

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef int boolean;
#define false 0
#define true 1

#define NODE_CAPACITY 4

typedef struct {
	float x, y;
} Point;

typedef struct {
	Point center;
	float half_dimension;
} AABB;


typedef struct QuadTree QuadTree;
struct QuadTree {
	AABB node;
	u32 points_size;
	Point points[NODE_CAPACITY];
	QuadTree *north_west;
	QuadTree *north_east;
	QuadTree *south_west;
	QuadTree *south_east;
};

typedef struct {
	Point player;
	QuadTree objects;
} Game;

#endif // TYPE_H_
