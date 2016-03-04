/*
 * California Polytechnic State University, San Luis Obispo
 * Computer Engineering - CPE 402, 405, 406
 * Author: Frank Poole
 * Professor: David Janzen
 * Date: 1-16-2016
 * Disclaimer: The original version of the following code was taken from
 * tldp.org/LDP/LG/issue74/misc/tougher
 */

#include "ServerSocket.h"

ServerSocket::ServerSocket(const in_port_t port) {
    if (!Socket::Create()) {
        throw SocketException("Could not create server socket.");
    }
    if (!Socket::Bind(port)) {
        throw SocketException(
                (std::string) "Could not bind to port " + std::to_string(port));
    }
    if (!Socket::Listen()) {
        throw new SocketException("Could not listen on socket.");
    }
}

ServerSocket::~ServerSocket() {
}

const ServerSocket &ServerSocket::operator<<(const std::string &s) const {
    if (!Socket::Send(s)) {
        throw SocketException("Could not write to socket.");
    }

    return *this;
}

const ServerSocket &ServerSocket::operator>>(std::string &s) const {
    if (!Socket::Recv(s)) {
        throw SocketException("Could not read from socket.");
    }

    return *this;
}

::google::protobuf::uint32 ServerSocket::read_protobuf_header(
        const char *header) const {
    ::google::protobuf::uint32 size;
    char buf[PROTOBUF_HEADER_LENGTH];

    memcpy(buf, header, PROTOBUF_HEADER_LENGTH);
    ::google::protobuf::io::ArrayInputStream ais(buf, PROTOBUF_HEADER_LENGTH);
    ::google::protobuf::io::CodedInputStream coded_input(&ais);
    coded_input.ReadVarint32(&size);

    return size;
}

const ServerSocket &ServerSocket::operator<<(
        const ::google::protobuf::Message &msg) const {
    char *packet;
    size_t len = ProtobufSocketSerializer::serialize(msg, packet);

    if (!Socket::Send(packet, len)) {
        throw SocketException("Could not write to socket.");
    }

    delete packet;
    return *this;
}

void ServerSocket::read_protobuf(::google::protobuf::Message &msg,
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

    // De-Serialize
    msg.ParseFromCodedStream(&coded_input);

    // Once the embedded message has been parsed, PopLimit() is called to
    // undo the limit
    coded_input.PopLimit(msgLimit);
}

const ServerSocket &ServerSocket::operator>>(
        ::google::protobuf::Message &msg) const {
    // Read the first four bytes.
    char lenBfr[PROTOBUF_HEADER_LENGTH];
    if (!Socket::Recv(&lenBfr, PROTOBUF_HEADER_LENGTH, MSG_PEEK)) {
        throw SocketException("Could not read header from socket.");
    }

    // Read the protocol buffer data.
    ::google::protobuf::uint32 len = read_protobuf_header(lenBfr);
    char dataBuf[len + PROTOBUF_HEADER_LENGTH];
    if (!Socket::Recv(dataBuf, len + PROTOBUF_HEADER_LENGTH, MSG_WAITALL)) {
        throw SocketException("Could not read from socket.");
    }
    read_protobuf(msg, dataBuf);

    return *this;
}

void ServerSocket::accept(ServerSocket &sock) {
    if (!Socket::Accept(sock)) {
        throw SocketException("Could not accept socket.");
    }
}
