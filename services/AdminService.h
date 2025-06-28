#ifndef ADMIN_SERVICE_H
#define ADMIN_SERVICE_H
#include "FileManager.h"
#include <iostream>
class AdminService {
public:
    static bool loginAdmin() {
        string user, pass;
        cout << "\033[1;35mEnter Admin Username: \033[0m"; cin >> user;
        cout << "\033[1;35mEnter Admin Password: \033[0m"; cin >> pass;
        return user == "admin" && pass == "admin123";
    }

    static void panel() {
        while (true) {
            vector<Booking> all = FileManager::loadBookings();
            cout << "\n\033[1;35mAdmin Panel\033[0m\n1. View All Bookings\n2. Approve Booking\n3. Cancel Booking\n4. Back\n\033[1;33mChoice: \033[0m";
            int ch; cin >> ch;
            if (ch == 1) {
                int idx = 1;
                for (const auto& b : all) {
                    cout << "\033[1;36m" << idx++ << ". Roll: " << b.rollNumber << ", Room: " << b.roomName << ", Date: " << b.date << ", Time: " << b.time << ", Status: " << b.status << "\033[0m\n";
                }
            } else if (ch == 2 || ch == 3) {
                int idx = 1;
                for (const auto& b : all) {
                    cout << "\033[1;36m" << idx++ << ". Roll: " << b.rollNumber << ", Room: " << b.roomName << ", Date: " << b.date << ", Time: " << b.time << ", Status: " << b.status << "\033[0m\n";
                }
                cout << "\033[1;33mEnter booking number to update: \033[0m";
                int num; cin >> num;
                if (num >= 1 && num <= all.size()) {
                    if (ch == 2) all[num - 1].status = "Approved";
                    else all.erase(all.begin() + num - 1);
                    FileManager::saveBookings(all);
                    cout << ((ch == 2) ? "\033[1;32m✔ Approved.\033[0m\n" : "\033[1;31m✖ Cancelled.\033[0m\n");
                }
            } else if (ch == 4) return;
            else cout << "\033[1;31mInvalid\033[0m\n";
        }
    }
};
#endif