#pragma once
#include "lib.h"
#include "Student.h"

class StudentGroup {
    vector<Student> students;

public:
    static constexpr double PASS_MARK = 5.0;

    void add(Student s) {
        students.push_back(std::move(s));
    }

    size_t size() const {
        return students.size();
    }

    bool empty() const {
        return students.empty();
    }

    const vector<Student> &all() const {
        return students;
    }

    size_t load(const string &path);

    void save(const string &path) const;

    void sortByFinal(Method m);

    StudentGroup extractFailed(Method m);
};
