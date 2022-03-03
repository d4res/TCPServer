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
    con_addr() {
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) throw "can not create a TCP socket";
}

TCPSocket::TCPSocket(int fd): 
    fd(fd),
    con_addr() {
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

    int _port = std::stoi(port);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(_port);
    
    if (bind(fd, (sockaddr *)&addr, sizeof(addr))) throw runtime_error(strerror(errno));
    if (::listen(fd, 8)) throw runtime_error(strerror(errno));
}

int TCPSocket::accept() {
    socklen_t addrlen;
    int con_fd = ::accept(fd, &con_addr, &addrlen);
    if (con_fd == -1) throw runtime_error(strerror(errno));
    return con_fd;
}

ssize_t TCPSocket::read(string &buffer) {
    ssize_t size;
    memset(buf, 0, sizeof(buf));
    size = ::read(fd, buf, sizeof(buf));
    buffer.assign(buf);
    return size;
}

ssize_t TCPSocket::write(const string buffer) {
    ssize_t size;
    size = ::write(fd, buffer.c_str(), buffer.size());
    perror(NULL);
    return size;
}