#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>

using namespace std;

class Bus
{
private:
    string busNumber, from, to, via;
    int totalSeats;

public:
    void adminMenu();
    void customerMenu();
    void addNewBus();
    void singleBusView();
    void allBusView();
    void deleteBus();
    void ticketBooking();
    void seatDetails();
    void deleteSeat();
    void bookingRecord();
    bool authenticateAdmin();
};

void Bus::adminMenu()
{
    int choice;

    cout << "\nAdmin Menu";
    cout << "\n1. Add Bus Details";
    cout << "\n2. Delete Bus Details";
    cout << "\n3. Exit";
    cout << "\nEnter your Choice : ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        addNewBus();
        break;
    case 2:
        deleteBus();
        break;
    case 3:
        break;
    default:
        cout << "\nInvalid Choice. Try Again!\n";
        adminMenu();
    }
}

void Bus::addNewBus()
{
    string tempBusNumber, tempFrom, tempTo, tempVia;
    int tempTotalSeats;
    ifstream file("bus.txt");
    ofstream outfile("bus.txt", ios::app);

    cout << "\n Add New Bus\n";
    cout << "Bus Number: ";
    cin >> busNumber;
    while (busNumber.empty())
    {
        cout << "Please Enter A Valid Bus Number: ";
        cin >> busNumber;
    }
    cout << "Total Seats: ";
    cin >> totalSeats;
    while (cin.fail() || totalSeats <= 0)
    {
        cin.clear();
        cout << "Please Enter A Valid Positive Integer";
        cin >> totalSeats;
    }
    cout << "From: ";
    cin >> from;
    while (from.empty())
    {
        cout << "Please Enter A Valid Starting Location: ";
        cin >> from;
    }
    cout << "To: ";
    cin >> to;
    while (to.empty())
    {
        cout << "Please Enter A Valid Destination: ";
        cin >> to;
    }
    cout << "Via: ";
    cin >> via;
    while (via.empty())
    {
        cout << "Please Enter A Valid Intermediate location: ";
        cin >> via;
    }

    if (!file.is_open())
    {
        outfile << busNumber << " " << totalSeats << " " << from << " " << to << " " << via << "\n";
        cout << "\n Bus Added Successfully\n";
    }
    else
    {
        bool found = false;
        while (file >> tempBusNumber >> tempTotalSeats >> tempFrom >> tempTo >> tempVia)
        {
            if (busNumber == tempBusNumber)
            {
                found = true;
                break;
            }
        }
        file.close();
        if (!found)
        {
            outfile << busNumber << " " << totalSeats << " " << from << " " << to << " " << via << "\n";
            cout << "\nBus Added Successfully\n";
        }
        else
        {
            cout << "\nDuplicate Record Found\n";
            addNewBus();
        }
    }
    outfile.close();
    adminMenu();
}

void Bus::deleteBus()
{
    string tempBusNumber;
    int found = 0;
    ifstream file("bus.txt");
    ofstream temp("temp.txt");

    cout << "\nBus Deletion\n";
    if (!file)
    {
        cout << "\nFile opening error\n";
        return;
    }

    cout << "\nBus Number: ";
    cin >> tempBusNumber;
    while (tempBusNumber.empty())
    {
        cout << "Please Enter A Valid Bus Number: ";
        cin >> tempBusNumber;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        ss >> busNumber >> totalSeats >> from >> to >> via;
        if (tempBusNumber != busNumber)
        {
            temp << line << endl;
        }
        else
        {
            cout << "\nBus Record Deleted Succesfully\n";
            found++;
        }
    }

    file.close();
    temp.close();
    remove("bus.txt");
    rename("temp.txt", "bus.txt");

    if (found == 0)
    {
        cout << "\nPlease Enter Valid Bus Number...\n";
    }
    adminMenu();
}

void Bus::customerMenu()
{
    int choice;

    cout << "\nCustomer Main Menu\n";
    cout << "\n1.View All Bus Details";
    cout << "\n2.Search Bus";
    cout << "\n3.Book Ticket Now";
    cout << "\n4.Seat Record";
    cout << "\n5.Delete Booking Record";
    cout << "\n6.Search Booking Record";
    cout << "\n7.Exit";
    cout << "\nEnter Your Choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        allBusView();
        break;
    case 2:
        singleBusView();
        break;
    case 3:
        ticketBooking();
        break;
    case 4:
        seatDetails();
        break;
    case 5:
        deleteSeat();
        break;
    case 6:
        bookingRecord();
        break;
    case 7:
        cout << "\nThank You For Visiting\n";
        break;
    default:
        cout << "\nInvalid Choice. Try Again!\n";
        customerMenu();
    }
}

