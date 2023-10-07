#pragma once

#include <list>
#include <unordered_map>
#include <vector>
#include <cstddef>
#include <iostream>

#include "utils.hpp"

namespace caches
{
        template <typename T, typename key_type = int>
        struct ideal
        {
                private:
                        size_t cache_capacity_ = 0;

                        std::list<std::pair<key_type, T>> cache_            {};
                        std::list<size_t>                 data_occurrences_ {}; 

                        using                data_list = typename std::list<size_t>;
                        using            list_iterator = typename std::list<std::pair<key_type, T>>::iterator;
                        using data_occurrence_iterator = typename std::unordered_map<key_type, data_list>::iterator;

                        std::unordered_map<key_type, list_iterator>             hashtable_ {};
                        std::unordered_map<key_type, data_list> data_occurrence_hashtable_ {};

                        bool cache_is_full () const
                        {
                                return cache_.size() == cache_capacity_;
                        }

                        void check_delete_null_occurrence (key_type key)
                        {
                                if (data_occurrence_hashtable_[key].begin() == data_occurrence_hashtable_[key].end())
                                        data_occurrence_hashtable_.erase(key);
                        }

                        bool data_will_occur_again (const key_type key)
                        {
                                return data_occurrence_hashtable_[key].size() != 1;
                        }

                        void delete_farthest_elem ()
                        {
                                size_t greatest_index = 0;
                
                                list_iterator     cached_elem_iterator   {};
                                data_occurrence_iterator elem_occurrence {};

                                for (auto it = cache_.begin(); it != cache_.end(); it++) {
                                        elem_occurrence = data_occurrence_hashtable_.find(it->first);
                                        if (elem_occurrence == data_occurrence_hashtable_.end()) {
                                                hashtable_.erase(it->first);
                                                cache_.erase(it);
                                                return;
                                        }
                                        auto index = *elem_occurrence->second.begin();
                                        if (index > greatest_index) {
                                                greatest_index = index;
                                                cached_elem_iterator = it;
                                        }
                                }

                                if (greatest_index) {
                                        hashtable_.erase(cached_elem_iterator->first);
                                        cache_.erase(cached_elem_iterator);
                                } else {
                                        hashtable_.erase(cache_.back().first);
                                        cache_.pop_back();
                                }
                        }

                public:
                        ideal (size_t size) : cache_capacity_(size) {
                                if (size < MIN_IDEAL_CACHE_CAPACITY) {
                                        std::cerr << "Minimum cache capacity is " << MIN_IDEAL_CACHE_CAPACITY << std::endl;
                                        exit((int) ERRORS::CACHE_CAPACITY_ERROR);
                                }
                        };
                        
                        template <typename func>
                        void parse_data (std::vector<T> &data, func hash_data)
                        {
                                data_occurrence_iterator occurrence_iter {};  
                                
                                for (auto it = data.cbegin(); it != data.cend(); it++) {
                                        occurrence_iter = data_occurrence_hashtable_.find(hash_data(*it));
                                        data_occurrence_hashtable_[hash_data(*it)].emplace_back(it - data.cbegin());
                                }
                        }

                        template <typename func>
                        bool lookup_update (key_type key, func get_data)
                        {
                                auto hit = hashtable_.find(key);
                                if (hit == hashtable_.end()) {
                                        if (!data_will_occur_again(key)) {
                                                return false;
                                        }
                                        if (cache_is_full()) {
                                                delete_farthest_elem();
                                        }
                                        cache_.emplace_front(key, get_data(key));
                                        hashtable_.emplace(key, cache_.begin());

                                        data_occurrence_hashtable_[key].pop_front();
                                        check_delete_null_occurrence(key);
                                        
                                        return false;
                                }

                                auto elem_iterator = hit->second;
                                if (elem_iterator != cache_.begin())
                                        cache_.splice(cache_.begin(), cache_, elem_iterator, std::next(elem_iterator));

                                data_occurrence_hashtable_[key].pop_front();
                                check_delete_null_occurrence(key);
                                
                                return true;
                        }

                        void dump (caches::ideal<int> const &cache) const
                        {
                                std::cout << "cache (" << cache.cache_capacity_ << ") ";
                                for (auto it = cache.cache_.cbegin(); it != cache.cache_.cend(); it++) {
                                        std::cout << "[" << it->second << "] ";
                                }
                                std::cout << std::endl;
                        }
                };
};