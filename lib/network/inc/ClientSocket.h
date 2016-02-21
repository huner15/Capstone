/*
 * California Polytechnic State University, San Luis Obispo
 * Computer Engineering - CPE 402, 405, 406
 * Author: Frank Poole
 * Professor: David Janzen
 * Date: 1-16-2016
 * Disclaimer: The original version of the following code was taken from
 * tldp.org/LDP/LG/issue74/misc/tougher
 */

#ifndef ClientSocket_H
#define ClientSocket_H

#include <iostream>
#include <sstream>
#include <google/protobuf/message.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>

#include "Socket.h"
#include "SocketException.h"
#include "ProtobufSocketSerializer.h"

/**
 * A Client Socket is a socket that connects to an open port. The client socket
 * should be used when it wants to communicate with an already open socket.
 * String data and protocol buffer data can be sent through the socket
 */
class ClientSocket : private Socket {
public:
    /**
     * Create a new socket, and connect to the specified host and port.
     * @param host the address or address alias of the host computer
     * @param port the port to connect to
     */
    ClientSocket(std::string host, const in_port_t port);

    /**
     * Close the socket.
     */
    virtual ~ClientSocket() {};

    /**
     * Send string data to the connected host.
     * @param string the data to send
     * @return the socket, for chaining
     */
    const ClientSocket &operator<<(const std::string &) const;

    /**
     * Receive string data from the connected host.
     * @param string the string to read data into
     * @return the socket, for chaining
     */
    const ClientSocket &operator>>(std::string &) const;

    /**
     * Send protocol buffer data from the connected host.
     * @param msg the message to send
     * @return the Socket, for chaining
     */
    const ClientSocket &operator<<(
            const ::google::protobuf::Message &msg) const;

    /**
     * Receive protocol buffer data from the connected host.
     * @param msg the message to read into
     * @return the socket, for chaining
     */
    const ClientSocket &operator>>(::google::protobuf::Message &msg) const;

private:
    /**
     * Read the length of the protocol buffer from the header.
     * Disclaimer: Taken from http://stackoverflow.com/questions/9496101/
     * protocol-buffer-over-socket-in-c
     * @param header raw data containing the protocol buffer header
     * @return the length of the protocol buffer message
     */
    ::google::protobuf::uint32 read_protobuf_header(const char *header) const;

    /**
     * Read a protocol buffer from raw data.
     * @param msg the message to read into
     * @param data the raw data
     */
    void read_protobuf(::google::protobuf::Message &msg,
                       const char *data) const;
};

#endif
