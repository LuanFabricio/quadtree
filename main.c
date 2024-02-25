#include "./platform.h"
#include "./mm.h"
#include "./types.h"

#define QUADTREE_IMPLEMENTATION
#include "./quadtree.h"

#define SCREEN_SIZE 800
#define SCREEN_HALF_SIZE (SCREEN_SIZE / 2.0f)

static QuadTree *root = NULL;

void draw_loop()
{
	Platform_begin_drawing();
		QuadTree_display(root);
	Platform_end_drawing();
}

int main()
{
	Platform_rand_seed();
	root = QuadTree_new(SCREEN_HALF_SIZE, SCREEN_HALF_SIZE, SCREEN_HALF_SIZE);

	int qpoints = 64;
	for (int i = 0; i < qpoints; i++) {
		QuadTree_insert(root,
				(Point) {
					Platform_rand_float_range(
							SCREEN_HALF_SIZE-root->node.half_dimension,
							SCREEN_HALF_SIZE+root->node.half_dimension),
					Platform_rand_float_range(
							SCREEN_HALF_SIZE-root->node.half_dimension,
							SCREEN_HALF_SIZE+root->node.half_dimension)
				});
	}

	Platform_init_window("Teste", SCREEN_SIZE, SCREEN_SIZE);

	mm_log();
#ifdef PLATFORM_WEB
	Platform_set_loop(draw_loop);
#else
	while (!Platform_window_should_close()) {
		draw_loop();
	}
#endif

	Platform_close_window();
	mm_clean();

	return 0;
}
