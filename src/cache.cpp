#include <cassert>
#include <string>
#include <iostream>

#include "../include/utils.hpp"
#include "../include/cache.hpp"
#include "../include/ui.hpp"


int get_data (int key)
{
        return key;
}

int hash_data (int data)
{
        return data;
}

void dump_cache (cache::Q2<int> const &cache)
{
        std::cout << "hot (" << cache.hot_cache_capacity_ << ") ";
        for (auto it = cache.hot_cache_.cbegin(); it != cache.hot_cache_.cend(); it++) {
                std::cout << "[" << it->second << "] ";
        }
        std::cout << std::endl;

        std::cout << "in  (" << cache.in_cache_capacity_ << ") ";
        for (auto it = cache.in_cache_.cbegin(); it != cache.in_cache_.cend(); it++) {
                std::cout << "[" << it->second << "] ";
        }
        std::cout << std::endl;

        std::cout << "out (" << cache.out_cache_capacity_ << ") ";
        for (auto it = cache.out_cache_.cbegin(); it != cache.out_cache_.cend(); it++) {
                std::cout << "[" << *it << "] ";
        }
        std::cout << std::endl;
}

int* get_user_data (size_t n_user_args, char *args[])
{
        assert(args);

        size_t cache_capacity  = 0;
        size_t n_data_elements = 0;
        sscanf(args[CACHE_CAPACITY_ARG_INDEX], "%ld", &cache_capacity);
        sscanf(args[N_DATA_ELEMENT_INDEX], "%ld", &n_data_elements);

        size_t n_inputed_data_arguments = n_user_args - FIRST_DATA_ELEMENT_INDEX;
        if (n_inputed_data_arguments > n_data_elements || n_inputed_data_arguments < n_data_elements) {
                std::cerr << "Number of entered data elements doesn't equal to n_data_elements!" << std::endl;
                exit(WRONG_N_ARGUMENTS);
        }

        int *cache_data = (int*) malloc(n_data_elements * sizeof(int));
        if (!cache_data)
                return nullptr;

        size_t ui = FIRST_DATA_ELEMENT_INDEX;
        for (size_t i = 0; i < n_data_elements; i++, ui++) {
                sscanf(args[ui], "%d", cache_data + i);
        }

        return cache_data;
}

int check_data_in_cache (cache::Q2<int> &cache, int *data, size_t n_data_elements)
{
        assert(data);

        size_t n_cache_hits = 0;

        for (size_t i = 0; i < n_data_elements; i++) {
                std::cout << "data: " << data[i] << "\n";
                dump_cache(cache);
                bool is_in_cache = cache.cache_data(hash_data(data[i]), get_data);

                if (is_in_cache) {
                        n_cache_hits++;
                }
        }

        return n_cache_hits;
}