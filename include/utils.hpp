#pragma once

enum ERRORS {
        ERROR                = 0xBADDED,
        WRONG_N_ARGUMENTS    = 0xBADA46,
        NULL_ALLOC           = 0xBADCA1,
        CACHE_CAPACITY_ERROR = 0xBADCA4,
        UNKNOWN_ARGUMENTS    = 0xBADA44
};

enum CACHE_CONSTS {
        MIN_2Q_CACHE_CAPACITY    = 4,
        MIN_IDEAL_CACHE_CAPACITY = 1
};
