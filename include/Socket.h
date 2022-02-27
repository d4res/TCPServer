#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <sys/socket.h>
#include <iostream>
#include <sstream>

using std::string;

class TCPSocket {
private: 
    int fd;

    int con_fd; 
    struct sockaddr con_addr;
    static constexpr int BUFSIZE = 1024;
    char buf[BUFSIZ];

public:
    
    TCPSocket();
    //~TCPSocket();

    void connect(std::string host, std::string port);

    void listen(std::string port);

    void accept();

    ssize_t read(string &buffer);
};

#endif