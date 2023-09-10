#include <string>
#include <iostream>

#include "include/cache.hpp" 
#include "include/ui.hpp"
#include "include/utils.hpp"

int main ()
{
        input_data_t inputted_data = {};
        int err = get_user_data(&inputted_data);
        if (err)
                return err;

        caches::two_q<int> cache{inputted_data.cache_capacity};

        int n_cache_hits = check_data_in_2q_cache(cache, inputted_data.data, inputted_data.n_data_elements);
        std::cout << n_cache_hits << std::endl;

        caches::ideal<int> ideal_cache{inputted_data.cache_capacity};
        ideal_cache.parse_data(inputted_data.data, inputted_data.n_data_elements, hash_data);
        int ideal_n_cache_hits = check_data_in_ideal_cache(ideal_cache, inputted_data.data, inputted_data.n_data_elements);
        std::cout << ideal_n_cache_hits << std::endl;

        return 0;
}