void Bus::allBusView()
{
    ifstream file("bus.txt");

    cout << "\nViewing All Buses\n";
    if (!file)
    {
        cout << "\nFile Opening Error\n";
        customerMenu();
        return;
    }

    while (file >> busNumber >> totalSeats >> from >> to >> via)
    {
        cout << "\nBus Number : " << busNumber << "\t Total Seats : " << totalSeats << "\tRoute : " << from << " To " << to << "\tVia : " << via << endl;
    }
    file.close();
    customerMenu();
}

void Bus::singleBusView()
{
    string tempFrom, tempTo;
    ifstream file("bus.txt");
    int found = 0;

    cout << "\nViewing Single Bus Details\n";
    if (!file)
    {
        cout << "\nFile Opening Error\n";
        customerMenu();
        return;
    }

    cout << "\nFrom : ";
    cin >> tempFrom;
    cout << "\nTo : ";
    cin >> tempTo;

    while (file >> busNumber >> totalSeats >> from >> to >> via)
    {
        if ((tempFrom == from && tempTo == to) || (tempFrom == to && tempTo == from))
        {
            cout << "\nBus Number : " << busNumber << "\tTotal Seats : " << totalSeats << "\tRoute : " << from << " To " <<

                to << "\tVia : " << via << endl;
            found++;
        }
    }

    file.close();
    if (found == 0)
    {
        cout << "\nSorry! No Bus Found On This Route\n";
    }
    customerMenu();
}

void Bus::seatDetails()
{
    ifstream busFile("bus.txt");
    ifstream seatFile("seat.txt");

    string tempNo, tempSeatNo, tempBusNo;
    int count = 0;

    cout << "\nGet Seat Records For Your Bus\n";
    if (!busFile || !seatFile)
    {
        cout << "\nFile Opening Error\n";
        customerMenu();
        return;
    }

    cout << "\nBus Number : ";
    cin >> tempNo;

    while (getline(seatFile, tempBusNo, ' ') && getline(seatFile, tempSeatNo))
    {
        if (tempNo == tempBusNo)
        {
            count++;
        }
    }
    seatFile.close();

    string line;
    int tempTotalSeats = 0;
    while (busFile >> busNumber >> totalSeats >> from >> to >> via)
    {
        if (tempNo == busNumber)
        {
            tempTotalSeats = totalSeats;
            break;
        }
    }
    busFile.close();

    cout << "\nSeat Availability Details";
    cout << "\nTotal : " << tempTotalSeats;
    cout << "\nReserved : " << count;
    cout << "\nEmpty : " << tempTotalSeats - count << endl;

    customerMenu();
}

void Bus::ticketBooking()
{
    ifstream busFile("bus.txt");
    ifstream seatFile("seat.txt");
    ofstream bookingFile("customer.txt", ios::app);

    string customerFirstName, customerLastName, tempBusNo, aadharNo, tempNo;
    int seats, count = 0, seatNo, choice, tempSSNo;

    cout << "\nTicket Booking Process\n";
    if (!busFile)
    {
        cout << "\nFile Opening Error\n";
        customerMenu();
        return;
    }

    cout << "\nBus Number: ";
    cin >> tempNo;

    while (busFile >> busNumber >> totalSeats >> from >> to >> via)
    {
        if (tempNo == busNumber)
        {
            seats = totalSeats;
            break;
        }
    }
    busFile.close();

    if (!seatFile)
    {
        cout << "\nFile Opening Error\n";
        customerMenu();
        return;
    }

    string line;
    while (getline(seatFile, line))
    {
        stringstream ss(line);
        ss >> tempBusNo >> tempSSNo;
        if (tempNo == tempBusNo)
        {
            count++;
        }
    }
    seatFile.close();

    if (seats - count == 0)
    {
        cout << "\nAll Seats Are Reserved\n";
        customerMenu();
        return;
    }

    do
    {
        cout << "Seat Number : ";
        cin >> seatNo;
        if (seatNo > seats || seatNo < 1)
        {
            cout << "\nPlese Enter Valid Seat Number";
            continue;
        }

        ifstream seatFile("seat.txt");
        bool seatAvailable = true;
        while (seatFile >> tempBusNo >> seatNo)
        {
            if (tempNo == tempBusNo && seatNo == tempSSNo)
            {
                seatAvailable = false;
                break;
            }
        }
        seatFile.close();

        if (!seatAvailable)
        {
            cout << "Sorry, This Seat Is Already Reserved";
            continue;
        }

        cout << "Seat Is Available!";
        cout << "\nCustomer First Name: ";
        cin >> customerFirstName;
        cout << "Customer Last Name: ";
        cin >> customerLastName;
        cout << "Aadhar Number (last 4 digit): ";
        cin >> aadharNo;

        bookingFile << customerFirstName << " " << customerLastName << " " << tempNo << " " << seatNo << " " << aadharNo << "\n";
        cout << "\nYour Seat Has Been Booked!";
        cout << "\nPlease Wait A Moment";
        cout << "\n ********************************************************";
        cout << "\n Your Booking Details";
        cout << "\n ********************************************************";
        cout << "\nName   : " << customerFirstName << " " << customerLastName;
        cout << "\nBus Number : " << tempNo;
        cout << "\nSeat ID: " << aadharNo << "@" << seatNo;
        cout << "\n  ********************************************************";
        cout << "\n  ********************************************************";
        cout << "\n\n Do you want To book another seat \nYes=1 or No=2 \n Enter your choice : ";
        cin >> choice;
    } while (choice == 1);

    bookingFile.close();
    customerMenu();
}

