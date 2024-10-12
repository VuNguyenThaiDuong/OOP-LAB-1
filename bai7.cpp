#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

// Structure to hold flight information
struct Flight {
    string flightCode;           // Flight code
    string departureDate;        // Departure date (dd/mm/yyyy)
    string departureTime;        // Departure time (hh:mm)
    string departureLocation;     // Departure location
    string arrivalLocation;       // Arrival location
};

// Function to validate flight code
// Input: flight code as a string
// Output: true if valid, false otherwise
bool isValidFlightCode(const string &code) {
    if (code.length() > 5 || code.find(' ') != string::npos) return false;
    for (char c : code) {
        if (!isalnum(c)) return false; // no special characters
    }
    return true;
}

// Function to validate date
// Input: date as a string (dd/mm/yyyy)
// Output: true if valid, false otherwise
bool isValidDate(const string &date) {
    int day, month, year;
    char sep1, sep2;
    stringstream ss(date);
    ss >> day >> sep1 >> month >> sep2 >> year;

    // Check date format
    if (sep1 != '/' || sep2 != '/') return false;

    // Check month range
    if (month < 1 || month > 12) return false;

    // Check days based on month
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            // Months with 31 days
            return (day >= 1 && day <= 31);
        case 4: case 6: case 9: case 11:
            // Months with 30 days
            return (day >= 1 && day <= 30);
        case 2:
            // February: Check for leap year
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                return (day >= 1 && day <= 29); // Leap year
            } else {
                return (day >= 1 && day <= 28); // Non-leap year
            }
        default:
            return false; // This should never be reached
    }
}

// Function to validate time
// Input: time as a string (hh:mm)
// Output: true if valid, false otherwise
bool isValidTime(const string &time) {
    int hour, minute;
    char sep;
    stringstream ss(time);
    ss >> hour >> sep >> minute;
    return (sep == ':' && hour >= 0 && hour < 24 && minute >= 0 && minute < 60);
}

// Function to validate location
// Input: location as a string
// Output: true if valid, false otherwise
bool isValidLocation(const string &location) {
    if (location.length() > 20 || location.find_first_of("0123456789") != string::npos) return false;
    for (char c : location) {
        if (!isalnum(c) && c != ' ') return false; // no numbers or special characters
    }
    return true;
}

// Function to input flight information
// Input: none
// Output: returns a Flight object with validated data
Flight inputFlight() {
    Flight flight;
    do {
        cout << "Enter flight code (max 5 characters, no spaces or special characters): ";
        cin >> flight.flightCode;
        if (!isValidFlightCode(flight.flightCode)) {
            cout << "Invalid flight code. Please try again." << endl;
        }
    } while (!isValidFlightCode(flight.flightCode));
    
    do {
        cout << "Enter departure date (dd/mm/yyyy): ";
        cin >> flight.departureDate;
        if (!isValidDate(flight.departureDate)) {
            cout << "Invalid date. Please ensure the date is in the format dd/mm/yyyy and valid." << endl;
        }
    } while (!isValidDate(flight.departureDate));
    
    do {
        cout << "Enter departure time (hh:mm): ";
        cin >> flight.departureTime;
        if (!isValidTime(flight.departureTime)) {
            cout << "Invalid time. Please enter the time in the format hh:mm." << endl;
        }
    } while (!isValidTime(flight.departureTime));
    
    do {
        cout << "Enter departure location (max 20 characters, no numbers or special characters): ";
        cin.ignore();
        getline(cin, flight.departureLocation);
        if (!isValidLocation(flight.departureLocation)) {
            cout << "Invalid departure location. Please try again." << endl;
        }
    } while (!isValidLocation(flight.departureLocation));
    
    do {
        cout << "Enter arrival location (max 20 characters, no numbers or special characters): ";
        getline(cin, flight.arrivalLocation);
        if (!isValidLocation(flight.arrivalLocation)) {
            cout << "Invalid arrival location. Please try again." << endl;
        }
    } while (!isValidLocation(flight.arrivalLocation));

    return flight;
}

// Comparison function for sorting flights
// Input: two Flight objects (a and b)
// Output: true if a should come before b based on date and time
bool compareFlights(const Flight &a, const Flight &b) {
    if (a.departureDate != b.departureDate)
        return a.departureDate < b.departureDate;
    return a.departureTime < b.departureTime;
}

// Function to print flight information
// Input: a Flight object
// Output: prints the flight details to console
void printFlight(const Flight &flight) {
    cout << "Flight code: " << flight.flightCode
         << ", Departure date: " << flight.departureDate
         << ", Departure time: " << flight.departureTime
         << ", Departure location: " << flight.departureLocation
         << ", Arrival location: " << flight.arrivalLocation << endl;
}

// Function to search for flights
// Input: vector of Flight objects and a query string
// Output: prints matching flights to console
void searchFlight(const vector<Flight> &flights, const string &query) {
    bool found = false;
    for (const Flight &flight : flights) {
        if (flight.flightCode == query || flight.departureLocation == query || flight.arrivalLocation == query) {
            printFlight(flight);
            found = true;
        }
    }
    if (!found) {
        cout << "No flights found for the query: " << query << endl;
    }
}

// Function to count flights between two locations
// Input: vector of Flight objects, from and to locations
// Output: returns the count of matching flights
int countFlights(const vector<Flight> &flights, const string &from, const string &to) {
    int count = 0;
    for (const Flight &flight : flights) {
        if (flight.departureLocation == from && flight.arrivalLocation == to) {
            count++;
        }
    }
    return count;
}

// Function to display flights from a specific location on a specific date
// Input: vector of Flight objects, location, and date
// Output: prints matching flights to console
void showFlightsFromDate(const vector<Flight> &flights, const string &location, const string &date) {
    bool found = false;
    for (const Flight &flight : flights) {
        if (flight.departureLocation == location && flight.departureDate == date) {
            printFlight(flight);
            found = true;
        }
    }
    if (!found) {
        cout << "No flights found departing from " << location << " on " << date << "." << endl;
    }
}

// Main function to run the flight management program
int main() {
    int n;
    cout << "Enter number of flights: ";
    cin >> n;

    vector<Flight> flights(n);

    // Input flight information
    for (int i = 0; i < n; ++i) {
        cout << "Enter details for flight " << (i + 1) << ":\n";
        flights[i] = inputFlight();
    }

    // Sort flights by departure date and time
    sort(flights.begin(), flights.end(), compareFlights);

    // Output sorted flight list
    cout << "\nSorted list of flights:\n";
    for (const Flight &flight : flights) {
        printFlight(flight);
    }

    // Search for flights
    string query;
    cout << "\nEnter flight code, departure, or arrival location to search: ";
    cin >> query;
    cout << "Search results:\n";
    searchFlight(flights, query);

    // Display flights from a specific location on a specific date
    string location, date;
    cout << "\nEnter departure location and date (dd/mm/yyyy) to list flights: ";
    cin.ignore();
    getline(cin, location);
    getline(cin, date);
    cout << "Flights departing from " << location << " on " << date << ":\n";
    showFlightsFromDate(flights, location, date);

    // Count flights between two locations
    string from, to;
    cout << "\nEnter departure and arrival locations to count flights: ";
    getline(cin, from);
    getline(cin, to);
    int count = countFlights(flights, from, to);
    cout << "Number of flights from " << from << " to " << to << ": " << count << endl;

    return 0;
}
