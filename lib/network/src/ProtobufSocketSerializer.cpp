/*
 * California Polytechnic State University, San Luis Obispo
 * Computer Engineering - CPE 402, 405, 406
 * Author: Frank Poole
 * Professor: David Janzen
 * Date: 1-16-2016
 * Disclaimer: The original version of the following code was taken from
 * tldp.org/LDP/LG/issue74/misc/tougher
 */

#include "ProtobufSocketSerializer.h"

size_t ProtobufSocketSerializer::serialize(
        const ::google::protobuf::Message &msg, char *&packet) {
    size_t size = PROTOBUF_HEADER_LENGTH + (size_t) msg.ByteSize();
    packet = new char[size]();

    ::google::protobuf::io::ArrayOutputStream aos(packet, (int) size);
    ::google::protobuf::io::CodedOutputStream coded_output(&aos);
    coded_output.WriteLittleEndian32((google::protobuf::uint32) msg.ByteSize());
    msg.SerializeToCodedStream(&coded_output);

    return size;
}
