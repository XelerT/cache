#include <cassert>
#include <string>
#include <iostream>

#include "utils.hpp"
#include "caches.hpp"
#include "cache.hpp"
#include "ui.hpp"

// static void dump_2q_cache    (caches::two_q<int> const &cache);
// static void dump_ideal_cache (caches::ideal<int> const &cache);
// static int get_data          (int key);

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

size_t run_cache (input_data_t &inputted_data, int cache2run)
{
        if (cache2run == RUN_2Q_CACHE) {
                caches::two_q<int> cache{inputted_data.cache_capacity_};                
                
                return check_data_in_cache<caches::two_q<int>>(cache, inputted_data.data_);
        } else if (cache2run == RUN_IDEAL_CACHE) {
                caches::ideal<int> ideal_cache{inputted_data.cache_capacity_};
                ideal_cache.parse_data(inputted_data.data_, hash_data);        
                
                return check_data_in_cache<caches::ideal<int>>(ideal_cache,
                                                               inputted_data.data_
                                                               );
        }

        return (size_t) ERRORS::UNKNOWN_ARGUMENTS;
}