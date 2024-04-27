# RouteRover - A Bus Management System
This repository contains a Bus Management System implemented in C++

---

## Description

The Bus Management System allows administrators to manage bus details, including adding new buses and deleting existing ones. Customers can view available buses, search for specific routes, book tickets, and manage their bookings.

## Features

- **Admin Module**: Add and delete bus details with password authentication.
- **Customer Module**: View available buses, search for routes, and book tickets.
- **Data Persistence**: Store bus details, seat information, and customer bookings in text files.
- **Seat Reservation**: Customers can reserve seats, and the system tracks seat availability.
- **Booking Records**: Customers can view their booking records.

## Code Structure

- **`main.cpp`**: Contains the main program logic, including the `main` function and the `Bus` class definition.
- **Data Files**:
  - `bus.txt`: Stores bus details (Bus Number, Total Seats, From, To, Via).
  - `seat.txt`: Stores seat information (Bus Number, Seat Number).
  - `customer.txt`: Stores customer booking records (First Name, Last Name, Bus Number, Seat Number, Aadhar Number).
- **Class `Bus`**: Implements the core functionalities of the system, including admin and customer menus, adding/deleting buses, booking tickets, etc.

## How to Use

1. **Compile**: Compile the program using a C++ compiler.
   ```bash
   g++ main.cpp -o bus_management_system
   ```
2. **Run**: Execute the compiled program.
   ```bash
   ./bus_management_system
   ```
3. **Usage**:
   - Upon running the program, choose between the admin and customer modules.
   - For admin access, enter the password when prompted (default: `admin`).
   - Follow on-screen instructions to perform various actions.

## Future Scope

❖ Software can be modified with the help of web dev. /app development.
❖ Provide SMS based alerts and email notifications for bookings.
❖ A wallet can be developed to handle payments.
❖ Chat feature can be included in the application to chat with customer care.
❖ Allow the customer to save favourite routes.

---
