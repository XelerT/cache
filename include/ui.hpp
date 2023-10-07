#pragma once

#include <vector>
#include <utility>

enum class cache_type
{
        RUN_2Q_CACHE,
        RUN_IDEAL_CACHE,
        UNKNOWN_TYPE
};

cache_type check_user_args (int argc, char **args);
std::pair<size_t, std::vector<int>> get_input_data ();