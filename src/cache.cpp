#include <cassert>
#include <string>
#include <iostream>

#include "utils.hpp"
#include "caches.hpp"
#include "cache.hpp"
#include "ui.hpp"

using namespace std;

namespace
{
        int get_data (int key)
        {
                return key;
        }
} // anonymous namespace


int hash_data (int data)
{
        return data;
}

template <typename T>
size_t check_data_in_cache (T &cache, std::vector<int> &data)
{
        size_t n_cache_hits = 0;

        for (auto it = data.cbegin(); it != data.cend(); it++) {
                bool is_in_cache = cache.lookup_update(hash_data(*it), get_data);
                //cache.dump();

                if (is_in_cache) {
                        n_cache_hits++;
                }
        }

        return n_cache_hits;
}

size_t run_cache (pair<size_t, vector<int>> input, const cache_type cache2run)
{
        auto cache_capacity = input.first;
        auto data           = input.second;

        if (cache2run == cache_type::RUN_2Q_CACHE) {
                caches::two_q<int> cache{cache_capacity};                
                
                return check_data_in_cache<caches::two_q<int>>(cache, data);
        }
        if (cache2run == cache_type::RUN_IDEAL_CACHE) {
                caches::ideal<int> ideal_cache{cache_capacity};
                ideal_cache.parse_data(data, hash_data);        
                
                return check_data_in_cache<caches::ideal<int>>(ideal_cache,
                                                               data
                                                               );
        }

        return (size_t) ERRORS::UNKNOWN_ARGUMENTS;
}