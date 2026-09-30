#pragma once
#include "lib.h"

enum class Method { Average, Median };

class Student {
    string name, surname;
    vector<int> hw;
    int exam;

public:
    Student();
    Student(const string &N, const string &SN, const vector<int> &HW, int E);
    Student(const Student &B);
    Student &operator=(const Student &A);
    ~Student();

    void clear();

    void input();

    void randomize(const string &N, const string &SN, std::mt19937 &gen);

    double average() const;
    double median() const;
    double finalGrade(Method m) const;

    void print(Method m) const;
    static void printHeader(Method m);
    static void printHeaderBoth();

    friend istream &operator>>(istream &in, Student &A);
    friend ostream &operator<<(ostream &out, const Student &A);
};
