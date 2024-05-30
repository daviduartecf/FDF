#include "../minunit/minunit.h"
#include "fdf.h"
#include "tester.h"

MU_TEST(width_test_2x2_0_map)
{
	t_map *map;
	int expected_width = 2;
	int actual_width;

	map = read_map("my_maps/2x2map.txt");
	if (!map)
	{
		printf("error opening file");
		return;
	}
	actual_width = map->width;
	mu_assert_int_eq(expected_width, actual_width);
}

MU_TEST(width_test_1x1_0_map)
{
	t_map *map;
	int expected_width = 1;
	int actual_width;

	map = read_map("my_maps/1x1map.txt");
	if (!map)
	{
		printf("error opening file");
		return;
	}
	actual_width = map->width;
	mu_assert_int_eq(expected_width, actual_width);
}

MU_TEST(file_not_existing_test)
{
	t_map *map;

	map = read_map("my_maps/nofile");
	if (!map)
	{
		//printf("error opening file");
		mu_assert(file_not_existing_test, "No file!");
		return;
	}
	else
		mu_fail("Opened no file!");
}

MU_TEST(width_test_1x1_negative_map)
{
	t_map *map;
	int expected_width = 1;
	int actual_width;

	map = read_map("my_maps/negative1x1map.txt");
	if (!map)
	{
		printf("error opening file");
		return;
	}
	actual_width = map->width;
	mu_assert_int_eq(expected_width, actual_width);
}

MU_TEST_SUITE(test_suite)
{
	MU_RUN_TEST(file_not_existing_test);
	MU_RUN_TEST(width_test_1x1_0_map);
	MU_RUN_TEST(width_test_2x2_0_map);
	MU_RUN_TEST(width_test_1x1_negative_map);
}

int main(int argc, char *argv[])
{
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
