#include <iostream>
#include <vector>
#include "models/Booking.h"
#include "services/FileManager.h"
#include "services/StudentService.h"
#include "services/AdminService.h"
#include "services/BookingService.h"
using namespace std;
int main() {
    while (true) {
        cout << "\n\033[1;36m--- IITG Room Booking System ---\033[0m\n1. Student Login/Register\n2. Admin Login\n3. Exit\n\033[1;33mChoice: \033[0m";
        int ch; cin >> ch;
        if (ch == 1) {
            cout << "\033[1;36m1. Register\n2. Login\n\033[1;33mChoice: \033[0m"; int op; cin >> op;
            string roll;
            if (op == 1) StudentService::registerStudent();
            else if (op == 2 && StudentService::loginStudent(roll)) BookingService::studentPanel(roll);
            else cout << "\033[1;31mLogin failed.\033[0m\n";
        } else if (ch == 2) {
            if (AdminService::loginAdmin()) AdminService::panel();
            else cout << "\033[1;31mAccess Denied\033[0m\n";
        } else if (ch == 3) break;
        else cout << "\033[1;31mInvalid Choice.\033[0m\n";
    }
    return 0;
}
