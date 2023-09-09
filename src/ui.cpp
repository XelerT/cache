#include <iostream>

#include "../include/ui.hpp"
#include "../include/utils.hpp"

int get_user_data (input_data_t *inputed_data)
{
        std::cin >> inputed_data->cache_capacity;
        std::cin >> inputed_data->n_data_elements;

        // size_t n_inputed_data_arguments = n_user_args - FIRST_DATA_ELEMENT_INDEX;
        // if (n_inputed_data_arguments > n_data_elements || n_inputed_data_arguments < n_data_elements) {
        // }

        inputed_data->data = (int*) malloc(inputed_data->n_data_elements * sizeof(int));
        if (!inputed_data->data)
                return NULL_ALLOC;

        size_t n_inputed_element = 0;

        while (n_inputed_element < inputed_data->n_data_elements) {
                std::cin >> inputed_data->data[n_inputed_element];
                n_inputed_element++;
        }
        if (n_inputed_element != inputed_data->n_data_elements) {
                std::cerr << "Number of entered data elements doesn't equal to n_data_elements!" << std::endl;
                return WRONG_N_ARGUMENTS;
        }

        return 0;
}