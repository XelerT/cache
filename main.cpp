#include <string>
#include <iostream>

#include "caches.hpp" 
#include "cache.hpp" 
#include "ui.hpp"
#include "utils.hpp"

int main (int argc, char *argv[])
{
        int cache2run = check_user_args(argc, argv);
        if (cache2run == (int) ERRORS::UNKNOWN_ARGUMENTS)
                return (int) ERRORS::UNKNOWN_ARGUMENTS;

        size_t n_cache_hits = run_cache(get_input_data(), cache2run);
        std::cout << n_cache_hits << std::endl;

        return 0;
}