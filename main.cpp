#include <string>
#include <iostream>

#include "include/cache.hpp" 
#include "include/ui.hpp"
#include "include/utils.hpp"

int main (int argc, char *argv[])
{
        int *data = get_user_data((size_t) argc, argv);
        if (!data)
                return ERROR;

        cache::Q2<int> cache{std::stoi(argv[CACHE_CAPACITY_ARG_INDEX])};
        std::cout << "cache cap: " << argv[CACHE_CAPACITY_ARG_INDEX] << std::endl;


        int n_cache_hits = check_data_in_cache(cache, data, std::stoi(argv[N_DATA_ELEMENT_INDEX]));
        std::cout << "number of cache hits: " << n_cache_hits << std::endl;

        return 0;
}