
#include <iostream>
#include <string>

using namespace std;

// Base class for Flight
class Flight {
protected:
    string flightNumber;
    string departureLocation;
    string arrivalLocation;
    string departureTime;
    string arrivalTime;
    int availableSeats;

public:
    Flight() : flightNumber(""), departureLocation(""), arrivalLocation(""), departureTime(""), arrivalTime(""), availableSeats(0) {}
    Flight(string flightNumber, string departureLocation, string arrivalLocation, string departureTime, string arrivalTime, int availableSeats)
        : flightNumber(flightNumber), departureLocation(departureLocation), arrivalLocation(arrivalLocation),
        departureTime(departureTime), arrivalTime(arrivalTime), availableSeats(availableSeats) {}

    virtual ~Flight() {}

    virtual string getFlightType() const = 0;
    virtual float calculateTicketPrice(int age) const = 0;

    string getFlightNumber() const { return flightNumber; }
    string getDepartureLocation() const { return departureLocation; }
    string getArrivalLocation() const { return arrivalLocation; }
    string getDepartureTime() const { return departureTime; }
    string getArrivalTime() const { return arrivalTime; }
    int getAvailableSeats() const { return availableSeats; }
    void setAvailableSeats(int seats) { availableSeats = seats; }
};

// Base class for Passenger
class Passenger {
protected:
    string name;
    int age;
    string contactInfo;
    string seatAllocation;

public:
    Passenger() : name(""), age(0), contactInfo(""), seatAllocation("") {}
    Passenger(string name, int age, string contactInfo, string seatAllocation)
        : name(name), age(age), contactInfo(contactInfo), seatAllocation(seatAllocation) {}

    virtual ~Passenger() {}

    virtual string getPassengerType() const = 0;

    string getName() const { return name; }
    int getAge() const { return age; }
    string getContactInfo() const { return contactInfo; }
    string getSeatAllocation() const { return seatAllocation; }
    void setSeatAllocation(string seat) { seatAllocation = seat; }
};

// Derived class for Domestic Flight
class DomesticFlight : public Flight {
private:
    bool hasMeal;

public:
    DomesticFlight() : Flight(), hasMeal(false) {}
    DomesticFlight(string flightNumber, string departureLocation, string arrivalLocation, string departureTime, string arrivalTime, int availableSeats, bool hasMeal)
        : Flight(flightNumber, departureLocation, arrivalLocation, departureTime, arrivalTime, availableSeats), hasMeal(hasMeal) {}

    string getFlightType() const override { return "Domestic"; }

    float calculateTicketPrice(int age) const override {
        return 200.0; // Simplified pricing for domestic flights
    }

    bool getHasMeal() const { return hasMeal; }
    void setHasMeal(bool meal) { hasMeal = meal; }
};

// Derived class for International Flight
class InternationalFlight : public Flight {
private:
    string destinationCountry;

public:
    InternationalFlight() : Flight(), destinationCountry("") {}
    InternationalFlight(string flightNumber, string departureLocation, string arrivalLocation, string departureTime, string arrivalTime, int availableSeats, string destinationCountry)
        : Flight(flightNumber, departureLocation, arrivalLocation, departureTime, arrivalTime, availableSeats), destinationCountry(destinationCountry) {}

    string getFlightType() const override { return "International"; }

    float calculateTicketPrice(int age) const override {
        return 500.0; // Simplified pricing for international flights
    }

    string getDestinationCountry() const { return destinationCountry; }
    void setDestinationCountry(string country) { destinationCountry = country; }
};

// Derived classes for different types of passengers
class AdultPassenger : public Passenger {
public:
    AdultPassenger() : Passenger() {}
    AdultPassenger(string name, int age, string contactInfo, string seatAllocation)
        : Passenger(name, age, contactInfo, seatAllocation) {}

    string getPassengerType() const override { return "Adult"; }
};

