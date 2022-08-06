#include "hash_functions.h"
#include <iostream>


int main(int argc, char *argv[])
{
	std::cout<<custom_hash::knuth_hash(16, 4);
    return 0;
}
