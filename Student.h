#pragma once
#include "lib.h"
#include "RandInt.hpp"

enum class Method { Average, Median };

class Student {
    string name, surname;
    vector<int> hw;
    int exam;

public:
    static constexpr int MIN_SCORE = 1, MAX_SCORE = 10;

    Student();
    
    Student(const string &N, const string &SN, const vector<int> &HW, int E);

    Student(const Student &B);
    Student &operator=(const Student &A);
    ~Student();

    void clear();
    void input();
    void randomize(const string &N, const string &SN, RandInt &hwCount, RandInt &score);

    const string &getName() const { return name; }
    const string &getSurname() const { return surname; }

    double average() const;
    double median() const;
    double finalGrade(Method m) const;

    void print(Method m) const;
    static void printHeader(Method m);
    static void printHeaderBoth();
    static void printHeaderBothTo(ostream &out);

    friend istream &operator>>(istream &in, Student &A);
    friend ostream &operator<<(ostream &out, const Student &A);
};
