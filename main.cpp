#include <string>
#include <iostream>

#include "include/caches.hpp" 
#include "include/cache.hpp" 
#include "include/ui.hpp"
#include "include/utils.hpp"

int main (int argc, char *argv[])
{
        int cache2run = check_user_args(argc, argv);
        if (cache2run == UNKNOWN_ARGUMENTS)
                return UNKNOWN_ARGUMENTS;

        input_data_t inputted_data = {};
        int err = get_user_data(&inputted_data);
        if (err)
                return err;

        size_t n_cache_hits = run_cache(&inputted_data, cache2run);
        std::cout << n_cache_hits << std::endl;

        user_data_dtor(&inputted_data);

        return 0;
}