class ChildPassenger : public Passenger {
public:
    ChildPassenger() : Passenger() {}
    ChildPassenger(string name, int age, string contactInfo, string seatAllocation)
        : Passenger(name, age, contactInfo, seatAllocation) {}

    string getPassengerType() const override { return "Child"; }
};

class SeniorPassenger : public Passenger {
public:
    SeniorPassenger() : Passenger() {}
    SeniorPassenger(string name, int age, string contactInfo, string seatAllocation)
        : Passenger(name, age, contactInfo, seatAllocation) {}

    string getPassengerType() const override { return "Senior"; }
};

// Flight Management System class
class FlightManagementSystem {
private:
    static const int MAX_FLIGHTS = 100;
    static const int MAX_PASSENGERS = 500;
    Flight* flights[MAX_FLIGHTS];
    Passenger* passengers[MAX_PASSENGERS];
    int numFlights;
    int numPassengers;
    bool loggedIn;

public:
    FlightManagementSystem() : numFlights(0), numPassengers(0), loggedIn(false) {}

    ~FlightManagementSystem() {
        // Cleanup allocated memory
        for (int i = 0; i < numFlights; ++i) {
            delete flights[i];
        }
        for (int i = 0; i < numPassengers; ++i) {
            delete passengers[i];
        }
    }

    // Method to add a new flight
    void addFlight(string flightNumber, string departureLocation, string arrivalLocation, string departureTime, string arrivalTime, int availableSeats, bool isInternational) {
        if (numFlights < MAX_FLIGHTS) {
            Flight* newFlight;
            if (isInternational) {
                newFlight = new InternationalFlight(flightNumber, departureLocation, arrivalLocation, departureTime, arrivalTime, availableSeats, "USA");
            }
            else {
                newFlight = new DomesticFlight(flightNumber, departureLocation, arrivalLocation, departureTime, arrivalTime, availableSeats, false);
            }
            flights[numFlights++] = newFlight;
            cout << "Flight added successfully!" << endl;
        }
        else {
            cout << "Maximum number of flights reached!" << endl;
        }
    }

