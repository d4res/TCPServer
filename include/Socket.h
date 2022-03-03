#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <sys/socket.h>
#include <iostream>
#include <sstream>

using std::string;


const int READY = 0;
const int DOWNLOAD = 1;
const int UPLOAD = 2;
const int DOWNLOAD_INDEX = 3;
const int UPLOAD_INDEX = 4;

class TCPSocket {
private: 
    int fd; 
    struct sockaddr con_addr;
    static constexpr int BUFSIZE = 1024;
    char buf[BUFSIZ];

public:
    
    TCPSocket();
    TCPSocket(int);
    //~TCPSocket();

    void connect(std::string host, std::string port);

    void listen(std::string port);

    int accept();

    ssize_t read(string &buffer);

    ssize_t write(const string buffer);
};

#endif