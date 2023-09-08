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

#define $ printf("%d line; In func = %s\n", __LINE__, __PRETTY_FUNCTION__);

namespace cache
{        
        template <typename T, typename KeyType = int> struct Q2 {
                size_t cache_capacity_        = 0;
                size_t hot_cache_part_divider = 4;
                size_t in_cache_part_divider  = 4;

                std::list<std::pair<KeyType, T>> hot_cache_;
                std::list<std::pair<KeyType, T>>  in_cache_;
                std::list<          KeyType>     out_cache_;

                using list_iterator = typename std::list<std::pair<KeyType, T>>::iterator;
                using out_list_iterator = typename std::list<KeyType>::iterator;

                std::unordered_map<KeyType, list_iterator>     hashtable_;
                std::unordered_map<KeyType, list_iterator>  in_hashtable_;
                std::unordered_map<KeyType, out_list_iterator> out_hashtable_;

                Q2(size_t size) : cache_capacity_(size) {                        
                        if (size < MIN_CACHE_CAPACITY) {
                                std::cerr << "Minimum cache capacity is " << MIN_CACHE_CAPACITY << std::endl;
                                exit(CACHE_CAPACITY_ERROR);
                        }
                };

                ~Q2() {};

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
                        std::cout << "Added " << key << " in hot" << std::endl;
                        if (hot_cache_is_full()) {
                                hashtable_.erase(hot_cache_.back().first);
                                hot_cache_.pop_back();
                        }
                        hot_cache_.emplace_front(key, get_data(key));
                        hashtable_.emplace(key, hot_cache_.begin());
                }

                void add_data2out_cache (int key) {
                        if (outCache_is_full()) {
                                out_hashtable_.erase(out_cache_.back());
                                out_cache_.pop_back();
                        }
                        std::cout << "Added " << key << " in out" << std::endl;
                        out_cache_.emplace_front(key);
                        out_hashtable_.emplace(key, out_cache_.begin());
                }

                template <typename func>
                void add_data_in_inCache (int key, func get_data) {
                        if (inCache_is_full()) {
                                add_data2out_cache(in_cache_.back().first);
                                in_hashtable_.erase(in_cache_.back().first);
                                in_cache_.pop_back();
                        }
                        std::cout << "Added " << key << " in in" << std::endl;

                        in_cache_.emplace_front(key, get_data(key));
                        in_hashtable_.emplace(key, in_cache_.begin());
                }

                template <typename func>
                bool cache_data (int key, func get_data) {
                        auto hit = hashtable_.find(key);
                        if (hit != hashtable_.end()) {
                                auto hot_cache_head = hit->second;
                                if (hot_cache_head != hot_cache_.begin())
                                        hot_cache_.splice(hot_cache_.end(), hot_cache_, hot_cache_head, std::next(hot_cache_head));
                                std::cout << "data elem hot cache true:" << key << std::endl;
                        
                                return true;
                        }
                        auto out_hit = out_hashtable_.find(key);
                        if (out_hit != out_hashtable_.end()) {
                                add_data2hot_cache(key, get_data);
                                printf("deleted %d from out\n", key);
                                out_cache_.erase(out_hit->second);
                                out_hashtable_.erase(out_hit);
                                return true;
                        }
                        hit = in_hashtable_.find(key);
                        if (hit == in_hashtable_.end()) {
                                add_data_in_inCache(key, get_data);
                                return false;
                        }
                        return true;
                }
        };
};

int* get_user_data       (size_t n_user_args, char *args[]);
int  check_data_in_cache (cache::Q2<int> &cache, int *data, size_t n_data_elements);
int  hash_data           (int data);