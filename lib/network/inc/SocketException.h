/*
 * California Polytechnic State University, San Luis Obispo
 * Computer Engineering - CPE 402, 405, 406
 * Author: Frank Poole
 * Professor: David Janzen
 * Date: 1-16-2016
 * Disclaimer: The original version of the following code was taken from
 * tldp.org/LDP/LG/issue74/misc/tougher
 */

#ifndef SocketException_H
#define SocketException_H

#include <string>

/**
 * A SocketException is thrown whenever issues occur with socket connections.
 */
class SocketException {
public:
    SocketException(std::string s) : m_s(s) { };

    ~SocketException() { };

    std::string description() { return m_s; }

private:
    std::string m_s;
};

#endif
