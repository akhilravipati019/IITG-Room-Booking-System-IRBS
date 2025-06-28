#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H
#include "../models/Room.h"
#include "../models/Booking.h"
#include <vector>
#include <fstream>
class FileManager {
public:
    static vector<Room> loadRooms() {
        vector<Room> rooms;
        ifstream fin("data/rooms.txt");
        Room r;
        while (fin >> ws && getline(fin, r.name) && getline(fin, r.category)) {
            rooms.push_back(r);
        }
        return rooms;
    }

    static vector<Booking> loadBookings() {
        vector<Booking> bookings;
        Booking b;
        ifstream fin("data/bookings.txt");
        while (getline(fin, b.rollNumber) && getline(fin, b.roomName) && getline(fin, b.category) &&
               getline(fin, b.date) && getline(fin, b.time) && getline(fin, b.reason) && getline(fin, b.status)) {
            bookings.push_back(b);
        }
        return bookings;
    }

    static void saveBookings(const vector<Booking>& bookings) {
        ofstream fout("data/bookings.txt");
        for (const auto& b : bookings) {
            fout << b.rollNumber << '\n' << b.roomName << '\n' << b.category << '\n' << b.date << '\n' << b.time << '\n' << b.reason << '\n' << b.status << '\n';
        }
    }
};
#endif