#pragma once

#include "ui.hpp"

size_t  check_data_in_2q_cache    (caches::two_q<int> &cache, int *data, size_t n_data_elements);
size_t  check_data_in_ideal_cache (caches::ideal<int> &cache, int *data, size_t n_data_elements);
int     hash_data                 (int data);
size_t  run_cache                 (input_data_t *inputted_data, int cache2run);
