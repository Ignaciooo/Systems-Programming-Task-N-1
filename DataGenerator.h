#pragma once
#include "lib.h"
#include "RandInt.hpp"

class DataGenerator {
    RandInt score;
    int hwCount;

public:
    explicit DataGenerator(int hwPerStudent = 5);

    void generateFile(const string &path, size_t count);
    
    static string studentsPath(size_t count, const string &dir = "files");
};
