#pragma once
#include "lib.h"

// Method used to turn the homework results into a single number
enum class Method { Average, Median };

class Student {
    string name, surname;
    vector<int> hw;      // homework results (any amount)
    int exam;

public:
    // Rule of three
    Student();
    Student(const string &N, const string &SN, const vector<int> &HW, int E);
    Student(const Student &B);
    Student &operator=(const Student &A);
    ~Student();

    void clear();

    // Interactive input from the console (n of homework is not known in advance)
    void input();
    // Random homework and exam results
    void randomize(const string &N, const string &SN, std::mt19937 &gen);

    // Calculations
    double average() const;                        // average of homework
    double median() const;                         // median of homework
    double finalGrade(Method m) const;             // 0.4 * (avg|med) + 0.6 * exam

    // Output
    void print(Method m) const;                    // one row, one method
    static void printHeader(Method m);             // header for one method
    static void printHeaderBoth();                 // header for both methods

    // Overloaded stream operators
    // >> reads ONE line: Name Surname HW1 ... HWn Exam   (last number = exam)
    // << writes ONE row: Avg | Med
    friend istream &operator>>(istream &in, Student &A);
    friend ostream &operator<<(ostream &out, const Student &A);
};
