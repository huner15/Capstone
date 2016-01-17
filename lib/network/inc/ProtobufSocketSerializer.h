/*
 * California Polytechnic State University, San Luis Obispo
 * Computer Engineering - CPE 402, 405, 406
 * Author: Frank Poole
 * Professor: David Janzen
 * Date: 1-16-2016
 */

#ifndef PROTOBUF_SOCKET_SERIALIZER_H
#define PROTOBUF_SOCKET_SERIALIZER_H

#include <iostream>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/message.h>

/**
 * The first four bytes of the shared protocol contains the size of the
 * following data.
 */
#define PROTOBUF_HEADER_LENGTH 4

/**
 * The protocol buffer socket serializer is used to encode header data into any
 * protocol buffer. The header is four bytes containing the length of the
 * buffer data.
 */
class ProtobufSocketSerializer {
public:
    /**
     * Serialize data for sending over a socket.
     * @param msg the protocol buffer message
     * @param packet The data buffer to write data into
     * @return the number of bytes encoded
     */
    static size_t serialize(
            const ::google::protobuf::Message &msg, char *&packet);
};

#endif
