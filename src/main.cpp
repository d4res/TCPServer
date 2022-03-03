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
using std::ofstream;
using std::endl;
using std::ifstream;
using std::stoi;
using std::stringstream;

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


    int status = READY;

    while (true) {
        int fd = serverSocket.accept();
        TCPSocket conSocket(fd);
        cout << "client connected" << endl;
        string buffer;
        vector<string> files = scanDir(FILEDIR);
        // for (size_t i = 0; i < files.size(); ++i) {
        //     string index = std::to_string(i) + ".";
        //     cout << std::left;
        //     cout << std::setw(3) << index ;
        //     cout << files[i] << endl; 
        // }

        while (conSocket.read(buffer)) {

            switch (status) {
            case READY:
                if (buffer == "upload") {
                    cout << "client is going to upload a file" << endl;
                    status = UPLOAD_INDEX;
                    conSocket.write("OK");
                }   

                if (buffer == "download") {
                    cout << "client is going to download a file" << endl;
                    status = DOWNLOAD_INDEX;
                    string replay;
                    stringstream ss;
                    
                    for (size_t i = 0; i < files.size(); ++i ) {
                        string index = std::to_string(i) + ".";
                        ss << std::left;
                        ss << std::setw(3) << index;
                        ss << files[i] << endl;
                    }
                    
                    replay = ss.str();
                    cout << replay;
                    conSocket.write(replay);
                }         
            case UPLOAD_INDEX:

                
            case DOWNLOAD_INDEX:
                // int download_index = stoi(buffer);
                // ifstream file_input(FILEDIR + "/" + files[download_index]);
                // string _buf;
                // while (file_input >> _buf) {
                //     conSocket.write(_buf);
                // }
                break;
            }
        }
    }

    return 0;
}