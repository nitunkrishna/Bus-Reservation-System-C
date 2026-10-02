#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 50

struct Bus
{
    char bus_no[11];
    char driver[30];
    char source[30];
    char destination[30];
    int total_seats;
    int fare;
};

struct Passenger
{
    char name[30];
    char phone[15];
    int seat_no;
    char bus_no[11];
};

void addBus();
int busAlreadyExists(char *bus_no);
void showBuses();
void reserveSeat();
void cancelSeat();
void showPassengers();
int seatAlreadyBooked(char *bus_no, int seat_no);
void saveBooking(struct Passenger p);
void deleteBooking(char *bus_no, int seat_no);

int main()
{
    int choice;
    while (1)
    {
        printf("\n========== BUS TICKET BOOKING SYSTEM ==========\n");
        printf("1. Add New Bus\n");
        printf("2. Show All Buses\n");
        printf("3. Reserve Seat\n");
        printf("4. Cancel Reservation\n");
        printf("5. Show Passenger List\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // remove newline

        switch (choice)
        {
        case 1:
            addBus();
            break;
        case 2:
            showBuses();
            break;
        case 3:
            reserveSeat();
            break;
        case 4:
            cancelSeat();
            break;
        case 5:
            showPassengers();
            break;
        case 6:
            printf("Thank you for using the system!\n");
            exit(0);
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

void addBus()
{
    struct Bus b;
    FILE *fp = fopen("buses.dat", "ab");
    if (!fp)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Bus Number: ");
    scanf("%10s", b.bus_no);

    if (busAlreadyExists(b.bus_no))
    {
        printf("Bus number already exists!\n");
        fclose(fp);
        return;
    }
    printf("Enter Driver Name: ");
    scanf(" %[^\n]", b.driver);
    printf("Enter Source: ");
    scanf(" %[^\n]", b.source);
    printf("Enter Destination: ");
    scanf(" %[^\n]", b.destination);
    do
    {
        printf("Enter Total Seats (1-%d): ", MAX_SEATS);
        scanf("%d", &b.total_seats);
        if (b.total_seats < 1 || b.total_seats > MAX_SEATS)
            printf("Invalid number of seats! Try again.\n");
    } while (b.total_seats < 1 || b.total_seats > MAX_SEATS);
    printf("Enter Fare per Seat: ");
    scanf("%d", &b.fare);
    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
    printf("Bus added successfully!\n");
}

int busAlreadyExists(char *bus_no)
{
    struct Bus b;
    FILE *fp = fopen("buses.dat", "rb");

    if (!fp)
        return 0;

    while (fread(&b, sizeof(b), 1, fp))
    {
        if (strcmp(b.bus_no, bus_no) == 0)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void showBuses()
{
    struct Bus b;
    FILE *fp = fopen("buses.dat", "rb");
    if (!fp)
    {
        printf("No bus data found!\n");
        return;
    }

    printf("\n%-10s %-15s %-10s %-10s %-10s %-10s\n",
           "Bus No", "Driver", "Source", "Dest", "Seats", "Fare");
    printf("-------------------------------------------------------------\n");

    while (fread(&b, sizeof(b), 1, fp))
        printf("%-10s %-15s %-10s %-10s %-10d %-10d\n",
               b.bus_no, b.driver, b.source, b.destination, b.total_seats, b.fare);

    fclose(fp);
}

void reserveSeat()
{
    struct Passenger p;
    struct Bus b;
    char busNo[11];
    int seat;
    int found;

    do
    {
        found = 0;

        FILE *fp = fopen("buses.dat", "rb");
        if (!fp)
        {
            printf("No bus available!\n");
            return;
        }

        printf("Enter Bus Number: ");
        scanf("%10s", busNo);

        while (fread(&b, sizeof(b), 1, fp))
        {
            if (strcmp(b.bus_no, busNo) == 0)
            {
                found = 1;
                break;
            }
        }
        fclose(fp);

        if (!found)
            printf("Invalid Bus! Try again.\n");

    } while (!found);

    do
    {
        printf("Enter Seat Number (1-%d): ", b.total_seats);
        scanf("%d", &seat);

        if (seat < 1 || seat > b.total_seats)
            printf("Invalid Seat! Try again.\n");
        else if (seatAlreadyBooked(busNo, seat))
            printf("Sorry, this seat is already booked! Try another seat.\n");

    } while (seat < 1 || seat > b.total_seats || seatAlreadyBooked(busNo, seat));

    printf("Enter Passenger Name: ");
    scanf(" %[^\n]", p.name);

    printf("Enter Phone Number: ");
    scanf("%14s", p.phone);

    strcpy(p.bus_no, busNo);
    p.seat_no = seat;

    saveBooking(p);

    printf("Seat booked successfully! Fare: %d Taka\n", b.fare);
}

void cancelSeat()
{
    char busNo[11];
    int seat;
    printf("Enter Bus Number: ");
    scanf("%10s", busNo);
    printf("Enter Seat Number: ");
    scanf("%d", &seat);

    if (!seatAlreadyBooked(busNo, seat))
    {
        printf("No such booking found!\n");
        return;
    }

    deleteBooking(busNo, seat);
    printf("Reservation cancelled successfully!\n");
}

void showPassengers()
{
    struct Passenger p;
    char busNo[11];
    int found = 0;
    printf("Enter Bus Number: ");
    scanf("%10s", busNo);

    FILE *fp = fopen("bookings.dat", "rb");
    if (!fp)
    {
        printf("No booking data found!\n");
        return;
    }

    printf("\nPassenger List for Bus %s:\n", busNo);
    printf("---------------------------------------------\n");
    printf("%-15s %-10s %-10s\n", "Name", "Phone", "Seat No");
    while (fread(&p, sizeof(p), 1, fp))
    {
        if (strcmp(p.bus_no, busNo) == 0)
        {
            printf("%-15s %-10s %-10d\n", p.name, p.phone, p.seat_no);
            found = 1;
        }
    }
    if (!found)
        printf("No passengers found for this bus.\n");

    fclose(fp);
}

int seatAlreadyBooked(char *bus_no, int seat_no)
{
    struct Passenger p;
    FILE *fp = fopen("bookings.dat", "rb");
    if (!fp)
        return 0;

    while (fread(&p, sizeof(p), 1, fp))
    {
        if (strcmp(p.bus_no, bus_no) == 0 && p.seat_no == seat_no)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void saveBooking(struct Passenger p)
{
    FILE *fp = fopen("bookings.dat", "ab");
    if (!fp)
    {
        printf("Error opening booking file!\n");
        return;
    }
    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);
}

void deleteBooking(char *bus_no, int seat_no)
{
    struct Passenger p;
    FILE *fp = fopen("bookings.dat", "rb");
    if (!fp)
    {
        printf("Booking file not found!\n");
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");
    if (!temp)
    {
        printf("Error creating temporary file!\n");
        fclose(fp);
        return;
    }

    while (fread(&p, sizeof(p), 1, fp))
    {
        if (!(strcmp(p.bus_no, bus_no) == 0 && p.seat_no == seat_no))
            fwrite(&p, sizeof(p), 1, temp);
    }

    fclose(fp);
    fclose(temp);
    remove("bookings.dat");
    rename("temp.dat", "bookings.dat");
}