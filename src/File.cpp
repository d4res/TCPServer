#include "File.h"
#include <dirent.h>
#include <sys/types.h>
#include <string>
#include <vector>
#include <iostream>
#include <cerrno>
#include <cstdlib>
#include <unistd.h>
#include <cstring>

using std::vector;
using std::string;
using std::runtime_error;
using std::cout;
using std::endl;

vector<string> scanDir( const string dir){
    vector<string> files;

    const char* _dir = dir.c_str();
    DIR *pdir;

    pdir = opendir(_dir);
    if (pdir == NULL) throw runtime_error(strerror(errno));

    struct dirent *pdirent;
    string filename;
    while (pdirent = readdir(pdir)) {
        filename.assign(pdirent->d_name);
        if (filename == "." || filename == "..") continue;
       files.push_back(filename);
    }

    return files;
}
