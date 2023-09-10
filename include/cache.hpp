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
        template <typename T, typename KeyType = int> 
        struct two_q {
                size_t cache_capacity_        = 0;
                size_t hot_cache_part_divider = 4;
                size_t in_cache_part_divider  = 4;

                std::list<std::pair<KeyType, T>> hot_cache_ {};
                std::list<std::pair<KeyType, T>>  in_cache_ {};
                std::list<          KeyType>     out_cache_ {};

                using data_list_iterator = typename std::list<std::pair<KeyType, T>>::iterator;
                using  out_list_iterator = typename std::list<KeyType>::iterator;

                std::unordered_map<KeyType, data_list_iterator> hot_hashtable_;
                std::unordered_map<KeyType, data_list_iterator>  in_hashtable_;
                std::unordered_map<KeyType, out_list_iterator>  out_hashtable_;

                two_q (size_t size) : cache_capacity_(size) {                        
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
                                auto elem_iterator = hit->second;
                                if (elem_iterator != hot_cache_.begin())
                                        hot_cache_.splice(hot_cache_.begin(), hot_cache_, elem_iterator, std::next(elem_iterator));
                        
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
        
        template <typename T, typename KeyType = int>
        struct ideal {
                size_t cache_capacity_ = 0;

                std::list<std::pair<KeyType, T>> cache_ {};
                std::list<size_t> data_occurrences_ {}; 

                using            list_iterator = typename std::list<std::pair<KeyType, T>>::iterator;
                using       data_list_iterator = typename std::list<size_t>::iterator;
                using data_occurrence_iterator = typename std::unordered_map<KeyType, data_list_iterator>::iterator;

                std::unordered_map<KeyType, list_iterator>                      hashtable_ {};
                std::unordered_map<KeyType, data_list_iterator> data_occurrence_hashtable_ {};

                ideal (size_t size) : cache_capacity_(size) {};
                ~ideal() {};

                bool cache_is_full () {
                        return cache_.size() == cache_capacity_;
                }

                template <typename func>
                void parse_data (T *data, size_t n_data_elements, func hash_data) {
                        for (size_t i = 0; i < n_data_elements; i++) {
                                data_occurrences_.emplace_front(i);
                                data_occurrence_hashtable_.emplace(hash_data(data[i]), data_occurrences_.begin());
                        }
                }

                template <typename func>
                bool lookup_update (KeyType key, func get_data) {
                        auto hit = hashtable_.find(key);
                        if (hit == hashtable_.end()) {
                                if (cache_is_full()) {
                                        delete_farthest_elem();
                                }
                                cache_.emplace_front(key, get_data(key));
                                hashtable_.emplace(key, cache_.begin());

                                data_occurrences_.erase(data_occurrence_hashtable_.find(key)->second);
                                data_occurrence_hashtable_.erase(key);
                                
                                return false;
                        }

                        auto elem_iterator = hit->second;
                        if (elem_iterator != cache_.begin())
                                cache_.splice(cache_.begin(), cache_, elem_iterator, std::next(elem_iterator));
                        
                        return true;
                }

                void delete_farthest_elem () {
                        size_t greatest_index = 0;

                        data_occurrence_iterator elem_occurrences {};
                        list_iterator cached_elem_iterator {};

                        for (auto it = cache_.begin(); it != cache_.end(); it++) {
                                elem_occurrences = data_occurrence_hashtable_.find(it->first);
                                if (elem_occurrences == data_occurrence_hashtable_.end())
                                        continue;
                                if (*(elem_occurrences->second) > greatest_index) {
                                        greatest_index = *(elem_occurrences->second);
                                        cached_elem_iterator = it;
                                }
                        }

                        if (greatest_index) {
                                cache_.erase(cached_elem_iterator);
                                data_occurrences_.erase(elem_occurrences->second);
                                data_occurrence_hashtable_.erase(elem_occurrences);
                        } else
                                cache_.pop_back();
                }
        };
};

int  check_data_in_2q_cache   (caches::two_q<int> &cache, int *data, size_t n_data_elements);
int check_data_in_ideal_cache (caches::ideal<int> &cache, int *data, size_t n_data_elements);
int  hash_data                (int data);