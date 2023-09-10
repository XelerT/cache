#pragma once

#include <list>
#include <unordered_map>
#include <vector>
#include <cstddef>
#include <iostream>

#include "utils.hpp"

namespace caches
{
        template <typename T, typename KeyType = int>
        struct ideal
        {
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