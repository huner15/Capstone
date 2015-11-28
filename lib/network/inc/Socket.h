//Taken from tldp.org/LDP/LG/issue74/misc/tougher

#ifndef Socket_class
#define Socket_class

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

const int MAX_HOSTNAME = 200;
const int MAX_CONNECTIONS = 5;
const int MAX_RECV = 500;

class Socket {
public:
    Socket();

    virtual ~Socket();

    /**
     * create a new socket
     * @return true if no problems occurred.
     */
    bool create();

    /**
     * Bind a socket to a port
     * @param  port the port to bind the socket to
     * @return      true if no problems
     */
    bool bind(const in_port_t port);

    /**
     * Listen for incoming connections
     * @return true if no issues on listening.
     */
    bool listen() const;

    /**
     * Accept a socket connection, and bind it to the new socket.
     */
    bool accept(Socket &) const;

    /**
     * Connect to a current socket
     * @param host the host to connect to
     * @param port the port to connect to
     * @return true if connection was successful
     */
    bool connect(const std::string host, const in_port_t port);

    /**
     * Send string data down the socket
     * @param  msg the string message to send
     * @return     true if no issues
     */
    bool send(const std::string &msg) const;

    /**
     * Send raw data down the socket
     * @param  msg the raw data to send
     * @param  len the length of the data
     * @return true if no issues.
     */
    bool send(const void *msg, size_t len) const;

    /**
     * Receive string data from the socket. (Default, 500 bytes)
     * @param  bfr   The string to write to
     * @param  flags Flags for socket reading options
     * @return       the number of bytes read
     */
    size_t recv(std::string &bfr, int flags = 0) const;

    /**
     * Receive raw data from a socket
     * @param  bfr the buffer to write data into (Ensure it is big enough!)
     * @param  len the number of bytes to receive
     * @param  flags flags for socket reading options
     * @return          the number of bytes read
     */
    size_t recv(void *bfr, size_t len, int flags = 0) const;

    /**
     * Set the socket to non-blocking mode
     * @param bool whether or not the socket should block
     */
    bool set_non_blocking(const bool);

    /**
     * Check of the socket is valid for use
     * @return false if the socket has not been created
     */
    bool is_valid() const {
        return m_sock != -1;
    }

private:
    int m_sock;
    sockaddr_in m_addr;
};

#endif