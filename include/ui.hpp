#pragma once

enum USER_ARGS_INDEXES {
        CACHE_CAPACITY_ARG_INDEX = 1,
        N_DATA_ELEMENT_INDEX     = 2,
        FIRST_DATA_ELEMENT_INDEX = 3
};

enum USER_DATA {
        RUN_2Q_CACHE,
        RUN_IDEAL_CACHE
};

struct input_data_t {
        int *data              = nullptr;
        size_t cache_capacity  = 0;
        size_t n_data_elements = 0;
};

int get_user_data   (input_data_t *inputted_data);
void user_data_dtor (input_data_t *inputted_data);
int check_user_args (int argc, char **args);