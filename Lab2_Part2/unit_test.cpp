#include "hash_map.h"
#include <iostream>
#include <string>
#include <assert.h>
#include <stdlib.h>
#include<time.h>
#include <stdbool.h>

#define TWO_TIMES_MAX_CAP 2 * 2039

#define log_success() std::cout<<__func__<<" passed\n"
#define log_int(arg) printf("%s == %d\n", #arg, arg)
#define log_size_t(arg) printf("%s == %ld\n", #arg, arg)
#define log_float(arg) printf("%s == %f\n", #arg, arg);

template<typename K> void print_array(K *array, size_t length) {
	for(size_t i = 0; i < length; i++) {
		std::cout << "array[" << i << "] == " << array[i] << std::endl;
	}
}

using std::string;

void test_init_int_float_empty(){
	hash_map <int, float>map(0, 0.75, 0.25);
	assert(map.get_size() == 0);
	assert(map.get_capacity() == 0);
	log_success();
}

void test_init_char_str_empty() {
	hash_map <char, string>map(0, 0.75, 0.25);
	assert(map.get_size() == 0);
	assert(map.get_capacity() == 0);
	log_success();
}

void test_orig_init_three(){
	hash_map<int,float> map(3, 0.75, 0.25);
	map.insert(1,1.1);
	map.insert(2,2.1);
	map.insert(3,3.1);

	assert(map.get_capacity() == 209);
	assert(map.get_size() == 3);
	assert(map.get_value(1) == (float) 1.1);
	assert(map.get_value(2) == (float) 2.1);
	assert(map.get_value(3) == (float) 3.1);
	log_success();
}

void test_rand_type_init_three() {
	hash_map<char, string> map(3, 0.75, 0.25);
	map.insert('a',"apple");
	map.insert('b',"bad");
	map.insert('c',"cat");

	assert(map.get_capacity() == 209);
	assert(map.get_size() == 3);
	assert(map.get_value('a') == "apple");
	assert(map.get_value('b') == "bad");
	assert(map.get_value('c') == "cat");
	log_success();
}

void test_equal_operator(){
	hash_map<int, float> map1(2, 0.75, 0.25);
	hash_map<int, float> map2(3, 0.75, 0.25);

	map1.insert(1,1);
	map1.insert(2,1);
	assert(map1.get_capacity() == 209);

	map2.insert(3,2);

	map2 = map1;
	assert(map2.get_size() == map1.get_size());
	assert(map2.get_value(1) == map1.get_value(1));
	assert(map2.get_value(2) == map1.get_value(2));
	assert(map2.get_value(3).has_value() == map1.get_value(3).has_value());

	log_success();
}

void test_A_eq_B_eq_C() {
	hash_map<int, float> map1(2, 0.75, 0.25);
	hash_map<int, float> map2(3, 0.75, 0.25);
	hash_map<int, float>map3(1, 0.75, 0.25);


	map1.insert(1,1);
	map1.insert(2,1);
	assert(map1.get_capacity() == 209);
	map2.insert(3,2);
	map3.insert(4,2);
	assert(map3.get_capacity() == 209);

	map1 = (map2 = map3);

	assert(map1.get_capacity() == map3.get_capacity() && map2.get_capacity() == map3.get_capacity());
	assert(map1.get_size() == map3.get_size() && map2.get_size() == map3.get_size());
	assert(map1.get_value(4).has_value() && map2.get_value(4).has_value() && map3.get_value(4).has_value());
	assert(map1.get_value(4).value() == map2.get_value(4).value() && map1.get_value(4).value() ==  map3.get_value(4).value());
	log_success();
}

void test_remove() {
	hash_map <int, float> map(1021, 1.2, 0.004);
	map.insert(1, 2.2);
	map.insert(2, 4.4);
	map.insert(4, 8);
	map.insert(3, -9);

	assert(map.remove(4));
	log_size_t(map.get_capacity());
	assert(map.get_capacity() == 209);
	assert(map.get_size() == 3);
	assert(map.get_value(4).has_value() == false);

	assert(map.remove(2));
	assert(map.get_capacity() == 209);
	assert(map.get_size() == 2);
	assert(map.get_value(2).has_value() == false);

	assert(map.remove(9) == false);
	assert(map.get_capacity() == 209);
	assert(map.get_size() == 2);
	assert(map.get_value(1).has_value());

	assert(map.get_value(1).value() == (float) 2.2);
	assert(map.get_value(3).value() == (float) -9);

	log_success();
}

