/**
 * @file Socket.cpp
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 3-3-16
 * @brief A Socket is a logical endpoint for communications that exists on the
 * transport layer. Disclaimer: The original version of the following code was
 * taken from tldp.org/LDP/LG/issue74/misc/tougher
 */

#include "Socket.h"

Socket::Socket() : _m_sock(-1) {
    ::memset(&_m_addr, 0, sizeof(_m_addr));
}

Socket::~Socket() {
    if (IsValid()) {
        ::close(_m_sock);
    }
}

bool Socket::Create() {
    int opt = 1;
    _m_sock = socket(AF_INET, SOCK_STREAM, 0);
    return IsValid() && ::setsockopt(_m_sock, SOL_SOCKET, SO_REUSEADDR,
                                     (const char *) &opt, sizeof(opt)) != -1;
}

bool Socket::Bind(const in_port_t port) {
    if (IsValid()) {
        _m_addr.sin_family = AF_INET;
        _m_addr.sin_addr.s_addr = INADDR_ANY;
        _m_addr.sin_port = htons(port);
        return ::bind(_m_sock, (struct sockaddr *) &_m_addr,
                      sizeof(_m_addr)) != -1;
    }
    else {
        return false;
    }
}

bool Socket::Listen() const {
    return IsValid() && ::listen(_m_sock, _MAX_CONNECTIONS) != -1;
}

bool Socket::Accept(Socket &new_socket) const {
    socklen_t addr_len = sizeof(_m_addr);
    new_socket._m_sock = ::accept(_m_sock, (sockaddr *) &_m_addr, &addr_len);
    return new_socket.IsValid();
}

bool Socket::Send(const std::string &msg) const {
    return ::send(_m_sock, msg.c_str(), msg.size(), 0) != -1;
}

size_t Socket::Recv(std::string &bfr, int flags) const {
    char buf[_MAX_RECV + 1];
    memset(buf, 0, _MAX_RECV + 1);
    ssize_t status = ::recv(_m_sock, buf, _MAX_RECV, flags);

    if (status == -1) {
        std::cout << "Status == -1, errno == " << errno
        << "In Socket::recv" << std::endl;
        return 0;
    }
    else {
        bfr = buf;
        return (size_t) status;
    }
}

size_t Socket::Recv(void *bfr, size_t len, int flags) const {
    ssize_t status = ::recv(_m_sock, bfr, len, flags);

    if (status == -1) {
        std::cout << "Status == -1, errno == " << errno
        << "In Socket::recv" << std::endl;
        return 0;
    }
    else {
        return (size_t) status;
    }
}

bool Socket::Connect(const std::string host, const in_port_t port) {
    if (IsValid()) {
        _m_addr.sin_family = AF_INET;
        _m_addr.sin_port = htons(port);
        inet_pton(AF_INET, host.c_str(), &_m_addr.sin_addr);
        return errno != EAFNOSUPPORT &&
               ::connect(_m_sock, (sockaddr *) &_m_addr, sizeof(_m_addr)) != -1;
    }
    else {
        return false;
    }
}

bool Socket::SetNonBlocking(const bool is_non_blocking) {
    int opts = fcntl(_m_sock, F_GETFL);

    if (opts != -1) {
        opts = is_non_blocking ? opts | O_NONBLOCK : opts & ~O_NONBLOCK;
        return fcntl(_m_sock, F_SETFL, opts) != -1;
    }
    else {
        return false;
    }
}

bool Socket::Send(const void *msg, size_t len) const {
    return ::send(_m_sock, msg, len, 0) != -1;
}
