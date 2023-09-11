# cache

My implementation of 2Q and Ideal cache. 

## Install,Build & Run

### Install

        $ git clone https://github.com/XelerT/cache.git
        $ cd cache

### Build
        $ cmake CMakeLists.txt
        $ make

### Run

We have two modes to work with caches:

1) 2Q cache
2) Ideal cache

To run program you need to pass on of the options below:

1) -i   - to run ideal cache
2) --tq - to run 2Q cache

        $ ./caches -i

Then you need to enter input data. First number is size of cache, second is number of data elements, which will be inputted next and next list of data.

        8 16 1 2 2 1 5 4 2 1 10 6 7 8 10 11 12 5

Output of the program is the amount of cache hits.

## Tests
To test caches we have python script, which is located at ```tests/``` directory. It has three working modes:

1) -c   - to test and compare hit rate ideal and 2Q caches
2) --tq - to test 2Q cache
3) -i   - to test ideal cache

        $ python tests/test_caches.py --tq
