#ifndef STUDENT_SERVICE_H
#define STUDENT_SERVICE_H
#include "../models/Student.h"
#include <fstream>
#include <sstream>
class StudentService {
public:
    static bool registerStudent() {
        Student s;
        cout << "\033[1;36mEnter Roll Number: \033[0m"; cin >> s.rollNumber;
        cin.ignore();
        cout << "\033[1;36mEnter Name: \033[0m"; getline(cin, s.name);
        cout << "\033[1;36mEnter Email: \033[0m"; getline(cin, s.email);
        cout << "\033[1;36mEnter Password: \033[0m"; cin >> s.password;
        ofstream fout("data/students.txt", ios::app);
        fout << s.rollNumber << ' ' << s.name << ' ' << s.email << ' ' << s.password << '\n';
        cout << "\033[1;32m✔ Registration Successful.\033[0m\n";
        return true;
    }

    static bool loginStudent(string& rollNumber) {
        string id, pass;
        cout << "\033[1;36mEnter Roll Number: \033[0m"; cin >> id;
        cout << "\033[1;36mEnter Password: \033[0m"; cin >> pass;
        ifstream fin("data/students.txt");
        string line;
        while (getline(fin, line)) {
            istringstream iss(line);
            string r, n, e, p;
            iss >> r >> n >> e >> p;
            if (r == id && p == pass) {
                rollNumber = r;
                return true;
            }
        }
        return false;
    }

    static void viewStudentBookings(const string& rollNumber) {
        vector<Booking> all = FileManager::loadBookings();
        int idx = 1;
        bool found = false;
        for (const auto& b : all) {
            if (b.rollNumber == rollNumber) {
                string statusColor = (b.status == "Approved") ? "\033[1;32m" : "\033[1;33m";
                cout << idx++ << ". Room: " << b.roomName << ", Date: " << b.date << ", Time: " << b.time << ", Status: " << statusColor << b.status << "\033[0m\nReason: " << b.reason << "\n";
                found = true;
            }
        }
        if (!found) cout << "\033[1;31mNo bookings found.\033[0m\n";
    }
};
#endif