void Bus::deleteSeat()
{
    string tempNo, tempSeatNo, tempBusNo, tempSSNo, customerFirstName, customerLastName, aadharNo, aadharcardNo;
    int found = 0;

    cout << "\nSeat Deletion Process\n";
    cout << "\n\t\t\t ------- Booking Deletion -------";
    cout << "\n\n\n\t\t Aadhar No: ";
    cin >> aadharcardNo;
    cout << "\n\n\t\t Bus No: ";
    cin >> tempNo;
    cout << "\n\n\t\t Seat No: ";
    cin >> tempSeatNo;

    ifstream customerFile("customer.txt");
    ofstream tempCustomerFile("tempCustomer.txt");

    if (!customerFile)
    {
        cout << "\nFile Opening Error\n";
        customerMenu();
        return;
    }

    while (customerFile >> customerFirstName >> customerLastName >> tempBusNo >> tempSSNo >> aadharNo)
    {
        if (aadharcardNo == aadharNo && tempNo == tempBusNo && tempSeatNo == tempSSNo)
        {
            found++;
        }
        else
        {
            tempCustomerFile << customerFirstName << " " << customerLastName << " " << tempBusNo << " " << tempSSNo << " " << aadharNo << "\n";
        }
    }
    customerFile.close();
    tempCustomerFile.close();
    remove("customer.txt");
    rename("tempCustomer.txt", "customer.txt");

    ifstream seatFile("seat.txt");
    ofstream tempSeatFile("tempSeat.txt");

    if (!seatFile)
    {
        cout << "\nFile Opening Error\n";
        customerMenu();
        return;
    }

    while (seatFile >> tempBusNo >> tempSSNo)
    {
        if (tempNo == tempBusNo && tempSeatNo == tempSSNo)
        {
            found++;
        }
        else
        {
            tempSeatFile << tempBusNo << " " << tempSSNo << "\n";
        }
    }
    seatFile.close();
    tempSeatFile.close();
    remove("seat.txt");
    rename("tempSeat.txt", "seat.txt");

    if (found == 0)
    {
        cout << "\nInvalid Input. Try Again!\n";
    }

    customerMenu();
}

void Bus::bookingRecord()
{
    string customerFirstName

        ,
        customerLastName, tempBusNo, tempSSNo, aadharNo, aadharcardNo;
    int found = 0;

    cout << "\nBooking Record\n";

    ifstream customerFile("customer.txt");
    if (!customerFile)
    {
        cout << "\nFile Opening Error\n";
        customerMenu();
        return;
    }

    cout << "\nAadhar Number (last 4 digits): ";
    cin >> aadharcardNo;

    while (customerFile >> customerFirstName >> customerLastName >> tempBusNo >> tempSSNo >> aadharNo)
    {
        if (aadharcardNo == aadharNo)
        {
            cout << "\n\t\tName : " << customerFirstName << " " << customerLastName;
            cout << "\n\t\tBus Number : " << tempBusNo;
            cout << "\n\t\tSeat Number : " << tempSSNo;
            found++;
        }
    }

    if (found == 0)
    {
        cout << "\n\nNo Booking Found\n";
    }
    customerFile.close();

    customerMenu();
}

bool Bus::authenticateAdmin()
{
    string password;
    cout << "\nEnter Admin Password: ";
    cin >> password;
    return (password == "admin");
}

int main()
{
    Bus obj;
    int choice;
    cout << "Welcome" << endl;
    cout << "1. Admin\n2. Customer\nChoose Mode: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        if (obj.authenticateAdmin())
        {
            obj.adminMenu();
        }
        else
        {
            cout << "\nIncorrect Password. Try Again!\n";
        }
        break;
    case 2:
        obj.customerMenu();
        break;
    default:
        cout << "\nInvalid Choice. Now Exiting Program\n";
    }

    return 0;
}
