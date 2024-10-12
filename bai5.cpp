#include <iostream>
using namespace std;

// Function to check if the year is a leap year
// Input: year (int) - the year to check
// Output: 1 if it's a leap year, 0 if it's not
int checkLeapyear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 1 : 0;
}

// Function to find the limits of days in each month
// Input: year (int) - the year to check
// Output: limit_day_of_month[] (int[]) - an array containing the number of days in each month
void find_limit_to_month(int year, int limit_day_of_month[]) {
    limit_day_of_month[2] = (checkLeapyear(year) == 1) ? 29 : 28; // Set the number of days for February
}

// Function to find the previous date
// Input: day (int), month (int), year (int) - the current day, month, and year
// Output: Prints the previous date
void findPreviousdate(int day, int month, int year, int limit_day_of_month[]) {
    if (day - 1 > 0) {
        day -= 1; // Decrease the day if it's greater than 1
    } else {
        if (month - 1 <= 0) {
            month = 12; // Switch to December
            year -= 1; // Decrease the year
            day = limit_day_of_month[month]; // Set the day to the last day of December
        } else {
            month -= 1; // Decrease the month
            day = limit_day_of_month[month]; // Set the day to the last day of the previous month
        }
    }
    cout << "Previous date is: " << day << "/" << month << "/" << year << endl;
}

// Function to find the next date
// Input: day (int), month (int), year (int) - the current day, month, and year
// Output: Prints the next date
void findNextdate(int day, int month, int year, int limit_day_of_month[]) {
    if (day + 1 <= limit_day_of_month[month]) {
        day += 1; // Increase the day if it doesn't exceed the limit
    } else {
        day = 1; // Reset the day to 1
        if (month + 1 > 12) {
            month = 1; // Switch to January
            year += 1; // Increase the year
        } else {
            month += 1; // Increase the month
        }
    }
    cout << "Next date is: " << day << "/" << month << "/" << year << endl;
}

// Function to find the ordinal day of the year
// Input: day (int), month (int), year (int) - the current day, month, and year
// Output: Prints the ordinal day of the year
void findorderdate(int day, int month, int year, int limit_day_of_month[]) {
    int orderday = 0;
    for (int i = 1; i < month; i++) {
        orderday += limit_day_of_month[i]; // Sum the days of previous months
    }
    orderday += day; // Add the current day
    cout << "Order day is: " << orderday << endl;
}

// Main function to handle user input and call other functions
// Input: day (int), month (int), year (int) - user-provided current day, month, and year
// Output: Calls functions to find the previous date, next date, and ordinal day
void findPreviousandNextdate(int day, int month, int year) {
    int limit_day_of_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    find_limit_to_month(year, limit_day_of_month); // Get the number of days in each month

    // Validate the day against the month's limit
    if (day > limit_day_of_month[month]) {
        cout << "Day exceeded limit for month." << endl; // Notify if the day exceeds the limit
    } else {
        findPreviousdate(day, month, year, limit_day_of_month); // Find the previous date
        findNextdate(day, month, year, limit_day_of_month); // Find the next date
        findorderdate(day, month, year, limit_day_of_month); // Find the ordinal day
    }
}

int main() {
    int day, month, year;
    cout << "Enter date (dd mm yyyy): "; // Prompt user to enter a date
    cin >> day >> month >> year;

    // Validate the date input
    if (day <= 0 || month <= 0 || month > 12) {
        cout << "This date does not exist." << endl; // Notify if the date is invalid
    } else {
        findPreviousandNextdate(day, month, year); // Call the function to find previous and next dates
    }

    return 0;
}
