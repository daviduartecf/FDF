#include "../../minunit/minunit.h"
#include "../fdf.h"
#include "tester.h"

MU_TEST(width_test_2x2_0_map)
{
	t_map *map;
	int expected_width = 2;
	int actual_width = 0;

	map = read_map("../my_maps/2x2map.txt");
	if (!map)
	{
		printf("error opening file");
		mu_assert_int_eq(expected_width, actual_width);
		return;
	}
	actual_width = map->width;
	mu_assert_int_eq(expected_width, actual_width);
}

MU_TEST(width_test_1x1_0_map)
{
	t_map *map;
	int expected_width = 1;
	int actual_width = 0;

	map = read_map("../my_maps/1x1map.txt");
	if (!map)
	{
		printf("error opening file");
		mu_assert_int_eq(expected_width, actual_width);
		return;
	}
	actual_width = map->width;
	mu_assert_int_eq(expected_width, actual_width);
}

MU_TEST(file_not_existing_test)
{
	t_map *map;

	map = read_map("../my_maps/nofile");
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
	int actual_width= 0;

	map = read_map("../my_maps/negative1x1map.txt");
	if (!map)
	{
		printf("error opening file");
		mu_assert_int_eq(expected_width, actual_width);
		return;
	}
	actual_width = map->width;
	mu_assert_int_eq(expected_width, actual_width);
}

MU_TEST(width_test_3x3_negative_map)
{
	t_map *map;
	int expected_width = 3;
	int actual_width = 0;

	map = read_map("../my_maps/negative3x3map.txt");
	if (!map)
	{
		printf("error opening file");
		mu_assert_int_eq(expected_width, actual_width);
		return;
	}
	actual_width = map->width;
	mu_assert_int_eq(expected_width, actual_width);
}

MU_TEST(width_test_2x2_largeint_map)
{
	t_map *map;
	int expected_width = 2;
	int actual_width = 0;

	map = read_map("../my_maps/largeint2x2map.txt");
	if (!map)
	{
		printf("error opening file");
		mu_assert_int_eq(expected_width, actual_width);
		return;
	}
	actual_width = map->width;
	mu_assert_int_eq(expected_width, actual_width);
}

MU_TEST(width_test_2x2_negative_largeint_map)
{
	t_map *map;
	int expected_width = 2;
	int actual_width = 0;

	map = read_map("../my_maps/negativelargeint2x2map.txt");
	if (!map)
	{
		printf("error opening file");
		mu_assert_int_eq(expected_width, actual_width);
		return;
	}
	actual_width = map->width;
	mu_assert_int_eq(expected_width, actual_width);
}

MU_TEST(width_test_2x1_wronglines_map)
{
	t_map *map;
	int expected_width = 2;
	int actual_width = 0;

	map = read_map("../my_maps/wronglinenumber2x1map.txt");
	if (!map)
	{
		mu_assert(width_test_2x1_wronglines_map, "Lines are not equal!");
		return;
	}
	mu_fail("Error: Lines were not equal in the map and it assumed as they were!");
}

MU_TEST(empty_map_test)
{
	t_map *map;

	map = read_map("../my_maps/emptymap.txt");
	if (!map)
	{
		mu_assert(width_test_2x1_wronglines_map, "Empty map!");
		return;
	}
	mu_fail("Error: Empty map should not be read!");
}

MU_TEST(width_test_2x2_above_int_limit_map)
{
	t_map *map;
	int expected_width = 2;
	int actual_width = 0;

	map = read_map("../my_maps/biggerthanint2x2map.txt");
	if (!map)
	{
		printf("error opening file");
		mu_assert_int_eq(expected_width, actual_width);
		return;
	}
	actual_width = map->width;
	mu_assert_int_eq(expected_width, actual_width);
}

MU_TEST(chars_in_input_map)
{
	t_map *map;

	map = read_map("../my_maps/chars2x2map.txt");
	if (!map)
	{
		mu_assert(chars_in_input_map, "Chars detected on input");
		return;
	}
	mu_fail("Chars in file and the file opened");
}

MU_TEST(random_ascii_chars_in_input_map)
{
	t_map *map;

	map = read_map("../my_maps/randomchars4x4map.txt");
	if (!map)
	{
		mu_assert(chars_in_input_map, "Chars detected on input");
		return;
	}
	mu_fail("Chars in file and the file opened");
}

MU_TEST_SUITE(test_suite)
{
	MU_RUN_TEST(file_not_existing_test);
	MU_RUN_TEST(width_test_1x1_0_map);
	MU_RUN_TEST(width_test_2x2_0_map);
	MU_RUN_TEST(width_test_1x1_negative_map);
 	MU_RUN_TEST(width_test_3x3_negative_map);
	MU_RUN_TEST(width_test_2x2_largeint_map);
	MU_RUN_TEST(width_test_2x2_negative_largeint_map);
	MU_RUN_TEST(width_test_2x1_wronglines_map);
	MU_RUN_TEST(empty_map_test);
	MU_RUN_TEST(chars_in_input_map);
	MU_RUN_TEST(random_ascii_chars_in_input_map);
	MU_RUN_TEST(width_test_2x2_above_int_limit_map);
}

int main(int argc, char *argv[])
{
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
