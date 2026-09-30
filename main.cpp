#include "lib.h"
#include "Student.h"

namespace {
    Method askMethod() {
        cout << "Calculate final grade by (a) average or (m) median? ";
        char c;
        cin >> c;
        return (c == 'm' || c == 'M') ? Method::Median : Method::Average;
    }

    void printOneMethod(const vector<Student> &group, Method m) {
        cout << "\nMethod: " << (m == Method::Average ? "average" : "median") << "\n";
        Student::printHeader(m);
        for (const Student &s : group) s.print(m);
        cout << endl;
    }

    void printBoth(const vector<Student> &group) {
        cout << endl;
        Student::printHeaderBoth();
        for (const Student &s : group) cout << s << "\n";
        cout << endl;
    }

    void manualInput(vector<Student> &group) {
        while (true) {
            cout << "Add a student? y/n ";
            char answ;
            cin >> answ;
            if (answ == 'n' || answ == 'N') break;
            Student s;
            s.input();
            group.push_back(s);
        }
        if (group.empty()) return;
        printOneMethod(group, askMethod());
    }

    void randomInput(vector<Student> &group) {
        static const vector<string> names    = {"Jonas", "Ona", "Petras", "Rasa", "Tomas", "Egle", "Lukas", "Ruta"};
        static const vector<string> surnames = {"Kazlauskas", "Petrauskas", "Jankauskas", "Butkus", "Paulauskas", "Stankevicius"};
        int n;
        cout << "How many students to generate? ";
        if (!(cin >> n) || n <= 0) { cin.clear(); cin.ignore(10000, '\n'); return; }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> pickN(0, names.size() - 1), pickS(0, surnames.size() - 1);
        for (int i = 0; i < n; ++i) {
            Student s;
            s.randomize(names[pickN(gen)], surnames[pickS(gen)], gen);
            group.push_back(s);
        }
        printOneMethod(group, askMethod());
    }

    void fileInput(vector<Student> &group) {
        string fName;
        cout << "Name file: ";
        cin >> fName;

        std::ifstream file("files/"+fName);
        if (!file) {
            cout << "Cannot open " << fName << "\n";
            return;
        }
        string header;
        std::getline(file, header);
        cin.ignore();

        int lineNo = 1;
        while (true) {
            Student s;
            if (file >> s) {
                group.push_back(s);
            } else if (file.eof()) {
                break;
            } else {
                file.clear();
                cout << "Warning: skipped invalid line near line " << lineNo + 1 << "\n";
            }
            ++lineNo;
        }
        printBoth(group);
    }
}

int main() {
    vector<Student> group;
    cout << "1 - enter students manually\n"
         << "2 - generate students randomly\n"
         << "3 - read students from a file\n"
         << "Choice: ";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1: manualInput(group); break;
        case 2: randomInput(group); break;
        case 3: fileInput(group);   break;
        default: cout << "Unknown choice\n";
    }
    return 0;
}
