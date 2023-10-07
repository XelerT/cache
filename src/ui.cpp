#include <iostream>
#include <cassert>
#include <cstring>

#include "ui.hpp"
#include "utils.hpp"

using namespace std;

cache_type check_user_args (int argc, char **args)
{
        assert(args);

        if (argc == 2 && !std::strcmp(args[1], "--tq"))
                return cache_type::RUN_2Q_CACHE;
        
        if (argc == 2 && !std::strcmp(args[1], "-i"))
                return cache_type::RUN_IDEAL_CACHE;

        std::cerr << "Unknown program options. Use: \n\t--tq - run 2Q cache\n\t -i - run ideal cache.\n";
        return cache_type::UNKNOWN_TYPE;        
}

pair<size_t, vector<int>> get_input_data ()
{
        size_t cache_capacity;
        size_t n_data_elements;

        std::cin >> cache_capacity;
        std::cin >> n_data_elements;

        std::vector<int> data;

        size_t input;

        while (data.size() < n_data_elements && std::cin) {
                if (!(std::cin >> input))
                        break;
                data.push_back(input);
        }
        
        if (std::cin.fail() && !std::cin.eof())
                throw std::runtime_error("You need to enter digits.");

        return {cache_capacity, data};
}