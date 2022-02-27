// 文件传输server端
// 功能:
// 接收来自客户端的文件
// 客户端指定文件名, 服务端发送

#include <iostream>
#include <sys/socket.h>
#include <vector>
#include "Socket.h"
#include "File.h"

using std::vector;
using std::string;
using  std::cout;
using std::endl;

void printOption() {
    cout << "This is the server side" << endl;
    cout << "waiting for client to connect" << endl;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: server port" << endl;
        //exit(0);  
    }
    //string port(argv[1]);
    printOption();

    // TCPSocket serverSocket;
    // serverSocket.listen("5566");
    // serverSocket.accept();
    // string buffer;
    // while (serverSocket.read(buffer) ) cout << buffer;

    vector<string> v = scanDir("./files");

    
    return 0;
}