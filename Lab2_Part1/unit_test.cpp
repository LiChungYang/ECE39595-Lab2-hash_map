#include "hash_map.h"
#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#define log_success() std::cout<<__func__<<" passed\n"
#define log_int(arg) printf("%s == %d\n", #arg, arg)
#define log_size_t(arg) printf("%s == %ld\n", #arg, arg)
#define log_float(arg) printf("%s == %f\n", #arg, arg);


void test_init_empty(){
	hash_map map(0);
	assert(map.get_size() == 0);
	assert(map.get_capacity() == 0);
	log_success();
}

void test_init_three(){
	hash_map map(3);
	assert(map.get_capacity() == 3);
	assert(map.get_size() == 0);
	log_success();
}

void test_insert_to_table(){
	hash_map map(3);
	map.insert(1,1);
	map.insert(4,2);

	assert(map.get_size() == 2);
	log_success();
}

void test_insert_duplicate() {
	hash_map map(3);
	map.insert(1,1);
	map.insert(4,2);
	map.insert(1, 1.1);

	assert(map.get_capacity() == 3);
	assert(map.get_size() == 2);
	assert(map.get_value(1) == (float) 1.1);
	assert(map.get_value(4) == (float) 2);
	
	log_success();
}

void test_copy_constructor(){
	hash_map map(3);
	map.insert(1,1);
	map.insert(4,2);

	hash_map map_cpy(map);
	assert(map.get_size() == 2);
	assert(map_cpy.get_value(1) == map.get_value(1));
	assert(map_cpy.get_value(4) == map.get_value(4));
	log_success();
}

void test_equal_operator(){
	hash_map map1(2);
	hash_map map2(3);

	map1.insert(1,1);
	map1.insert(2,1);

	map2.insert(3,2);

	map2 = map1;
	assert(map2.get_size() == map1.get_size());
	assert(map2.get_value(1) == map1.get_value(1));
	assert(map2.get_value(2) == map1.get_value(2));
	assert(map2.get_value(3).has_value() == map1.get_value(3).has_value());

	log_success();
}

void test_A_eq_B_eq_C(){
	hash_map map1(2);
	hash_map map2(3);
	hash_map map3(0);

	map1.insert(1,1);
	map1.insert(2,1);
	map2.insert(3,2);
	map3 = map2 = map1;


	assert(map1.get_capacity() == map2.get_capacity());
	assert(map2.get_capacity() == map3.get_capacity());
	assert(map1.get_capacity() == map3.get_capacity());

	assert(map1.get_size() == map2.get_size());
	assert(map2.get_size() == map3.get_size());
	assert(map1.get_size() == map3.get_size());


	assert(map1.get_value(1) == map2.get_value(1));
	assert(map2.get_value(1) == map3.get_value(1));
	assert(map1.get_value(1) == map3.get_value(1));

	assert(map1.get_value(2) == map2.get_value(2));
	assert(map2.get_value(2) == map3.get_value(2));
	assert(map1.get_value(2) == map3.get_value(2));

	assert(map1.get_value(3) == map2.get_value(3));
	assert(map2.get_value(3) == map3.get_value(3));
	assert(map1.get_value(3) == map3.get_value(3));

	log_success();
}

 void test_remove() {
	hash_map map(3);
	map.insert(1, 2.2);
	map.insert(2, 4.4);
	map.insert(4, 8);
	map.insert(3, -9);

	assert(map.remove(4));
	assert(map.get_size() == 3);
	assert(map.get_value(4).has_value() == false);

	assert(map.remove(2));
	assert(map.get_size() == 2);
	assert(map.get_value(2).has_value() == false);

	assert(map.remove(9) == false);
	assert(map.get_size() == 2);
	assert(map.get_value(1).has_value());

	float key_1_val = 2.2;	//use a variable here to avoid truncation error in asserts
	float key_3_val = -9;	//use a variable here to avoid truncation error in asserts

	assert(map.get_value(1).value() == key_1_val);
	assert(map.get_value(3).value() == key_3_val);

	log_success();
}

void test_get_bucket_size() {
	hash_map map(3);
	map.insert(1, 2.2);
	map.insert(2, 4.4);
	map.insert(4, 8);
	map.insert(3, -9);

	size_t *bucket_sizes = new size_t [map.get_size()];
	map.get_bucket_sizes(bucket_sizes);

	assert(bucket_sizes[0] == 1);
	assert(bucket_sizes[1] == 2);
	assert(bucket_sizes[2] == 1);

	delete [] bucket_sizes;
	log_success();
}

void test_get_all_keys() {
	hash_map map(3);
	map.insert(1, 2.2);
	map.insert(2, 4.4);
	map.insert(4, 8);
	map.insert(3, -9);

	int *keys = new int[map.get_size()];
	map.get_all_keys(keys);

	// for(size_t i = 0 ; i < map.get_size(); i++) {
	// 	log_int(keys[i]);
	// }

	assert(keys[0] == 3);
	assert(keys[1] == 1);
	assert(keys[2] == 4);
	assert(keys[3] == 2);
	delete [] keys;
	log_success();
}

int main(int argc, char* argv[]) {
	test_init_empty();
	test_init_three();
	test_insert_to_table();
	test_insert_duplicate();
	test_copy_constructor();
	test_equal_operator();
	test_A_eq_B_eq_C();
	test_remove();
	test_get_bucket_size();
	test_get_all_keys();
	return EXIT_SUCCESS;
}
