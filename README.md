# 🚌 Bus Reservation System in C

A console-based **Bus Reservation System** developed using the C programming language. This project allows users to add buses, reserve seats, cancel reservations, and view passenger information.

The project uses **structures** and **file handling** to store bus and passenger data permanently.

## Features

- Add new buses
- Prevent duplicate bus numbers
- Display all available buses
- Reserve seats for passengers
- Validate bus and seat numbers
- Prevent double booking of seats
- Cancel existing reservations
- Display passenger lists for a specific bus
- Store bus and booking information using binary files
- Preserve data after the program is closed

## Concepts Used

This project demonstrates several fundamental C programming concepts:

- Structures (`struct`)
- Functions
- File Handling
- Binary File Operations
- `fread()` and `fwrite()`
- Strings and String Functions
- Loops
- Conditional Statements
- Input Validation

## Project Structure

```text
Bus-Reservation-System-C/
│
├── main.c
├── README.md
└── .gitignore
```

The program automatically creates the following data files when required:

```text
buses.dat
bookings.dat
temp.dat
```

## How It Works

When the program starts, the following menu is displayed:

```text
========== BUS TICKET BOOKING SYSTEM ==========
1. Add New Bus
2. Show All Buses
3. Reserve Seat
4. Cancel Reservation
5. Show Passenger List
6. Exit
```

### 1. Add New Bus

Allows the user to add a new bus with information such as:

- Bus number
- Driver name
- Source
- Destination
- Total number of seats
- Fare per seat

Duplicate bus numbers are not allowed.

### 2. Show All Buses

Displays information about all buses stored in the system.

### 3. Reserve Seat

Allows a passenger to reserve a seat on a selected bus.

The system checks whether:

- The bus exists
- The seat number is valid
- The seat is already booked

If an invalid bus or seat number is entered, the user can try again.

### 4. Cancel Reservation

Allows an existing reservation to be cancelled using the bus number and seat number.

### 5. Show Passenger List

Displays the passenger list for a selected bus, including:

- Passenger name
- Phone number
- Seat number

## Data Storage

The project uses binary files for permanent data storage.

```text
buses.dat
```

Stores bus information.

```text
bookings.dat
```

Stores passenger booking information.

The program uses `fwrite()` to save structures into files and `fread()` to retrieve them.

## Compile and Run

Using GCC:

```bash
gcc main.c -o bus_reservation
```

Run on Linux/macOS:

```bash
./bus_reservation
```

Run on Windows:

```bash
bus_reservation.exe
```

## .gitignore

The generated data files can be excluded from GitHub by adding the following to `.gitignore`:

```gitignore
*.dat
```

## Future Improvements

Possible improvements include:

- Display available and booked seats visually
- Search buses by source and destination
- Update bus information
- Delete buses
- Search passenger reservations
- Generate booking IDs
- Add departure date and time
- Calculate total revenue
- Improve input validation
- Add an admin login system

## Author

**Nitun Krishna Biswas**

GitHub: `nitunkrishna`

## License

This project is created for educational purposes. Future updates may be possible.
