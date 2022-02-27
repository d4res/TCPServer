#include "Socket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <sstream>
#include <unistd.h>
#include <cassert>
#include <iostream>

using std::string;
using std::runtime_error;
using std::ostream;
using std::stringstream;

TCPSocket::TCPSocket():
    con_fd(-1), 
    con_addr() {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) throw "can not create a TCP socket";
}

void TCPSocket::connect(string host, string port) {
    struct addrinfo hints, *p;
    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;
    int ret = getaddrinfo(host.c_str(), port.c_str(), &hints, &p);
    if (ret) throw runtime_error(strerror(errno));
    ret = ::connect(fd, p->ai_addr, p->ai_addrlen);
    if(ret) throw runtime_error(strerror(errno));
}

void TCPSocket::listen(string port) {
    struct addrinfo hints, *p;
    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family =  AF_INET;
    getaddrinfo(NULL, port.c_str(), &hints, &p);
    if (bind(fd, p->ai_addr, p->ai_addrlen)) throw runtime_error(strerror(errno));
    if (::listen(fd, 8)) throw runtime_error(strerror(errno));
}

void TCPSocket::accept() {
    socklen_t addrlen;
    con_fd = ::accept(fd, &con_addr, &addrlen);
    if (con_fd == -1) throw runtime_error(strerror(errno));
}

ssize_t TCPSocket::read(string &buffer) {
    if (con_fd == -1) throw runtime_error("this socket does not connect to another socket"); 
    ssize_t size;
    memset(buf, 0, sizeof(buf));
    size = ::read(con_fd, buf, sizeof(buf));
    buffer.assign(buf);
    return size;
}