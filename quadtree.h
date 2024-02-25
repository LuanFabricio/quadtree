#ifndef QUADTREE_H_
#define QUADTREE_H_

#include "./platform.h"
#include "./defines.h"
#include "./types.h"
#include "./mm.h"

#define QUADTREE static

QUADTREE QuadTree *QuadTree_new(float x, float y, float half_dimension);
QUADTREE void QuadTree_subdivide(QuadTree *root);
QUADTREE boolean QuadTree_insert(QuadTree *root, Point p);
QUADTREE void QuadTree_display(const QuadTree *root);

#ifdef QUADTREE_IMPLEMENTATION
#define AABB_IMPLEMENTATION
#include "./aabb.h"

QUADTREE QuadTree *QuadTree_new(float x, float y, float half_dimension)
{
	AABB node = {
		.center = {
			.x = x,
			.y = y,
		},
		.half_dimension = half_dimension,
	};

	QuadTree *q_ptr = (QuadTree*) mm_malloc(sizeof(QuadTree));
	if (q_ptr) {
		q_ptr->node = node;
		q_ptr->points_size = 0;
		for (unsigned int i = 0; i < NODE_CAPACITY; i++) {
			q_ptr->points[i].x = 0;
			q_ptr->points[i].y = 0;
		}
		q_ptr->north_west = NULL;
		q_ptr->north_east = NULL;
		q_ptr->south_west = NULL;
		q_ptr->south_east = NULL;

		return q_ptr;
	}

	return NULL;
}

QUADTREE void QuadTree_subdivide(QuadTree *root)
{
	float x, y, half_dimension = root->node.half_dimension / 2.0;
	x = root->node.center.x - half_dimension;
	y = root->node.center.y - half_dimension;
	root->north_west = QuadTree_new(x, y, half_dimension);

	x = root->node.center.x + half_dimension;
	y = root->node.center.y - half_dimension;
	root->north_east = QuadTree_new(x, y, half_dimension);

	x = root->node.center.x - half_dimension;
	y = root->node.center.y + half_dimension;
	root->south_west = QuadTree_new(x, y, half_dimension);

	x = root->node.center.x + half_dimension;
	y = root->node.center.y + half_dimension;
	root->south_east = QuadTree_new(x, y, half_dimension);
}

QUADTREE boolean QuadTree_insert(QuadTree *root, Point p)
{
	if (!AABB_contains_point(root->node, p)) {
		return false;
	}

	if (root->points_size < NODE_CAPACITY && root->north_west == NULL) {
		root->points[root->points_size] = p;
		root->points_size += 1;
		return true;
	}

	if(root->north_west == NULL) {
		QuadTree_subdivide(root);
	}

	if (QuadTree_insert(root->north_west, p)) return true;
	if (QuadTree_insert(root->north_east, p)) return true;
	if (QuadTree_insert(root->south_west, p)) return true;
	if (QuadTree_insert(root->south_east, p)) return true;

	return false;
}

#define NODE_COLOR 0xf0f0f0ff
#define POINT_COLOR 0xff0000ff
QUADTREE void QuadTree_display(const QuadTree *root)
{
	if (root == NULL) return;

	AABB_display(root->node);

	for (u32 i = 0; i < root->points_size; i++) {
		Platform_draw_rectangle(
				root->points[i].x,
				root->points[i].y,
				2.0, 2.0, POINT_COLOR);
	}

	QuadTree_display(root->north_west);
	QuadTree_display(root->north_east);
	QuadTree_display(root->south_west);
	QuadTree_display(root->south_east);
}

//QUADTREE void QuadTree_print(const QuadTree *root)
//{
//	printf("Root: { %.2f, %.2f } %.2f\n", root->node.center.x, root->node.center.y, root->node.half_dimension);
//	if (root->points_size > 0){
//		printf("Points: \n");
//	}
//	for (size_t i = 0; i < root->points_size; i++) {
//		Point p = root->points[i];
//		printf("\t[%lu]: { %.2f, %.2f }\n", i, p.x, p.y);
//	}
//
//	if (root->north_west) {
//		printf("North west:\n");
//		QuadTree_print(root->north_west);
//	}
//
//	if (root->north_east) {
//		printf("North east:\n");
//		QuadTree_print(root->north_east);
//	}
//
//	if (root->south_west) {
//		printf("South west:\n");
//		QuadTree_print(root->south_west);
//	}
//
//	if (root->south_east) {
//		printf("South east:\n");
//		QuadTree_print(root->south_east);
//	}
//}
#endif // QUADTREE_IMPLEMENTATION

#endif // QUADTREE_H_
