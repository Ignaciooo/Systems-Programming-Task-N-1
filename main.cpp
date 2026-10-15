#include "lib.h"
#include "Student.h"
#include "StudentGroup.h"
#include "DataGenerator.h"
#include "SpeedTest.h"
#include "Timer.h"
#include "ExceptionHandler.h"

namespace {
    const vector<size_t> SIZES = {1000, 10000, 100000, 1000000, 10000000};

    Method askMethod() {
        cout << "Calculate final grade by (a) average or (m) median? ";
        char c;
        cin >> c;
        return (c == 'm' || c == 'M') ? Method::Median : Method::Average;
    }

    void printOneMethod(const StudentGroup &group, Method m) {
        cout << "\nMethod: " << (m == Method::Average ? "average" : "median") << "\n";
        Student::printHeader(m);
        for (const Student &s : group.all()) {
            try {
                s.print(m);
            } catch (const std::domain_error &e) {
                cout << "  [skipped] " << e.what() << "\n";
            }
        }
        cout << endl;
    }

    void printBoth(const StudentGroup &group) {
        cout << endl;
        Student::printHeaderBoth();
        for (const Student &s : group.all()) {
            try {
                cout << s << "\n";
            } catch (const std::domain_error &e) {
                cout << "  [skipped] " << e.what() << "\n";
            }
        }
        cout << endl;
    }

    void manualInput(StudentGroup &group) {
        while (true) {
            cout << "Add a student? y/n ";
            char answ;
            cin >> answ;
            if (answ == 'n' || answ == 'N') break;
            Student s;
            s.input();
            group.add(std::move(s));
        }
        if (group.empty()) return;
        printOneMethod(group, askMethod());
    }

    void randomInput(StudentGroup &group) {
        static const vector<string> names    = {"Francisco", "Ignacio", "Noe", "Pablo", "Jorge", "Tomas", "Javier", "Lucas", "Pedro"};
        static const vector<string> surnames = {"Diaz", "Garcia", "Fernandez", "Moro", "Perez", "Herrero", "Gomez"};
        int n;
        cout << "How many students to generate? ";
        if (!(cin >> n) || n <= 0) { cin.clear(); cin.ignore(10000, '\n'); return; }

        RandInt pickN{0, static_cast<int>(names.size()) - 1};
        RandInt pickS{0, static_cast<int>(surnames.size()) - 1};
        RandInt hwCount{3, 10}, score{Student::MIN_SCORE, Student::MAX_SCORE};
        for (int i = 0; i < n; ++i) {
            Student s;
            s.randomize(names[static_cast<size_t>(pickN())], surnames[static_cast<size_t>(pickS())], hwCount, score);
            group.add(std::move(s));
        }
        printOneMethod(group, askMethod());
    }

    void fileInput(StudentGroup &group) {
        string fName;
        cout << "Name file: ";
        cin >> fName;

        size_t skipped = group.load("files/" + fName);
        if (skipped) cout << "Warning: skipped " << skipped << " invalid line(s)\n";
        printBoth(group);
    }

    void generateFiles() {
        DataGenerator gen;
        for (size_t n : SIZES) {
            Timer t;
            gen.generateFile(DataGenerator::studentsPath(n), n);
            cout << "Generated " << DataGenerator::studentsPath(n)
                 << " (" << std::fixed << std::setprecision(2) << t.elapsed() << " s)" << endl;
        }
    }

    void runSpeedTest() {
        SpeedTest(Method::Average).runAll(SIZES);
    }
}

int main() {
    StudentGroup group;
    cout << "1 - enter students manually\n"
         << "2 - generate students randomly\n"
         << "3 - read students from a file\n"
         << "4 - generate data files (1 000 ... 10 000 000 records)\n"
         << "5 - speed analysis: read, sort, split failed/passed, write two files\n"
         << "Choice: ";
    int choice;
    if (!(cin >> choice)) {
        cout << "Invalid choice\n";
        return 1;
    }

    try {
        switch (choice) {
            case 1: manualInput(group); break;
            case 2: randomInput(group); break;
            case 3: fileInput(group);   break;
            case 4: generateFiles();    break;
            case 5: runSpeedTest();     break;
            default: cout << "Unknown choice\n";
        }
    } catch (...) {
        processException();
        return 1;
    }
    return 0;
}
