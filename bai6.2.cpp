#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;

// Structure to hold student information
struct Student {
    string name;           // Student name
    float mathScore;       // Math score
    float literatureScore; // Literature score
    float englishScore;    // English score
    float averageScore;    // Average score
    string classification; // Classification
};

// Function to validate student name
// Input: student name as a string
// Output: true if valid, false otherwise
bool isValidName(const string &name) {
    for (char c : name) {
        if (isdigit(c)) return false; // No digits allowed
    }
    return name.length() > 0 && name.length() <= 50; // Length check
}

// Function to validate scores
// Input: score as a float
// Output: true if valid (0 to 10), false otherwise
bool isValidScore(float score) {
    return score >= 0 && score <= 10;
}

// Function to classify student based on average score
// Input: average score as a float
// Output: classification as a string
string classifyStudent(float average) {
    if (average >= 9) return "Xuất sắc";
    if (average >= 8) return "Giỏi";
    if (average >= 6.5) return "Khá";
    if (average >= 5) return "Trung bình";
    return "Yếu";
}

// Function to input student information
// Input: none
// Output: returns a Student object with validated data
Student inputStudent() {
    Student student;
    do {
        cout << "Enter student's name: ";
        getline(cin, student.name);
        if (!isValidName(student.name)) {
            cout << "Invalid name. Please try again." << endl;
        }
    } while (!isValidName(student.name));

    // Input Math score
    do {
        cout << "Enter Math score (0-10): ";
        cin >> student.mathScore;
        if (!isValidScore(student.mathScore)) {
            cout << "Invalid score. Please enter a number between 0 and 10." << endl;
        }
    } while (!isValidScore(student.mathScore));

    // Input Literature score
    do {
        cout << "Enter Literature score (0-10): ";
        cin >> student.literatureScore;
        if (!isValidScore(student.literatureScore)) {
            cout << "Invalid score. Please enter a number between 0 and 10." << endl;
        }
    } while (!isValidScore(student.literatureScore));

    // Input English score
    do {
        cout << "Enter English score (0-10): ";
        cin >> student.englishScore;
        if (!isValidScore(student.englishScore)) {
            cout << "Invalid score. Please enter a number between 0 and 10." << endl;
        }
    } while (!isValidScore(student.englishScore));

    // Calculate average score
    student.averageScore = (2 * student.mathScore + student.literatureScore + student.englishScore) / 4;
    student.classification = classifyStudent(student.averageScore);

    return student;
}

// Function to find the student with the highest average score
// Input: vector of Student objects
// Output: Student object with the highest average score
Student findTopStudent(const vector<Student> &students) {
    return *max_element(students.begin(), students.end(), [](const Student &a, const Student &b) {
        return a.averageScore < b.averageScore;
    });
}

// Function to search for students by name
// Input: vector of Student objects and a search query
// Output: prints matching students to console
void searchStudentsByName(const vector<Student> &students, const string &query) {
    bool found = false;
    for (const Student &student : students) {
        if (student.name.find(query) != string::npos) {
            cout << "Found: " << student.name << ", Average Score: " << fixed << setprecision(2) << student.averageScore 
                 << ", Classification: " << student.classification << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No students found matching the query: " << query << endl;
    }
}

// Function to find students with the lowest math score
// Input: vector of Student objects
// Output: prints students with the lowest math score
void findLowestMathScoreStudents(const vector<Student> &students) {
    float lowestScore = numeric_limits<float>::max();
    for (const Student &student : students) {
        if (student.mathScore < lowestScore) {
            lowestScore = student.mathScore;
        }
    }

    cout << "Students with the lowest Math score (" << lowestScore << "):" << endl;
    for (const Student &student : students) {
        if (student.mathScore == lowestScore) {
            cout << student.name << endl;
        }
    }
}

// Main function to run the student management program
int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;
    cin.ignore(); // Ignore leftover newline character

    vector<Student> students(n);

    // Input student information
    for (int i = 0; i < n; ++i) {
        cout << "Enter details for student " << (i + 1) << ":\n";
        students[i] = inputStudent();
    }

    // Output average scores and classifications
    cout << "\nAverage scores and classifications:\n";
    for (const Student &student : students) {
        cout << student.name << ": Average Score = " << fixed << setprecision(2) << student.averageScore
             << ", Classification = " << student.classification << endl;
    }

    // Find and output the student with the highest average score
    Student topStudent = findTopStudent(students);
    cout << "\nStudent with the highest average score: " << topStudent.name
         << " with an average score of " << fixed << setprecision(2) << topStudent.averageScore << endl;

    // Search for students by name
    string searchQuery;
    cout << "\nEnter a name to search for: ";
    getline(cin, searchQuery);
    searchStudentsByName(students, searchQuery);

    // Find students with the lowest math score
    findLowestMathScoreStudents(students);

    return 0;
}
