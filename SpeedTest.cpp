#include "SpeedTest.h"
#include "StudentGroup.h"
#include "DataGenerator.h"
#include "Timer.h"

SpeedTestResult SpeedTest::runOne(size_t records) const {
    SpeedTestResult r;
    r.records = records;
    const string tag = std::to_string(records);

    Timer total, t;
    StudentGroup group;
    group.load(DataGenerator::studentsPath(records, dir));
    r.read = t.elapsed();

    t.reset();
    group.sortByFinal(method);
    r.sort = t.elapsed();

    t.reset();
    StudentGroup failed = group.extractFailed(method);
    r.split = t.elapsed();

    t.reset();
    failed.save(dir + "/failed_" + tag + ".txt");
    group.save(dir + "/passed_" + tag + ".txt");
    r.write = t.elapsed();

    r.total = total.elapsed();
    r.failed = failed.size();
    r.passed = group.size();
    return r;
}

void SpeedTest::runAll(const vector<size_t> &sizes) const {
    cout << right << setw(10) << "Records" << setw(10) << "Read" << setw(10) << "Sort"
         << setw(10) << "Split" << setw(10) << "Write" << setw(10) << "TOTAL"
         << setw(10) << "Failed" << setw(10) << "Passed" << "\n"
         << string(80, '-') << "\n";

    for (size_t n : sizes) {
        try {
            SpeedTestResult r = runOne(n);
            cout << std::fixed << std::setprecision(3) << setw(10) << r.records
                 << setw(10) << r.read << setw(10) << r.sort << setw(10) << r.split
                 << setw(10) << r.write << setw(10) << r.total
                 << setw(10) << r.failed << setw(10) << r.passed << endl;
        } catch (const std::exception &e) {
            cout << setw(10) << n << "  skipped: " << e.what() << endl;
        }
    }
    cout << endl;
}
