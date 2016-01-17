/*
 * California Polytechnic State University, San Luis Obispo
 * Computer Engineering - CPE 402, 405, 406
 * Author: Frank Poole
 * Professor: David Janzen
 * Date: 1-16-2016
 * Disclaimer: The original version of the following code was taken from
 * tldp.org/LDP/LG/issue74/misc/tougher
 */

#ifndef Socket_H
#define Socket_H

#include <string>
#include <string.h>
#include <fcntl.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

/** Maximum number of characters in a host's name. */
const int MAX_HOSTNAME = 200;

/** Maximum number of connections to be maintained. */
const int MAX_CONNECTIONS = 5;

/** Maximum number of characters that may be received. */
const int MAX_RECV = 500;

/**
 * A Socket is a logical endpoint for communications that exists on the
 * transport layer. The Socket class includes functions for initializing
 * connections with other hosts and sending and receiving data.
 */
class Socket {
public:
    Socket();

    virtual ~Socket();

    /**
     * Create a new socket.
     * @return true if no errors occurred
     */
    bool create();

    /**
     * Bind a socket to a port.
     * @param port the port to bind the socket to
     * @return true if no errors occurred
     */
    bool bind(const in_port_t port);

    /**
     * Listen for incoming network connections.
     * @return true if no errors occurred
     */
    bool listen() const;

    /**
     * Accept a socket connection and bind the socket.
     * @return true if no errors occurred
     */
    bool accept(Socket &) const;

    /**
     * Connect to a socket.
     * @param host the host to connect to
     * @param port the port to connect to
     * @return true if connection was successful
     */
    bool connect(const std::string host, const in_port_t port);

    /**
     * Send string data to connected hosts.
     * @param msg the string message to send
     * @return true if no errors occurred
     */
    bool send(const std::string &msg) const;

    /**
     * Send raw data to connected hosts.
     * @param msg the raw data to send
     * @param len the length of the data
     * @return true if no errors occurred
     */
    bool send(const void *msg, size_t len) const;

    /**
     * Receive string data from the socket (Default, 500 bytes).
     * @param bfr the string to write to
     * @param flags flags for socket reading options
     * @return the number of bytes read
     */
    size_t recv(std::string &bfr, int flags = 0) const;

    /**
     * Receive raw data from the socket.
     * @param bfr the buffer to write data into
     * @param len the number of bytes to receive
     * @param flags flags for socket reading options
     * @return the number of bytes read
     */
    size_t recv(void *bfr, size_t len, int flags = 0) const;

    /**
     * Set the socket to non-blocking mode.
     * @param bool true if the socket should block, false if the socket
     * shouldn't block
     */
    bool set_non_blocking(const bool);

    /**
     * Check of the socket is valid for use.
     * @return true if the socket is valid for use or return false if the
     * socket has not been created
     */
    bool is_valid() const {
        return m_sock != -1;
    }

private:
    /** The socket file descriptor. */
    int m_sock;

    /** System call structure for handling internet addresses. */
    sockaddr_in m_addr;
};

#endif
