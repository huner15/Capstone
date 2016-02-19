/*
 * California Polytechnic State University, San Luis Obispo
 * Computer Engineering - CPE 402, 405, 406
 * Author: Frank Poole
 * Professor: David Janzen
 * Date: 1-16-2016
 * Disclaimer: The original version of the following code was taken from
 * tldp.org/LDP/LG/issue74/misc/tougher
 */

#ifndef ServerSocket_H
#define ServerSocket_H

#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <arpa/inet.h>
#include <google/protobuf/message.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/descriptor.h>

#include "Socket.h"
#include "SocketException.h"
#include "ProtobufSocketSerializer.h"

/**
 * A Server Socket is a socket used primarily by a server application,
 * or whenever the socket expects to receive a connection, instead of
 * connect to one. String data and protobuf data can be sent over the sockets.
 */
class ServerSocket : private Socket {
public:
    /**
     * Create and open a socket on the specified port.
     * @param port the port number
     */
    ServerSocket(const in_port_t port);

    /**
     * Create a socket for accepting a current connection.
     */
    ServerSocket() { }

    /**
     * Close the socket.
     */
    virtual ~ServerSocket();

    /**
    * Write a string to the client.
    * string the string to write
    */
    const ServerSocket &operator<<(const std::string &) const;

    /**
     * Read a string form the client.
     * string the string to read into
     */
    const ServerSocket &operator>>(std::string &) const;

    /**
     * Write a protocol buffer to the client.
     * msg the protocol buffer message to write
     */
    const ServerSocket &operator<<(
            const ::google::protobuf::Message &msg) const;

    /**
     * Read a protocol buffer from the client into message.
     * msg the protocol buffer message to read into
     */
    const ServerSocket &operator>>(::google::protobuf::Message &msg) const;

    /**
     * Accept a connection and bind it to the new socket.
     */
    void accept(ServerSocket &sock);

private:
    /**
     * Read a the header length from a protocol buffer.
     * Disclaimer: Taken from http://stackoverflow.com/questions/9496101/
     * protocol-buffer-over-socket-in-c
     * @param data the raw bytes of the protocol buffer
     * @return the length of the header
     */
    ::google::protobuf::uint32 read_protobuf_header(const char *data) const;

    /**
     * Read a protocol buffer from raw data.
     * @param msg the message to read
     * @param data the raw data containing the message plus the header
     */
    void read_protobuf(::google::protobuf::Message &msg,
                       const char *data) const;
};

#endif
