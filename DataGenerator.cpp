#include "DataGenerator.h"
#include "Student.h"

DataGenerator::DataGenerator(int hwPerStudent)
    : score{Student::MIN_SCORE, Student::MAX_SCORE}, hwCount(hwPerStudent) {
    if (hwPerStudent < 1) throw std::invalid_argument("hwCount must be at least 1");
}

string DataGenerator::studentsPath(size_t count, const string &dir) {
    return dir + "/students" + std::to_string(count) + ".txt";
}

void DataGenerator::generateFile(const string &path, size_t count) {
    std::filesystem::path p(path);
    if (p.has_parent_path()) std::filesystem::create_directories(p.parent_path());

    std::ofstream out(path);
    if (!out) throw std::ios_base::failure("Cannot open file for writing: " + path);

    out << left << setw(16) << "Name" << setw(16) << "Surname" << right;
    for (int i = 1; i <= hwCount; ++i) out << setw(5) << ("HW" + std::to_string(i));
    out << setw(6) << "Exam" << '\n';

    for (size_t i = 1; i <= count; ++i) {
        out << left << setw(16) << ("Name" + std::to_string(i))
            << setw(16) << ("Surname" + std::to_string(i)) << right;
        for (int k = 0; k < hwCount; ++k) out << setw(5) << score();
        out << setw(6) << score() << '\n';
    }
    out.flush();
    if (!out) throw std::ios_base::failure("Write failed: " + path);
}
