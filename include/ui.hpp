#pragma once

#include <vector>

enum USER_ARGS_INDEXES {
        CACHE_CAPACITY_ARG_INDEX = 1,
        N_DATA_ELEMENT_INDEX     = 2,
        FIRST_DATA_ELEMENT_INDEX = 3
};

enum USER_DATA {
        RUN_2Q_CACHE,
        RUN_IDEAL_CACHE
};

struct input_data_t 
{
        public:
                std::vector<int> data_;
                size_t cache_capacity_;
                size_t n_data_elements_;

                input_data_t ();
};

int check_user_args (int argc, char **args);