/*
 * TailNumber.cpp
 * Specific Atomics
 * Frank Poole
 * 2-4-16
 * TODO: Description
 */

#include <algorithm>

#include "TailNumber.h"

/*
char genRandom() {
    static const char alphabet[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    return alphabet[rand() % (sizeof(alphabet) - 1)];
}
*/

/*
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
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}
*/

std::string random_string(size_t length) {
    static const std::string alphanums =
            "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static std::mt19937 rg{std::random_device{}()};
    static std::uniform_int_distribution<> pick(0, alphanums.size() - 1);

    std::string s;

    s.reserve(length);

    while(length--)
        s += alphanums[pick(rg)];

    return s;
}

TailNumber::TailNumber() {
    /*
    for (int i = 0; i < _length; ++i) {
        _tail_number += genRandom();
    }
    */
    _tail_number = random_string(_length);
}

TailNumber::TailNumber(std::string tail_number) {
    _tail_number = tail_number;
}

TailNumber::~TailNumber() {

}

std::string TailNumber::GetTailNumber() {
    return _tail_number;
}
