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
        struct two_q 
        {
                private:
                        size_t cache_capacity_        = 0;
                        size_t hot_cache_part_divider = 4;
                        size_t in_cache_part_divider  = 4;

                        std::list<std::pair<key_type, T>> hot_cache_ {};
                        std::list<std::pair<key_type, T>>  in_cache_ {};
                        std::list<          key_type>     out_cache_ {};

                        using data_list_iterator = typename std::list<std::pair<key_type, T>>::iterator;
                        using  out_list_iterator = typename std::list<key_type>::iterator;

                        std::unordered_map<key_type, data_list_iterator> hot_hashtable_ {};
                        std::unordered_map<key_type, data_list_iterator>  in_hashtable_ {};
                        std::unordered_map<key_type, out_list_iterator>  out_hashtable_ {};

                        size_t hot_cache_capacity_ = cache_capacity_ / hot_cache_part_divider;
                        size_t in_cache_capacity_  = cache_capacity_ / in_cache_part_divider;
                        size_t out_cache_capacity_ = cache_capacity_ - in_cache_capacity_ - hot_cache_capacity_;

                        bool hot_cache_is_full () const
                        {
                                return (hot_cache_.size() == hot_cache_capacity_);
                        }

                        bool inCache_is_full () const
                        {
                                return (in_cache_.size() == in_cache_capacity_);  
                        }

                        bool outCache_is_full () const
                        {
                                return (out_cache_.size() == out_cache_capacity_);
                        }

                        template <typename func>
                        void add_data2hot_cache (key_type key, func get_data) 
                        {
                                if (hot_cache_is_full()) {
                                        hot_hashtable_.erase(hot_cache_.back().first);
                                        hot_cache_.pop_back();
                                }
                                hot_cache_.emplace_front(key, get_data(key));
                                hot_hashtable_.emplace(key, hot_cache_.begin());
                        }

                        void add_data2out_cache (key_type key) 
                        {
                                if (outCache_is_full()) {
                                        out_hashtable_.erase(out_cache_.back());
                                        out_cache_.pop_back();
                                }
                                out_cache_.emplace_front(key);
                                out_hashtable_.emplace(key, out_cache_.begin());
                        }

                        template <typename func>
                        void add_data2in_cache (key_type key, func get_data) 
                        {
                                if (inCache_is_full()) {
                                        add_data2out_cache(in_cache_.back().first);
                                        in_hashtable_.erase(in_cache_.back().first);
                                        in_cache_.pop_back();
                                }
                                in_cache_.emplace_front(key, get_data(key));
                                in_hashtable_.emplace(key, in_cache_.begin());
                        }

                public:
                        two_q (size_t size) : cache_capacity_(size)
                        {                        
                                if (size < MIN_2Q_CACHE_CAPACITY) {
                                        std::cerr << "Minimum cache capacity is " << MIN_2Q_CACHE_CAPACITY << std::endl;
                                        exit((int) ERRORS::CACHE_CAPACITY_ERROR);
                                }
                        };
                        
                        template <typename func>
                        bool lookup_update (key_type key, func get_data) 
                        {
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

                        void dump (caches::two_q<int> const &cache)
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
        };
};