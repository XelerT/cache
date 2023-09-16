#include <iostream>
#include <assert.h>
#include <string.h>

#include "../include/ui.hpp"
#include "../include/utils.hpp"

int get_user_data (input_data_t *inputted_data)
{
        assert(inputted_data);

        std::cin >> inputted_data->cache_capacity;
        std::cin >> inputted_data->n_data_elements;

        inputted_data->data = (int*) malloc(inputted_data->n_data_elements * sizeof(int));
        if (!inputted_data->data)
                return NULL_ALLOC;

        size_t n_inputted_element = 0;

        while (n_inputted_element < inputted_data->n_data_elements) {
                std::cin >> inputted_data->data[n_inputted_element];
                n_inputted_element++;
        }
        if (n_inputted_element != inputted_data->n_data_elements) {
                std::cerr << "Number of entered data elements doesn't equal to n_data_elements!" << std::endl;
                return WRONG_N_ARGUMENTS;
        }

        return 0;
}

void user_data_dtor (input_data_t *inputted_data)
{
        assert(inputted_data);

        if (inputted_data->data) {
                free(inputted_data->data);
                inputted_data->data = nullptr;
        }
}

int check_user_args (int argc, char **args)
{
        assert(args);

        if (argc == 2 && !strcmp(args[1], "--tq"))
                return RUN_2Q_CACHE;
        else if (argc == 2 && !strcmp(args[1], "-i"))
                return RUN_IDEAL_CACHE;

        std::cerr << "Unknown program options. Use: \n\t--tq - run 2Q cache\n\t -i - run ideal cache.\n";
        return UNKNOWN_ARGUMENTS;        
}