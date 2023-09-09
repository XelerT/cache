#include <string>
#include <iostream>

#include "include/cache.hpp" 
#include "include/ui.hpp"
#include "include/utils.hpp"

int main ()
{
        input_data_t inputed_data = {};
        int err = get_user_data(&inputed_data);
        if (err)
                return err;

        caches::two_q<int> cache{inputed_data.cache_capacity};

        int n_cache_hits = check_data_in_cache(cache, inputed_data.data, inputed_data.n_data_elements);
        std::cout << n_cache_hits << std::endl;

        return 0;
}