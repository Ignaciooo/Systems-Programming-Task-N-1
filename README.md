# Student Grade Calculation System

A C++ application designed to process, calculate, and manage student academic performance. The system calculates final grades based on homework assignments and exam results, utilizing object-oriented programming (OOP) principles, `std::vector` containers, and file I/O operations.

# Final Grade Calculation Formula

Final Points = 0.4 * HW + 0.6 * Exam

where `HW` is either the **average** or the **median** of the homework results (user's choice).

# Students.txt format

```
Name        Surname    HW1   HW2   HW3   HW4   HW5   Exam
Name1       Surname1     8     9    10     6    10      9
Name2       Surname2     7    10     8     5     4      6
```

# Sample Output Format

```
Name        Surname        Final (Avg.) | Final (Med.)
------------------------------------------------------
Ignacio     Morán             8.84 |         9.00
Noé         Peláez            6.32 |         6.40
```
