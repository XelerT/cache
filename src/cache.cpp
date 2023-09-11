#include <cassert>
#include <string>
#include <iostream>

#include "../include/utils.hpp"
#include "../include/caches.hpp"
#include "../include/cache.hpp"
#include "../include/ui.hpp"

static void dump_2q_cache    (caches::two_q<int> const &cache);
static void dump_ideal_cache (caches::ideal<int> const &cache);
static int get_data          (int key);

static int get_data (int key)
{
        return key;
}

int hash_data (int data)
{
        return data;
}

static void dump_2q_cache (caches::two_q<int> const &cache)
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

static void dump_ideal_cache (caches::ideal<int> const &cache)
{
        std::cout << "cache (" << cache.cache_capacity_ << ") ";
        for (auto it = cache.cache_.cbegin(); it != cache.cache_.cend(); it++) {
                std::cout << "[" << it->second << "] ";
        }
        std::cout << std::endl;
}

size_t check_data_in_2q_cache (caches::two_q<int> &cache, int *data, size_t n_data_elements)
{
        assert(data);

        size_t n_cache_hits = 0;

        for (size_t i = 0; i < n_data_elements; i++) {
                bool is_in_cache = cache.lookup_update(hash_data(data[i]), get_data);
                // dump_2q_cache(cache);

                if (is_in_cache) {
                        n_cache_hits++;
                }
        }

        return n_cache_hits;
}

size_t check_data_in_ideal_cache (caches::ideal<int> &cache, int *data, size_t n_data_elements)
{
        assert(data);

        size_t n_cache_hits = 0;

        for (size_t i = 0; i < n_data_elements; i++) {
                bool is_in_cache = cache.lookup_update(hash_data(data[i]), get_data);
                // dump_ideal_cache(cache);

                if (is_in_cache) {
                        n_cache_hits++;
                }
        }

        return n_cache_hits;
}