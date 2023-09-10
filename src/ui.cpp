#include <iostream>

#include "../include/ui.hpp"
#include "../include/utils.hpp"

int get_user_data (input_data_t *inputted_data)
{
        std::cin >> inputted_data->cache_capacity;
        std::cin >> inputted_data->n_data_elements;

        // size_t n_inputted_data_arguments = n_user_args - FIRST_DATA_ELEMENT_INDEX;
        // if (n_inputted_data_arguments > n_data_elements || n_inputted_data_arguments < n_data_elements) {
        // }

        inputted_data->data = (int*) malloc(inputted_data->n_data_elements * sizeof(int));
        if (!inputted_data->data)
                return NULL_ALLOC;

        size_t n_inputed_element = 0;

        while (n_inputed_element < inputted_data->n_data_elements) {
                std::cin >> inputted_data->data[n_inputed_element];
                n_inputed_element++;
        }
        if (n_inputed_element != inputted_data->n_data_elements) {
                std::cerr << "Number of entered data elements doesn't equal to n_data_elements!" << std::endl;
                return WRONG_N_ARGUMENTS;
        }

        return 0;
}