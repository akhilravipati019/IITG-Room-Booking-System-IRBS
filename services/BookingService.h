#ifndef BOOKING_SERVICE_H
#define BOOKING_SERVICE_H
#include "FileManager.h"
#include "../utils/Utility.h"
#include <iostream>
class BookingService {
public:
    static void studentPanel(const string& rollNumber) {
        while (true) {
            cout << "\n1. Book Room\n2. Cancel Booking\n3. View Booking Status\n4. Exit\nChoice: ";
            int ch; cin >> ch;
            if (ch == 1) bookRoom(rollNumber);
            else if (ch == 2) cancelBooking(rollNumber);
            else if (ch == 3) viewBookings(rollNumber);
            else break;
        }
    }

private:
    static void bookRoom(const string& rollNumber) {
        vector<Room> rooms = FileManager::loadRooms();
        cout << "\nSelect Room Category:\n1. Club\n2. Common\n3. Board\n4. Others\n5. Back\nChoice: ";
        int cat; cin >> cat;
        string type;
        if (cat == 1) type = "Club";
        else if (cat == 2) type = "Common";
        else if (cat == 3) type = "Board";
        else if (cat == 4) type = "Others";
        else return;

        vector<Room> filtered;
        for (auto& r : rooms) if (r.category == type) filtered.push_back(r);
        if (filtered.empty()) { cout << "No rooms available.\n"; return; }

        for (size_t i = 0; i < filtered.size(); ++i)
            cout << i+1 << ". " << filtered[i].name << endl;

        cout << "Choose room number: ";
        int choice; cin >> choice;
        if (choice < 1 || choice > filtered.size()) return;

        string date, startTime, endTime;
        cout << "Enter date (DD-MM-YYYY): "; cin >> date;
        do {
            cout << "Enter start time (HH:MM): "; cin >> startTime;
        } while (!Utility::isValidTimeFormat(startTime));
        do {
            cout << "Enter end time (HH:MM): "; cin >> endTime;
        } while (!Utility::isValidTimeFormat(endTime));

        string bookingTime = startTime + " to " + endTime;
        vector<Booking> all = FileManager::loadBookings();
        for (auto& b : all) {
            if (b.status == "Approved" && b.roomName == filtered[choice - 1].name && b.date == date && Utility::isTimeConflict(b.time, bookingTime)) {
                cout << "Time conflict.\n"; return;
            }
        }
        Booking b;
        b.rollNumber = rollNumber;
        b.roomName = filtered[choice - 1].name;
        b.category = filtered[choice - 1].category;
        b.date = date;
        b.time = bookingTime;
        cin.ignore();
        cout << "Enter reason: "; getline(cin, b.reason);
        b.status = "Pending";
        all.push_back(b);
        FileManager::saveBookings(all);
        cout << "Booking sent for approval.\n";
    }

    static void cancelBooking(const string& rollNumber) {
        vector<Booking> all = FileManager::loadBookings();
        vector<int> indices;
        for (size_t i = 0, j = 1; i < all.size(); ++i) {
            if (all[i].rollNumber == rollNumber) {
                cout << j++ << ". Room: " << all[i].roomName << ", Date: " << all[i].date << ", Time: " << all[i].time << ", Status: " << all[i].status << "\n";
                indices.push_back(i);
            }
        }
        if (indices.empty()) { cout << "No bookings to cancel.\n"; return; }
        cout << "Enter number to cancel (0 to go back): ";
        int ch; cin >> ch;
        if (ch > 0 && ch <= indices.size()) {
            all.erase(all.begin() + indices[ch - 1]);
            FileManager::saveBookings(all);
            cout << "Cancelled.\n";
        }
    }

    static void viewBookings(const string& rollNumber) {
        vector<Booking> all = FileManager::loadBookings();
        int idx = 1;
        for (const auto& b : all) {
            if (b.rollNumber == rollNumber) {
                cout << idx++ << ". Room: " << b.roomName << ", Date: " << b.date << ", Time: " << b.time << ", Status: " << b.status << ", Reason: " << b.reason << "\n";
            }
        }
        if (idx == 1) cout << "No bookings found.\n";
    }
};
#endif