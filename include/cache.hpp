#pragma once

#include <vector>

#include "ui.hpp"

template <typename T>
size_t check_data_in_cache (T &cache, std::vector<int> &data);
int     hash_data          (int data);
size_t  run_cache          (input_data_t &inputted_data, int cache2run);