    // Method to update details of an existing flight
    void updateFlightDetails(int index, int availableSeats) {
        if (index >= 0 && index < numFlights) {
            flights[index]->setAvailableSeats(availableSeats);
            cout << "Flight details updated successfully!" << endl;
        }
        else {
            cout << "Invalid flight index!" << endl;
        }
    }
     Passenger* getPassengerByName(const string& name) {
        for (int i = 0; i < numPassengers; i++) {
            if (passengers[i]->getName() == name) {
                return passengers[i];
            }
        }
        return nullptr; // Return null if no passenger found
    }
    // Method to add a new passenger
    void addPassenger(string name, int age, string contactInfo, string seatAllocation, bool isAdult) {
        if (numPassengers < MAX_PASSENGERS) {
            Passenger* newPassenger;
            passengers[numPassengers++];
            cout << "Passenger added successfully!" << endl;
        }
        else {
            cout << "Maximum number of passengers reached!" << endl;
        }
    }

void searchFlights(const string& key, const string& value) {
    bool found = false;
    for (int i = 0; i < numFlights; i++) {
        if ((key == "flightNumber" && flights[i]->getFlightNumber() == value) ||
            (key == "departureLocation" && flights[i]->getDepartureLocation() == value) ||
            (key == "arrivalLocation" && flights[i]->getArrivalLocation() == value)) {
            // Display flight details
            found = true;
            cout << "Flight Number: " << flights[i]->getFlightNumber() << ", Departure: " << flights[i]->getDepartureLocation()
                 << ", Arrival: " << flights[i]->getArrivalLocation() << ", Seats: " << flights[i]->getAvailableSeats() << endl;
        }
    }
    if (!found) cout << "No matching flights found." << endl;
}
void displayAvailableFlights() {
    for (int i = 0; i < numFlights; i++) {
        if (flights[i]->getAvailableSeats() > 0) {
            cout << "Flight Number: " << flights[i]->getFlightNumber() << " has " << flights[i]->getAvailableSeats() << " available seats." << endl;
        }
    }
}
bool bookFlight(const string& flightNumber, Passenger* passenger) {
    for (int i = 0; i < numFlights; i++) {
        if (flights[i]->getFlightNumber() == flightNumber && flights[i]->getAvailableSeats() > 0) {
            flights[i]->setAvailableSeats(flights[i]->getAvailableSeats() - 1);
            passenger->setSeatAllocation(flightNumber);
            cout << "Booking successful for " << passenger->getName() << " on flight " << flightNumber << endl;
            return true;
        }
    }
    cout << "Booking failed." << endl;
    return false;
}
bool cancelBooking(const string& flightNumber, Passenger* passenger) {
    for (int i = 0; i < numFlights; i++) {
        if (flights[i]->getFlightNumber() == flightNumber) {
            flights[i]->setAvailableSeats(flights[i]->getAvailableSeats() + 1);
            passenger->setSeatAllocation("");
            cout << "Booking cancelled for " << passenger->getName() << endl;
            return true;
        }
    }
    cout << "Cancellation failed." << endl;
    return false;
}
void displayPassengers(const string& flightNumber) {
    cout << "Passengers on Flight " << flightNumber << ":" << endl;
    bool found = false;
    for (int i = 0; i < numPassengers; i++) {
        if (passengers[i]->getSeatAllocation() == flightNumber) {
            cout << passengers[i]->getName() << " (" << passengers[i]->getAge() << " years)" << endl;
            found = true;
        }
    }
    if (!found) cout << "No passengers found on this flight." << endl;
}
float calculateTicketPrice(int age) const  {
    return (age > 65) ? 100.0 : 500.0;  // Discounted price if senior
}
class Passenger {
protected:
    string mealPreference;  // Add this attribute

public:
    void setMealPreference(const string& meal) { mealPreference = meal; }
    string getMealPreference() const { return mealPreference; }
};
int countPassengers(const string& flightNumber) {
    int count = 0;
    for (int i = 0; i < numPassengers; i++) {
        if (passengers[i]->getSeatAllocation() == flightNumber) {
            count++;
        }
    }
    return count;
}
void displayTotalFlights() {
    cout << "Total number of flights: " << numFlights << endl;
}

    // Other methods for login, logout, etc.
    void login(string username, string password) {
        // Mock authentication
        if (username == "admin" && password == "admin123") {
            cout << "Login successful!" << endl;
            loggedIn = true;
        }
        else {
            cout << "Invalid username or password!" << endl;
        }
    }

    void logout() {
        loggedIn = false;
        cout << "Logged out successfully!" << endl;
    }

