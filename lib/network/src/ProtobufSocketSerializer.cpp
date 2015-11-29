#include <iostream>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>

#include "ProtobufSocketSerializer.h"

#define HEADER_LEN 4

int ProtobufSocketSerializer::serialize(
        const ::google::protobuf::Message &msg, char *&packet) {
    int size = msg.ByteSize() + HEADER_LEN;
    packet = new char[size]();

    ::google::protobuf::io::ArrayOutputStream aos(packet, size);
    ::google::protobuf::io::CodedOutputStream coded_output(&aos);
    coded_output.WriteVarint32((google::protobuf::uint32) msg.ByteSize());
    msg.SerializeToCodedStream(&coded_output);

    return size;
}