#include <string>
#include <iostream>

#include "caches.hpp" 
#include "cache.hpp" 
#include "ui.hpp"
#include "utils.hpp"

int main (int argc, char *argv[])
{
        cache_type cache2run = check_user_args(argc, argv);
        if (cache2run == cache_type::UNKNOWN_TYPE)
                return -1;

        size_t n_cache_hits = run_cache(get_input_data(), cache2run);
        std::cout << n_cache_hits << std::endl;

        return 0;
}