    bool isLoggedIn() {
        return loggedIn;
    }
};
int main() {
FlightManagementSystem fms;

    // Define variables for input
    int choice, index;
    bool running = true;
    string username, password, flightNumber, departureLocation, arrivalLocation, departureTime, arrivalTime;
    int availableSeats, age;
    bool isInternational;
    string name, contactInfo, seatAllocation;
    bool isAdult;

    while (running) {
        cout << "Welcome to the Flight Management System!" << endl;
        cout << "1. Login" << endl;
        cout << "2. Add Flight" << endl;
        cout << "3. Update Flight Details" << endl;
        cout << "4. Add Passenger" << endl;
        cout << "5. Search Flights" << endl;
        cout << "6. Display Available Flights" << endl;
        cout << "7. Book a Flight" << endl;
        cout << "8. Cancel a Booking" << endl;
        cout << "9. Display All Passengers on a Flight" << endl;
        cout << "10. Logout" << endl;
        cout << "11. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (!fms.isLoggedIn()) {
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                fms.login(username, password);
            } else {
                cout << "Already logged in!" << endl;
            }
            break;
        case 2:
            if (fms.isLoggedIn()) {
                cout << "Enter flight number: ";
                cin >> flightNumber;
                cout << "Enter departure location: ";
                cin >> departureLocation;
                cout << "Enter arrival location: ";
                cin >> arrivalLocation;
                cout << "Enter departure time (YYYY-MM-DD HH:MM): ";
                cin >> departureTime;
                cout << "Enter arrival time (YYYY-MM-DD HH:MM): ";
                cin >> arrivalTime;
                cout << "Enter available seats: ";
                cin >> availableSeats;
                cout << "Is it an international flight? (0 for no, 1 for yes): ";
                cin >> isInternational;
                fms.addFlight(flightNumber, departureLocation, arrivalLocation, departureTime, arrivalTime, availableSeats, isInternational);
            } else {
                cout << "Please login first!" << endl;
            }
            break;
        case 3:
            if (fms.isLoggedIn()) {
                cout << "Enter index of flight to update: ";
                cin >> index;
                cout << "Enter new available seats: ";
                cin >> availableSeats;
                fms.updateFlightDetails(index, availableSeats);
            } else {
                cout << "Please login first!" << endl;
            }
            break;
        case 4:
            if (fms.isLoggedIn()) {
                cout << "Enter passenger name: ";
                cin.ignore(); // Clear input buffer
                getline(cin, name);
                cout << "Enter passenger age: ";
                cin >> age;
                cout << "Enter contact information: ";
                cin.ignore(); // Clear input buffer
                getline(cin, contactInfo);
                cout << "Enter seat allocation: ";
                cin >> seatAllocation;
                cout << "Is it an adult passenger? (0 for no, 1 for yes): ";
                cin >> isAdult;
                fms.addPassenger(name, age, contactInfo, seatAllocation, isAdult);
            } else {
                cout << "Please login first!" << endl;
            }
            break;
        case 5:
            if (fms.isLoggedIn()) {
                string key, value;
                cout << "Enter search key (flightNumber, departureLocation, arrivalLocation): ";
                cin >> key;
                cout << "Enter search value: ";
                cin >> value;
                fms.searchFlights(key, value);
            } else {
                cout << "Please login first!" << endl;
            }
            break;
        case 6:
            if (fms.isLoggedIn()) {
                fms.displayAvailableFlights();
            } else {
                cout << "Please login first!" << endl;
            }
            break;
        case 7:
            if (fms.isLoggedIn()) {
                cout << "Enter flight number to book: ";
                cin >> flightNumber;
                cout << "Enter passenger name: ";
                cin >> name;
                // Assume we have a method to get passenger by name
                Passenger* passenger = fms.getPassengerByName(name);
                if (passenger) {
                    fms.bookFlight(flightNumber, passenger);
                } else {
                    cout << "Passenger not found." << endl;
                }
            } else {
                cout << "Please login first!" << endl;
            }
            break;
        case 8:
            if (fms.isLoggedIn()) {
                cout << "Enter flight number to cancel booking: ";
                cin >> flightNumber;
                cout << "Enter passenger name: ";
                cin >> name;
                // Assume we have a method to get passenger by name
                Passenger* passenger = fms.getPassengerByName(name);
                if (passenger) {
                    fms.cancelBooking(flightNumber, passenger);
                } else {
                    cout << "Passenger not found." << endl;
                }
            } else {
                cout << "Please login first!" << endl;
            }
            break;
        case 9:
            if (fms.isLoggedIn()) {
                cout << "Enter flight number to display passengers: ";
                cin >> flightNumber;
                fms.displayPassengers(flightNumber);
            } else {
                cout << "Please login first!" << endl;
            }
            break;
        case 10:
            if (fms.isLoggedIn()) {
                fms.logout();
            } else {
                cout << "You are not logged in!" << endl;
            }
            break;
        case 11:
            running = false;
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice! Please enter a number between 1 and 11." << endl;
            break;
        }
    }

    return 0;
}
