#include <iostream>
#include "hasher.h"
#include <stdio.h>
#include <random>
#include <algorithm> 
#include <ctime> 

std::string random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::srand(std::time(nullptr));
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

int main(int argc, const char *argv[])
{
    std::string str = random_string(10);
    Sha1* sha1Str = new Sha1;
    Hasher h{sha1Str};
    std::vector<uint16_t> result(SHA_DIGEST_LENGTH / 2);
    h.toHash(result, str);
    std::cout << "source string: " << str << std::endl;
    std::cout << "hash: ";
    for (auto e: result){
        std::cout << std::hex << e << " ";
    }
    std::cout << std::endl;
    return 0;
}

