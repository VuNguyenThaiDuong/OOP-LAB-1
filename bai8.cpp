#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

// Structure to represent a savings book
struct SavingsBook {
    string code;          // Book code (max 5 characters)
    string type;          // Type of savings (short-term, long-term)
    string customerName;  // Customer name (max 30 characters)
    string idCard;        // ID card (9 or 12 digits)
    tm openingDate;       // Opening date (tm structure for date)
    double depositAmount; // Deposit amount (positive value)
    double interestRate;  // Interest rate (% per year)
};

// Function to validate the savings book code
// Input: string code - The code of the savings book
// Output: bool - Returns true if valid, false otherwise
// This function checks if the code is at most 5 characters long
// and contains only alphanumeric characters.
bool isValidCode(const string& code) {
    return code.length() <= 5 && code.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") == string::npos;
}

// Function to validate the ID card number
// Input: string idCard - The ID card number
// Output: bool - Returns true if valid (9 or 12 digits), false otherwise
// This function checks if the ID card is either 9 or 12 digits long
// and consists only of numeric characters.
bool isValidIdCard(const string& idCard) {
    return (idCard.length() == 9 || idCard.length() == 12) && idCard.find_first_not_of("0123456789") == string::npos;
}

// Function to check if a year is a leap year
// Input: int year - The year to check
// Output: bool - Returns true if the year is a leap year, false otherwise
// This function determines if a given year is a leap year based on the
// rules of the Gregorian calendar.
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Function to validate the opening date
// Input: int day, int month, int year - The date to validate
// Output: bool - Returns true if the date is valid, false otherwise
// This function checks if the given date is valid considering the month
// and whether it's a leap year.
bool isValidDate(int day, int month, int year) {
    if (month < 1 || month > 12) return false; // Month must be between 1 and 12
    if (day < 1) return false; // Day must be positive

    // Days in each month
    int daysInMonth[] = { 31, (isLeapYear(year) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    return day <= daysInMonth[month - 1]; // Check if day is valid for the month
}

// Function to validate deposit amount
// Input: double amount - The deposit amount to validate
// Output: bool - Returns true if amount is positive, false otherwise
// This function ensures that the deposit amount is a positive value.
bool isValidDepositAmount(double amount) {
    return amount > 0;
}

// Function to calculate interest based on the type of savings
// Input: SavingsBook& book - The savings book for which to calculate interest
// Output: double - Returns the calculated interest amount
// This function computes the interest based on the savings type
// and the duration since the book was opened.
double calculateInterest(const SavingsBook& book) {
    time_t now = time(0);
    tm* currentTime = localtime(&now);
    double interest = 0.0;

    // Calculate the difference in days
    double days = difftime(mktime(currentTime), mktime(const_cast<tm*>(&book.openingDate))) / (60 * 60 * 24);
    
    if (book.type == "short-term" && days <= 183) {
        interest = book.depositAmount * (book.interestRate / 100) * (days / 365);
    } else if (book.type == "long-term" && days > 183) {
        interest = book.depositAmount * (book.interestRate / 100) * (days / 365);
    }
    return interest;
}

// Function to withdraw money from the savings book
// Input: SavingsBook& book - The savings book from which to withdraw money
//        double amount - The amount to withdraw
// Output: void
// This function handles the withdrawal process, including adjusting
// the interest rate if the withdrawal is made before the term ends.
void withdrawMoney(SavingsBook& book, double amount) {
    if (amount > book.depositAmount) {
        cout << "Withdraw amount exceeds the deposit amount." << endl;
        return;
    }
    
    // If withdrawing before the term ends
    if (book.type == "short-term") {
        cout << "Withdrawing before the term ends, interest rate will be lower." << endl;
        book.interestRate = 0.5; // Adjust interest rate for early withdrawal
    }
    
    book.depositAmount -= amount;
    cout << "Successfully withdrawn: " << amount << endl;
}

// Function to print savings book information
// Input: SavingsBook& book - The savings book to print
// Output: void
// This function displays all relevant information about the savings book,
// including calculated interest.
void printSavingsBook(const SavingsBook& book) {
    cout << "Savings Book Code: " << book.code << endl;
    cout << "Type of Savings: " << book.type << endl;
    cout << "Customer Name: " << book.customerName << endl;
    cout << "ID Card: " << book.idCard << endl;
    cout << "Opening Date: " << put_time(&book.openingDate, "%d/%m/%Y") << endl;
    cout << "Deposit Amount: " << fixed << setprecision(2) << book.depositAmount << endl;
    cout << "Interest Rate: " << book.interestRate << "%" << endl;
    cout << "Calculated Interest: " << fixed << setprecision(2) << calculateInterest(book) << endl;
}

// Function to enter savings book information
// Output: SavingsBook - Returns a SavingsBook struct with entered data
// This function prompts the user for all relevant information to create
// a new savings book, validating input as necessary.
SavingsBook enterSavingsBookInfo() {
    SavingsBook book;
    
    // Input code
    do {
        cout << "Enter savings book code (max 5 characters): ";
        cin >> book.code;
    } while (!isValidCode(book.code));
    
    // Input type
    cout << "Enter type of savings (short-term, long-term): ";
    cin >> book.type;

    // Input customer name
    cout << "Enter customer name (max 30 characters): ";
    cin.ignore();
    getline(cin, book.customerName);

    // Input ID card
    do {
        cout << "Enter ID card (9 or 12 digits): ";
        cin >> book.idCard;
    } while (!isValidIdCard(book.idCard));

    // Input opening date
    int day, month, year;
    do {
        cout << "Enter opening date (dd mm yyyy): ";
        cin >> day >> month >> year;
    } while (!isValidDate(day, month, year));

    book.openingDate = {0};
    book.openingDate.tm_mday = day;
    book.openingDate.tm_mon = month - 1; // Month is 0-based in tm structure
    book.openingDate.tm_year = year - 1900; // Year since 1900

    // Input deposit amount
    do {
        cout << "Enter deposit amount (must be positive): ";
        cin >> book.depositAmount;
    } while (!isValidDepositAmount(book.depositAmount));

    // Set default interest rate
    book.interestRate = 0.0;

    return book;
}

int main() {
    vector<SavingsBook> savingsBooks; // List to store savings books
    int choice; // User choice for menu options

    do {
        cout << "1. Enter Savings Book\n";
        cout << "2. Print Savings Book Information\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                SavingsBook book = enterSavingsBookInfo(); // Get book info from user
                savingsBooks.push_back(book); // Add to the list of savings books
                cout << "Savings book added successfully." << endl;
                break;
            }
            case 2: {
                for (const auto& book : savingsBooks) {
                    printSavingsBook(book); // Print each savings book's info
                    cout << endl;
                }
                break;
            }
            case 3: {
                string code;
                cout << "Enter savings book code to withdraw money: ";
                cin >> code;
                double amount;
                cout << "Enter amount to withdraw: ";
                cin >> amount;

                for (auto& book : savingsBooks) {
                    if (book.code == code) {
                        withdrawMoney(book, amount); // Withdraw money from specified book
                        break;
                    }
                }
                break;
            }
            case 4:
                cout << "Exiting program." << endl; // Exit the program
                break;
            default:
                cout << "Invalid choice, please try again." << endl; // Invalid choice handling
        }
    } while (choice != 4); // Loop until exit option is chosen

    return 0; // Exit the program
}


