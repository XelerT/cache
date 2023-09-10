#include <string>
#include <iostream>
#include <string.h>

#include "include/cache.hpp" 
#include "include/ui.hpp"
#include "include/utils.hpp"

int main (int argc, char *argv[])
{
        input_data_t inputted_data = {};
        int err = get_user_data(&inputted_data);
        if (err)
                return err;

        int n_cache_hits = 0;

        if ((argc == 2 && !strcmp(argv[1], "--tq")) || (argc == 3 && !strcmp(argv[2], "--tq"))) {
                caches::two_q<int> cache{inputted_data.cache_capacity};                
                n_cache_hits = check_data_in_2q_cache(cache, inputted_data.data, inputted_data.n_data_elements);
        } else if ((argc == 2 && !strcmp(argv[1], "-i")) || (argc == 3 && !strcmp(argv[2], "-i"))) {
                caches::ideal<int> ideal_cache{inputted_data.cache_capacity};
                ideal_cache.parse_data(inputted_data.data, inputted_data.n_data_elements, hash_data);        
                n_cache_hits = check_data_in_ideal_cache(ideal_cache, inputted_data.data, inputted_data.n_data_elements);
        } else {
                std::cerr << "Program options are: --tq, -i.\n";
                return UNKNOWN_ARGUMENTS;
        }
        std::cout << n_cache_hits << std::endl;

        return 0;
}