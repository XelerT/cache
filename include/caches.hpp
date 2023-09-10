#pragma once

#include "ideal.hpp"
#include "two_q.hpp"

int  check_data_in_2q_cache   (caches::two_q<int> &cache, int *data, size_t n_data_elements);
int check_data_in_ideal_cache (caches::ideal<int> &cache, int *data, size_t n_data_elements);
int  hash_data                (int data);