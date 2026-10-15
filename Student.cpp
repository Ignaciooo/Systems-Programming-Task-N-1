#include "Student.h"

namespace {
    const int W_NAME = 12, W_SURNAME = 15, W_NUM = 12;

    bool readScore(int &value, int lo, int hi) {
        while (true) {
            if (!(cin >> value)) return false;
            if (value >= lo && value <= hi) return true;
            cout << "  Value must be between " << lo << " and " << hi << ": ";
        }
    }
}

Student::Student() : name(""), surname(""), hw(), exam(0) {}

Student::Student(const string &N, const string &SN, const vector<int> &HW, int E)
    : name(N), surname(SN), hw(HW), exam(E) {
    auto bad = [](int v) { return v < MIN_SCORE || v > MAX_SCORE; };
    if (bad(E) || std::any_of(HW.begin(), HW.end(), bad))
        throw std::invalid_argument("Student " + N + " " + SN + ": scores must be between 1 and 10");
}

Student::Student(const Student &B)
    : name(B.name), surname(B.surname), hw(B.hw), exam(B.exam) {}

Student &Student::operator=(const Student &A) {
    if (this != &A) {
        name = A.name;
        surname = A.surname;
        hw = A.hw;
        exam = A.exam;
    }
    return *this;
}

Student::~Student() { clear(); }

void Student::clear() {
    name.clear();
    surname.clear();
    hw.clear();
    exam = 0;
}

void Student::input() {
    clear();
    cout << "Name: ";    cin >> name;
    cout << "Surname: "; cin >> surname;

    cout << "Enter homework results (1-10), enter 0 when you are done:\n";
    while (true) {
        cout << "  HW" << hw.size() + 1 << ": ";
        int n;
        if (!readScore(n, 0, 10)) {
            cin.clear();
            cin.ignore(10000, '\n');
            break;
        }
        if (n == 0) break;
        hw.push_back(n);
    }

    cout << "Exam (1-10): ";
    if (!readScore(exam, 1, 10)) {
        cin.clear();
        cin.ignore(10000, '\n');
        exam = 0;
    }
}

void Student::randomize(const string &N, const string &SN, RandInt &hwCount, RandInt &score) {
    clear();
    name = N;
    surname = SN;
    int n = hwCount();
    for (int i = 0; i < n; ++i) hw.push_back(score());
    exam = score();
}

double Student::average() const {
    if (hw.empty()) throw std::domain_error(name + " " + surname + ": no homework results");
    return accumulate(hw.begin(), hw.end(), 0.0) / static_cast<double>(hw.size());
}

double Student::median() const {
    if (hw.empty()) throw std::domain_error(name + " " + surname + ": no homework results");
    vector<int> tmp(hw);
    std::sort(tmp.begin(), tmp.end());
    size_t n = tmp.size();
    if (n % 2 == 1) return tmp[n / 2];
    return (tmp[n / 2 - 1] + tmp[n / 2]) / 2.0;
}

double Student::finalGrade(Method m) const {
    double h = (m == Method::Average) ? average() : median();
    return 0.4 * h + 0.6 * exam;
}

void Student::printHeader(Method m) {
    const char *title = (m == Method::Average) ? "Final_Point(Aver.)" : "Final_Point(Med.)";
    cout << left << setw(W_NAME) << "Name" << setw(W_SURNAME) << "Surname"
         << right << setw(W_NUM + 6) << title << "\n";
    cout << string(W_NAME + W_SURNAME + W_NUM + 6, '-') << "\n";
}

void Student::printHeaderBoth() { printHeaderBothTo(cout); }

void Student::printHeaderBothTo(ostream &out) {
    out << left << setw(W_NAME) << "Name" << setw(W_SURNAME) << "Surname"
         << right << setw(W_NUM) << "Final (Avg.)" << " | " << setw(W_NUM) << "Final (Med.)" << "\n";
    out << string(W_NAME + W_SURNAME + W_NUM + 3 + W_NUM, '-') << "\n";
}

void Student::print(Method m) const {
    cout << left << setw(W_NAME) << name << setw(W_SURNAME) << surname
         << right << std::fixed << std::setprecision(2) << setw(W_NUM + 6) << finalGrade(m) << "\n";
}

ostream &operator<<(ostream &out, const Student &A) {
    out << left << setw(W_NAME) << A.name << setw(W_SURNAME) << A.surname
        << right << std::fixed << std::setprecision(2)
        << setw(W_NUM) << A.finalGrade(Method::Average) << " | "
        << setw(W_NUM) << A.finalGrade(Method::Median);
    return out;
}

istream &operator>>(istream &in, Student &A) {
    string line;
    do {
        if (!std::getline(in, line)) return in;
    } while (line.find_first_not_of(" \t\r") == string::npos);

    std::istringstream ss(line);
    string n, s;
    vector<int> v;
    int x;
    if (!(ss >> n >> s)) { in.setstate(std::ios::failbit); return in; }
    while (ss >> x) v.push_back(x);
    if (!ss.eof() || v.size() < 2) { in.setstate(std::ios::failbit); return in; }
    if (std::any_of(v.begin(), v.end(), [](int k) { return k < Student::MIN_SCORE || k > Student::MAX_SCORE; })) {
        in.setstate(std::ios::failbit);
        return in;
    }

    A.clear();
    A.name = n;
    A.surname = s;
    A.exam = v.back();
    v.pop_back();
    A.hw = v;
    return in;
}
