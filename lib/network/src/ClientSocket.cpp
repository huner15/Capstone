/*
 * California Polytechnic State University, San Luis Obispo
 * Computer Engineering - CPE 402, 405, 406
 * Author: Frank Poole
 * Professor: David Janzen
 * Date: 1-16-2016
 * Disclaimer: The original version of the following code was taken from
 * tldp.org/LDP/LG/issue74/misc/tougher
 */

#include "ClientSocket.h"

template<typename T>
std::string to_string(T value) {
    std::ostringstream os;
    os << value;

    return os.str();
}

ClientSocket::ClientSocket(std::string host, const in_port_t port) {
    if (!Socket::create()) {
        throw SocketException("Could not create client socket.");
    }

    if (!Socket::connect(host, port)) {
        throw SocketException("Could not connect to" + host + ":" +
                              to_string(port) + ".");
    }
}

const ClientSocket &ClientSocket::operator<<(const std::string &s) const {
    if (!Socket::send(s)) {
        throw SocketException("Could not write to socket.");
    }

    return *this;
}

const ClientSocket &ClientSocket::operator>>(std::string &s) const {
    if (!Socket::recv(s)) {
        throw SocketException("Could not read from socket.");
    }

    return *this;
}

const ClientSocket &ClientSocket::operator<<(
        const ::google::protobuf::Message &msg) const {
    char *packet;
    size_t len = ProtobufSocketSerializer::serialize(msg, packet);

    if (!Socket::send(packet, len)) {
        throw SocketException("Could not write to socket.");
    }

    delete packet;

    return *this;
}

::google::protobuf::uint32 ClientSocket::read_protobuf_header(
        const char *header) const {
    ::google::protobuf::uint32 size;
    char buf[PROTOBUF_HEADER_LENGTH];

    memcpy(buf, header, PROTOBUF_HEADER_LENGTH);
    ::google::protobuf::io::ArrayInputStream ais(buf, PROTOBUF_HEADER_LENGTH);
    ::google::protobuf::io::CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&size);//Decode the header and get the size

    return size;
}

void ClientSocket::read_protobuf(::google::protobuf::Message &msg,
                                 const char *data) const {
    // Read the header again to determine the message length.
    ::google::protobuf::uint32 size = read_protobuf_header(data);
    char buf[PROTOBUF_HEADER_LENGTH + size];
    memcpy(buf, data, PROTOBUF_HEADER_LENGTH + size);

    ::google::protobuf::io::ArrayInputStream ais(
            buf, PROTOBUF_HEADER_LENGTH + size);

    // Re-read the input length
    ::google::protobuf::io::CodedInputStream coded_input(&ais);

    // Read an unsigned integer with variant encoding, truncating to 32 bits.
    ::google::protobuf::uint32 siz;
    coded_input.ReadVarint32(&siz);

    // Read the remainder of the message
    ::google::protobuf::io::CodedInputStream::Limit msgLimit =
            coded_input.PushLimit(siz);

    //De-Serialize
    msg.ParseFromCodedStream(&coded_input);

    // Once the embedded message has been parsed, PopLimit() is called to
    // undo the limit
    coded_input.PopLimit(msgLimit);
}

const ClientSocket &ClientSocket::operator>>(
        ::google::protobuf::Message &msg) const {
    char lenBfr[PROTOBUF_HEADER_LENGTH];

    // Read the protocol buffer size header (first four bytes).
    // TODO: This condition used to be ! instead of != 1.
    if (Socket::recv(&lenBfr, PROTOBUF_HEADER_LENGTH, MSG_PEEK) == -1) {
        throw SocketException("Could not read header from socket.");
    }

    // Read the protocol buffer data.
    ::google::protobuf::uint32 len = read_protobuf_header(lenBfr);
    char dataBuf[PROTOBUF_HEADER_LENGTH + len];
    // TODO: This condition used to be ! instead of != 1.
    if (Socket::recv(dataBuf, len + PROTOBUF_HEADER_LENGTH, MSG_WAITALL)
        == -1) {
        throw SocketException("Could not read from socket.");
    }

    read_protobuf(msg, dataBuf);

    return *this;
}
