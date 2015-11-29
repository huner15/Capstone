#ifndef __PROTOBUF_SOCKET_SERIALIZER_H__
#define __PROTOBUF_SOCKET_SERIALIZER_H__

#include <google/protobuf/message.h>

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
     * @param packet The data buffer to write data into.
     * This will be allocated in the serializer.
     * @return the number of bytes encoded.
     */
    static int serialize(
            const ::google::protobuf::Message &msg, char *&packet);
};

#endif