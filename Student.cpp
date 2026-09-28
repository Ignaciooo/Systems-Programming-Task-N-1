#include "Student.h"

namespace {
    const int W_NAME = 12, W_SURNAME = 15, W_NUM = 12;

    // Reads an integer in [lo, hi]; returns false if the input is not a number.
    bool readScore(int &value, int lo, int hi) {
        while (true) {
            if (!(cin >> value)) return false;
            if (value >= lo && value <= hi) return true;
            cout << "  Value must be between " << lo << " and " << hi << ": ";
        }
    }
}

// ---------- Rule of three ----------
Student::Student() : name(""), surname(""), hw(), exam(0) {}

Student::Student(const string &N, const string &SN, const vector<int> &HW, int E)
    : name(N), surname(SN), hw(HW), exam(E) {}

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

// ---------- Input ----------
void Student::input() {
    clear();
    cout << "Name: ";    cin >> name;
    cout << "Surname: "; cin >> surname;

    cout << "Enter homework results (1-10), enter 0 when you are done:\n";
    while (true) {
        cout << "  HW" << hw.size() + 1 << ": ";
        int n;
        if (!readScore(n, 0, 10)) {           // not a number -> stop homework input
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

void Student::randomize(const string &N, const string &SN, std::mt19937 &gen) {
    clear();
    name = N;
    surname = SN;
    std::uniform_int_distribution<int> count(3, 10), score(1, 10);
    int n = count(gen);
    for (int i = 0; i < n; ++i) hw.push_back(score(gen));
    exam = score(gen);
}

// ---------- Calculations ----------
double Student::average() const {
    if (hw.empty()) return 0.0;
    return accumulate(hw.begin(), hw.end(), 0.0) / hw.size();
}

double Student::median() const {
    if (hw.empty()) return 0.0;
    vector<int> tmp(hw);                       // sort a copy, keep original order
    std::sort(tmp.begin(), tmp.end());
    size_t n = tmp.size();
    if (n % 2 == 1) return tmp[n / 2];
    return (tmp[n / 2 - 1] + tmp[n / 2]) / 2.0;
}

double Student::finalGrade(Method m) const {
    double h = (m == Method::Average) ? average() : median();
    return 0.4 * h + 0.6 * exam;
}

// ---------- Output ----------
void Student::printHeader(Method m) {
    const char *title = (m == Method::Average) ? "Final_Point(Aver.)" : "Final_Point(Med.)";
    cout << left << setw(W_NAME) << "Name" << setw(W_SURNAME) << "Surname"
         << right << setw(W_NUM + 6) << title << "\n";
    cout << string(W_NAME + W_SURNAME + W_NUM + 6, '-') << "\n";
}

void Student::printHeaderBoth() {
    cout << left << setw(W_NAME) << "Name" << setw(W_SURNAME) << "Surname"
         << right << setw(W_NUM) << "Final (Avg.)" << " | " << setw(W_NUM) << "Final (Med.)" << "\n";
    cout << string(W_NAME + W_SURNAME + W_NUM + 3 + W_NUM, '-') << "\n";
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
    do {                                       // skip blank lines
        if (!std::getline(in, line)) return in;
    } while (line.find_first_not_of(" \t\r") == string::npos);

    std::istringstream ss(line);
    string n, s;
    vector<int> v;
    int x;
    if (!(ss >> n >> s)) { in.setstate(std::ios::failbit); return in; }
    while (ss >> x) v.push_back(x);
    if (!ss.eof() || v.empty()) { in.setstate(std::ios::failbit); return in; }   // bad line

    A.clear();
    A.name = n;
    A.surname = s;
    A.exam = v.back();                         // last number is the exam
    v.pop_back();
    A.hw = v;
    return in;
}
