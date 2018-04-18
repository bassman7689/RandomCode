#include <cstdlib>
#include <iostream>

#include "FileUtils.h"

std::string FileUtils::readFile(const char *filename)
{
    errno = 0;
    FILE *file = fopen(filename, "rt");
    if (file == NULL)
    {
        std::cout << "Error num: " << errno << std::endl;
        std::cout << "Filename:  " << filename << std::endl;
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = new char[length + 1];
    memset(data, 0, sizeof(char) * (length + 1));
    fread(data, length, length, file);

    fclose(file);

    std::string results(data);
    delete[] data;

    return results;
}
