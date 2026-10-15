#pragma once
#include "lib.h"
#include "Student.h"

struct SpeedTestResult {
    size_t records = 0, failed = 0, passed = 0;
    double read = 0, sort = 0, split = 0, write = 0, total = 0;
};

class SpeedTest {
    Method method;
    string dir;

public:
    explicit SpeedTest(Method m = Method::Average, string directory = "files")
        : method(m), dir(std::move(directory)) {}

    SpeedTestResult runOne(size_t records) const;

    void runAll(const vector<size_t> &sizes) const;
};
