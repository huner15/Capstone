/*
 * @file TailNumber.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 2-9-16
 * @brief Contains TailNumber function implementations.
 */

#include <random>
#include <stdexcept>

#include "TailNumber.h"

/* Disclaimer: The following function is a modified version of the original
 * version at http://stackoverflow.com/questions/440133/how-do-i-create-a-
 * random-alpha-numeric-string-in-c
 */
std::string random_string(size_t length) {
    if (length >= 0) {
        std::string str;
        str.reserve(length);

        /* String containing all alphanumeric characters. */
        static const std::string alphanumeric =
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
                "0123456789";

        /* A Mersenne Twister pseudo-random generator of 32-bit numbers with a
         * state size of 19937 bits. */
        static std::mt19937 rg{std::random_device{}()};

        /* A integer distribution equal to the number of alphanumeric
         * characters. */
        static std::uniform_int_distribution<> pick(
                0, (int) alphanumeric.size() - 1);

        /* Add length number of random characters from the alphabet to the
         * string by picking a character from a range using the specified
         * generator. */
        while (length--) {
            str += alphanumeric[pick(rg)];
        }

        return str;
    }
    else {
        throw std::out_of_range ("String length less than zero.");
    }
}

TailNumber::TailNumber() {
    _tail_number = random_string(_length);
}

TailNumber::TailNumber(std::string tail_number) {
    if (tail_number.length() == _length) {
        _tail_number = tail_number;
    }
    else {
        throw std::out_of_range ("Tail Number must be six characters.");
    }
}

TailNumber::~TailNumber() {
}

std::string TailNumber::Get() {
    return _tail_number;
}

bool TailNumber::operator==(TailNumber tail_number) {
    return tail_number.Get().compare(_tail_number) == 0;
}
