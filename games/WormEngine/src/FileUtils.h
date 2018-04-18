#ifndef __FILE_UTILS__
#define __FILE_UTILS__

#include <cstdio>
#include <cstring>
#include <string>

class FileUtils {
public:
    static std::string readFile(const char *filename);
};

#endif
