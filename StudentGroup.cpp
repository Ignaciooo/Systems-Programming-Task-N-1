#include "StudentGroup.h"

size_t StudentGroup::load(const string &path) {
    std::ifstream file(path);
    if (!file) throw std::ios_base::failure("Cannot open file for reading: " + path);

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    string header;
    std::getline(buffer, header);

    size_t skipped = 0;
    while (true) {
        Student s;
        if (buffer >> s) {
            students.push_back(std::move(s));
        } else if (buffer.eof()) {
            break;
        } else {
            buffer.clear();
            ++skipped;
        }
    }
    return skipped;
}

void StudentGroup::save(const string &path) const {
    std::ofstream out(path);
    if (!out) throw std::ios_base::failure("Cannot open file for writing: " + path);

    std::ostringstream buffer;
    Student::printHeaderBothTo(buffer);
    for (const Student &s : students) buffer << s << '\n';
    out << buffer.str();
    out.flush();
    if (!out) throw std::ios_base::failure("Write failed: " + path);
}

void StudentGroup::sortByFinal(Method m) {
    students.sort([m](const Student &a, const Student &b) {
        return a.finalGrade(m) < b.finalGrade(m);
    });
}

StudentGroup StudentGroup::extractFailed(Method m) {
    auto firstPassed = std::partition_point(students.begin(), students.end(),
        [m](const Student &s) { return s.finalGrade(m) < PASS_MARK; });

    StudentGroup failed;
    failed.students.assign(std::make_move_iterator(students.begin()),
                           std::make_move_iterator(firstPassed));
    students.erase(students.begin(), firstPassed);
    return failed;
}