void test_insert_to_more_than_max_size(){
	hash_map<int, float> map(3, 1.2, 0.45);

	srand(time(NULL));
	size_t capacities[] = {209, 1021, 2039};
	for(int key = 0; key < TWO_TIMES_MAX_CAP; key++) {
		map.insert(key, (rand()%TWO_TIMES_MAX_CAP) / 6371);
		if(key == 3) {
			assert(map.get_capacity() == 209);	
		}
		if(key == 250) {
			assert(map.get_capacity() == 1021);
		}
		if(key >= 1227) {
			assert(map.get_capacity() == 2039);
		}
	}

	assert(map.get_size() == TWO_TIMES_MAX_CAP);
	assert(map.get_capacity() == capacities[2]);

	log_success();
}

void test_insert_duplicate() {
	hash_map<int, float> map(3, 1.2, 0.45);
	for(int i = 0; i < 4; i++) {
		map.insert(1,0.5);
	}
	assert(map.get_size() == 1);
	log_size_t(map.get_capacity());
	// assert(map.get_capacity() == 3);
	int *keys = new int[map.get_capacity()];

	delete [] keys;
	log_success();
}

void test_get_all_keys() {
	hash_map<int,float> map(3, 0.75, 0.25);
	map.insert(1, 2.2);
	map.insert(2, 4.4);
	map.insert(4, 8);
	map.insert(3, -9);

	assert(map.get_capacity() == 209);
	assert(map.get_size() == 4);
	int *keys = new int[map.get_size()];
	map.get_all_keys(keys);

	//print_array<int>(keys, map.get_size());
	assert(keys[0] == 1);
	assert(keys[1] == 2);
	assert(keys[2] == 3);
	assert(keys[3] == 4);
	delete [] keys;
	log_success();
}

void test_get_bucket_size() {

	hash_map<int,float> map(3, 0.75, 0.25);
	map.insert(1, 2.2);
	map.insert(2, 4.4);
	map.insert(4, 8);
	map.insert(3, -9);

	size_t *bucket_sizes = new size_t [map.get_capacity()];
	map.get_bucket_sizes(bucket_sizes);

	for(size_t i = 0; i < map.get_capacity(); i++) {
		if(i == 1 || i == 2 || i == 3 || i == 4) {
			assert(bucket_sizes[i] == 1);
		}
		else {
			assert(bucket_sizes[i] == 0);
		}
	}

	delete [] bucket_sizes;
	log_success();
}

void test_get_all_sorted_keys() {
	hash_map<int,float> map(209, 0.75, 0.25);
	srand(time(NULL));
	size_t capacity_before_rehash = map.get_capacity(); 
	for(size_t i = 0; i < capacity_before_rehash; i++) {
		//fill in the map
		map.insert(i, (rand()%1000)/251);
	}
	log_size_t(map.get_capacity());
	assert(map.get_capacity() == 1021);
	
	int *keys = new int[map.get_size()];
	map.get_all_sorted_keys(keys);

	//print_array<int>(keys, map.get_size());

	for(int i = 0; i < 209; i++) {
		assert(keys[i] == i);
	}

	delete [] keys;
	log_success();
}

int main(int argc, char* argv[]) {
	test_init_int_float_empty();
	test_init_char_str_empty();
	test_orig_init_three();
	test_rand_type_init_three();
	test_equal_operator();
	test_A_eq_B_eq_C();
	test_remove();
	test_get_all_keys();
	test_get_bucket_size();
	test_get_all_sorted_keys();
	test_insert_duplicate();
	test_insert_to_more_than_max_size();
	return EXIT_SUCCESS;
}
