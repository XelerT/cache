#pragma once

#include <vector>
#include <utility>

enum USER_ARGS_INDEXES {
        CACHE_CAPACITY_ARG_INDEX = 1,
        N_DATA_ELEMENT_INDEX     = 2,
        FIRST_DATA_ELEMENT_INDEX = 3
};

enum USER_DATA {
        RUN_2Q_CACHE,
        RUN_IDEAL_CACHE
};

int check_user_args (int argc, char **args);
std::pair<size_t, std::vector<int>> get_input_data ();