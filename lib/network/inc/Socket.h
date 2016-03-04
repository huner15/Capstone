/**
 * @file Socket.h
 * @author Specific Atomics
 * @authors Frank Poole
 * @date 3-3-16
 * @brief A Socket is a logical endpoint for communications that exists on the
 * transport layer. Disclaimer: The original version of the following code was
 * taken from tldp.org/LDP/LG/issue74/misc/tougher
 */

#ifndef Socket_H_
#define Socket_H_

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

/**
 * A Socket is a logical endpoint for communications that exists on the
 * transport layer. The Socket class includes functions for initializing
 * connections with other hosts and sending and receiving data.
 */
class Socket {
private:
    /** The socket file descriptor. */
    int _m_sock;

    /** System call structure for handling internet addresses. */
    sockaddr_in _m_addr;

    /** Maximum number of characters in a host's name. */
    const int _MAX_HOSTNAME = 200;

    /** Maximum number of connections to be maintained. */
    const int _MAX_CONNECTIONS = 5;

    /** Maximum number of characters that may be received. */
    const int _MAX_RECV = 500;

public:
    Socket();

    virtual ~Socket();

    /**
     * Create a new socket.
     * @return true if no errors occurred
     */
    bool Create();

    /**
     * Bind a socket to a port.
     * @param port the port to bind the socket to
     * @return true if no errors occurred
     */
    bool Bind(const in_port_t port);

    /**
     * Listen for incoming network connections.
     * @return true if no errors occurred
     */
    bool Listen() const;

    /**
     * Accept a socket connection and bind the socket.
     * @return true if no errors occurred
     */
    bool Accept(Socket &new_socket) const;

    /**
     * Connect to a socket.
     * @param host the host to connect to
     * @param port the port to connect to
     * @return true if connection was successful
     */
    bool Connect(const std::string host, const in_port_t port);

    /**
     * Send string data to connected hosts.
     * @param msg the string message to send
     * @return true if no errors occurred
     */
    bool Send(const std::string &msg) const;

    /**
     * Send raw data to connected hosts.
     * @param msg the raw data to send
     * @param len the length of the data
     * @return true if no errors occurred
     */
    bool Send(const void *msg, size_t len) const;

    /**
     * Receive string data from the socket (Default, 500 bytes).
     * @param bfr the string to write to
     * @param flags flags for socket reading options
     * @return the number of bytes read
     */
    size_t Recv(std::string &bfr, int flags = 0) const;

    /**
     * Receive raw data from the socket.
     * @param bfr the buffer to write data into
     * @param len the number of bytes to receive
     * @param flags flags for socket reading options
     * @return the number of bytes read
     */
    size_t Recv(void *bfr, size_t len, int flags = 0) const;

    /**
     * Set the socket to non-blocking mode.
     * @param bool true if the socket should block, false if the socket
     * shouldn't block
     */
    bool SetNonBlocking(const bool is_non_blocking);

    /**
     * Check of the socket is valid for use.
     * @return true if the socket is valid for use or return false if the
     * socket has not been created
     */
    bool IsValid() const {
        return _m_sock != -1;
    }
};

#endif
