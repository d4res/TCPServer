// 文件传输server端
// 功能:
// 接收来自客户端的文件
// 客户端指定文件名, 服务端发送

#include <iostream>
#include <sys/socket.h>
#include <vector>
#include <fstream>
#include <iomanip>
#include "Socket.h"
#include "File.h"

using std::fstream;
using std::vector;
using std::string;
using  std::cout;
using std::endl;
using std::ifstream;

void printOption() {
    cout << "This is the server side" << endl;
    cout << "waiting for client to connect" << endl;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: server port" << endl;
        exit(0);
    }
    printOption();

    TCPSocket serverSocket;
    serverSocket.listen(argv[1]);

    while (true) {
        serverSocket.accept();
        cout << "client connected" << endl;
        string buffer;
        vector<string> files = scanDir(FILEDIR);
        for (size_t i = 0; i < files.size(); ++i) {
            string index = std::to_string(i) + ".";
            cout << std::left;
            cout << std::setw(3) << index ;
            cout << files[i] << endl; 
        }


        // waiting for command
        while (serverSocket.read(buffer)) {
            if (buffer == "upload") {
                cout << "upload" << endl;
            } 
        }

        // ifstream input(FILEDIR + "/" + files[0]); 
        // string buf;
        // while (input >> buf) {
        //     serverSocket.write(buf);
        // }
    }

    return 0;
}