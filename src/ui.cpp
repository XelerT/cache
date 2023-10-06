#include <iostream>
#include <cassert>
#include <cstring>

#include "ui.hpp"
#include "utils.hpp"

input_data_t::input_data_t () {
        std::cin >> cache_capacity_;
        std::cin >> n_data_elements_;

        size_t input = 0;

        while (data_.size() < n_data_elements_ && std::cin) {
                if (!(std::cin >> input))
                        break;
                data_.push_back(input);
        }

        if (std::cin.fail() && !std::cin.eof())
                throw std::runtime_error("You need to enter digits.");  
};

int check_user_args (int argc, char **args)
{
        assert(args);

        if (argc == 2 && !std::strcmp(args[1], "--tq"))
                return RUN_2Q_CACHE;
        
        if (argc == 2 && !std::strcmp(args[1], "-i"))
                return RUN_IDEAL_CACHE;

        std::cerr << "Unknown program options. Use: \n\t--tq - run 2Q cache\n\t -i - run ideal cache.\n";
        return (int) ERRORS::UNKNOWN_ARGUMENTS;        
}