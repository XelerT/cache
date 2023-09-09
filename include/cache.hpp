#pragma once

#include <list>
#include <unordered_map>
#include <vector>
#include <cstddef>
#include <iostream>

#include "../include/utils.hpp"

enum CACHE_CONSTS {
        MIN_CACHE_CAPACITY = 4
};

namespace caches
{        
        template <typename T, typename KeyType = int> struct two_q {
                size_t cache_capacity_        = 0;
                size_t hot_cache_part_divider = 4;
                size_t in_cache_part_divider  = 4;

                std::list<std::pair<KeyType, T>> hot_cache_;
                std::list<std::pair<KeyType, T>>  in_cache_;
                std::list<          KeyType>     out_cache_;

                using data_list_iterator = typename std::list<std::pair<KeyType, T>>::iterator;
                using out_list_iterator  = typename std::list<KeyType>::iterator;

                std::unordered_map<KeyType, data_list_iterator> hot_hashtable_;
                std::unordered_map<KeyType, data_list_iterator>  in_hashtable_;
                std::unordered_map<KeyType, out_list_iterator>  out_hashtable_;

                two_q(size_t size) : cache_capacity_(size), hot_cache_{} {                        
                        if (size < MIN_CACHE_CAPACITY) {
                                std::cerr << "Minimum cache capacity is " << MIN_CACHE_CAPACITY << std::endl;
                                exit(CACHE_CAPACITY_ERROR);
                        }
                };

                ~two_q() {};

                size_t hot_cache_capacity_ = cache_capacity_ / hot_cache_part_divider;
                size_t in_cache_capacity_  = cache_capacity_ / in_cache_part_divider;
                size_t out_cache_capacity_ = cache_capacity_ - in_cache_capacity_ - hot_cache_capacity_;

                bool hot_cache_is_full () {
                        return (hot_cache_.size() == hot_cache_capacity_);
                }

                bool inCache_is_full () {
                        return (in_cache_.size() == in_cache_capacity_);  
                }

                bool outCache_is_full () {
                        return (out_cache_.size() == out_cache_capacity_);
                }

                template <typename func>
                void add_data2hot_cache (int key, func get_data) {
                        if (hot_cache_is_full()) {
                                hot_hashtable_.erase(hot_cache_.back().first);
                                hot_cache_.pop_back();
                        }
                        hot_cache_.emplace_front(key, get_data(key));
                        hot_hashtable_.emplace(key, hot_cache_.begin());
                }

                void add_data2out_cache (int key) {
                        if (outCache_is_full()) {
                                out_hashtable_.erase(out_cache_.back());
                                out_cache_.pop_back();
                        }
                        out_cache_.emplace_front(key);
                        out_hashtable_.emplace(key, out_cache_.begin());
                }

                template <typename func>
                void add_data2in_cache (int key, func get_data) {
                        if (inCache_is_full()) {
                                add_data2out_cache(in_cache_.back().first);
                                in_hashtable_.erase(in_cache_.back().first);
                                in_cache_.pop_back();
                        }
                        in_cache_.emplace_front(key, get_data(key));
                        in_hashtable_.emplace(key, in_cache_.begin());
                }

                template <typename func>
                bool lookup_update (int key, func get_data) {
                        auto hit = hot_hashtable_.find(key);
                        if (hit != hot_hashtable_.end()) {
                                auto hot_cache_head = hit->second;
                                if (hot_cache_head != hot_cache_.begin())
                                        hot_cache_.splice(hot_cache_.end(), hot_cache_, hot_cache_head, std::next(hot_cache_head));
                        
                                return true;
                        }
                        auto out_hit = out_hashtable_.find(key);
                        if (out_hit != out_hashtable_.end()) {
                                add_data2hot_cache(key, get_data);
                                out_cache_.erase(out_hit->second);
                                out_hashtable_.erase(out_hit);

                                return true;
                        }
                        hit = in_hashtable_.find(key);
                        if (hit == in_hashtable_.end()) {
                                add_data2in_cache(key, get_data);
                                return false;

                        }
                        return true;
                }
        };
};

int  check_data_in_cache (caches::two_q<int> &cache, int *data, size_t n_data_elements);
int  hash_data           (int data);