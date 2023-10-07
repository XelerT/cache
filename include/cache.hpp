#pragma once

#include <vector>
#include <utility>

#include "ui.hpp"

int     hash_data          (int data);
size_t run_cache (std::pair<size_t, std::vector<int>> input, const int cache2run);
