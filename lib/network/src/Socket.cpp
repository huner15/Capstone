/*
 * California Polytechnic State University, San Luis Obispo
 * Computer Engineering - CPE 402, 405, 406
 * Author: Frank Poole
 * Professor: David Janzen
 * Date: 1-16-2016
 * Disclaimer: The original version of the following code was taken from
 * tldp.org/LDP/LG/issue74/misc/tougher
 */

#include "Socket.h"

Socket::Socket() : m_sock(-1) {
    ::memset(&m_addr, 0, sizeof(m_addr));
}

Socket::~Socket() {
    if (is_valid()) {
        ::close(m_sock);
    }
}

bool Socket::create() {
    int opt = 1;
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    return is_valid() && ::setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR,
                                      (const char *) &opt, sizeof(opt)) != -1;
}

bool Socket::bind(const in_port_t port) {
    if (is_valid()) {
        m_addr.sin_family = AF_INET;
        m_addr.sin_addr.s_addr = INADDR_ANY;
        m_addr.sin_port = htons(port);
        return ::bind(m_sock, (struct sockaddr *) &m_addr,
                      sizeof(m_addr)) != -1;
    }
    else {
        return false;
    }
}

bool Socket::listen() const {
    return is_valid() && ::listen(m_sock, MAX_CONNECTIONS) != -1;
}

bool Socket::accept(Socket &new_socket) const {
    socklen_t addr_len = sizeof(m_addr);
    new_socket.m_sock = ::accept(m_sock, (sockaddr *) &m_addr, &addr_len);
    return new_socket.is_valid();
}

bool Socket::send(const std::string &msg) const {
    return ::send(m_sock, msg.c_str(), msg.size(), 0) != -1;
}

size_t Socket::recv(std::string &bfr, int flags) const {
    char buf[MAX_RECV + 1];
    memset(buf, 0, MAX_RECV + 1);
    ssize_t status = ::recv(m_sock, buf, MAX_RECV, flags);

    if (status != -1) {
        std::cout << "Status == -1, errno == " << errno
        << "In Socket::recv" << std::endl;
        return 0;
    }
    else {
        bfr = buf;
        return (size_t) status;
    }
}

size_t Socket::recv(void *bfr, size_t len, int flags) const {
    ssize_t status = ::recv(m_sock, bfr, len, flags);

    if (status == -1) {
        std::cout << "Status == -1, errno == " << errno
        << "In Socket::recv" << std::endl;
        return 0;
    }
    else {
        return (size_t) status;
    }
}

bool Socket::connect(const std::string host, const in_port_t port) {
    if (is_valid()) {
        m_addr.sin_family = AF_INET;
        m_addr.sin_port = htons(port);
        inet_pton(AF_INET, host.c_str(), &m_addr.sin_addr);
        return errno != EAFNOSUPPORT &&
               ::connect(m_sock, (sockaddr *) &m_addr, sizeof(m_addr)) != -1;
    }
    else {
        return false;
    }
}

bool Socket::set_non_blocking(const bool b) {
    int opts = fcntl(m_sock, F_GETFL);

    if (opts != -1) {
        opts = b ? opts | O_NONBLOCK : opts & ~O_NONBLOCK;
        return fcntl(m_sock, F_SETFL, opts) != -1;
    }
    else {
        return false;
    }
}

bool Socket::send(const void *msg, size_t len) const {
    return ::send(m_sock, msg, len, 0) != -1;
}
