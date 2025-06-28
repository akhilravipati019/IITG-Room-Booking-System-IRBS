# IITG Room Booking System

A terminal-based room booking system built using C++ with Object-Oriented Programming and file handling. It supports separate interfaces for students and administrators to manage, approve, and cancel room bookings on campus.

---

## Features

### Student Panel
- Register with roll number, name, email, and password.
- Login with roll number and password.
- Book a room by selecting:
  - Room category (Club, Common, Board, Others)
  - Specific room
  - Booking by date and time
  - Reason for booking
- Cancel your own bookings.
- View all your bookings with status.

### Admin Panel
- Login with admin credentials (`admin/admin123`).
- View all student booking requests.
- Approve selected bookings.
- Disapprove selected bookings.

### Other Highlights
- Modular codebase using models, services, and utilities.
- All data stored persistently in `.txt` files under the `data/` directory.
- Input validation for date/time format and time slot conflicts.

---
