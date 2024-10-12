#include <iostream>
#include <cmath> // Library for the abs function
using namespace std;

// Function to calculate the Greatest Common Divisor (GCD)
// Input: int a - First number, int b - Second number
// Output: Returns the GCD of a and b
int calculateGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to determine the sign of the fraction
// Input: int &numerator - Reference to the numerator, 
//        int &denominator - Reference to the denominator
// Output: Modifies the numerator and denominator to ensure the denominator is positive
void determineSign(int &numerator, int &denominator) {
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}

// Function to simplify a fraction
// Input: int numerator - The numerator, int denominator - The denominator
// Output: Prints the simplified fraction in the form of "numerator/denominator"
void simplifyFraction(int numerator, int denominator) {
    int gcd = calculateGCD(abs(numerator), abs(denominator));
    numerator /= gcd;
    denominator /= gcd;
    cout << "Reduced answer: " << numerator << "/" << denominator << endl;
}

// Function to compare two fractions
// Input: int numerator_1, int denominator_1 - First fraction
//        int numerator_2, int denominator_2 - Second fraction
// Output: Prints which fraction is larger or if they are equal
void compareFractions(int numerator_1, int denominator_1, int numerator_2, int denominator_2) {
    int a = numerator_1 * denominator_2; // Cross multiplication
    int b = numerator_2 * denominator_1; // Cross multiplication

    if (a > b) {
        cout << "Fraction " << numerator_1 << '/' << denominator_1 << " is larger." << endl;
        simplifyFraction(numerator_1, denominator_1); // Corrected function name
    } else if (a < b) {
        cout << "Fraction " << numerator_2 << '/' << denominator_2 << " is larger." << endl;
        simplifyFraction(numerator_2, denominator_2); // Corrected function name
    } else {
        cout << "Both fractions are equal." << endl;
    }
}

int main() {
    int numerator_1, denominator_1, numerator_2, denominator_2;

    // Input: Prompt user for the first fraction
    cout << "Enter numerator for first fraction: ";
    cin >> numerator_1;      // User inputs the numerator

    cout << "Enter denominator for first fraction: ";
    cin >> denominator_1;    // User inputs the denominator

    // Input: Prompt user for the second fraction
    cout << "Enter numerator for second fraction: ";
    cin >> numerator_2;      // User inputs the numerator

    cout << "Enter denominator for second fraction: ";
    cin >> denominator_2;    // User inputs the denominator

    // Check if the denominators are zero
    if (denominator_1 == 0 || denominator_2 == 0) {
        cout << "Denominator must not be 0" << endl;
    } else {
        // Determine the sign of the fractions
        determineSign(numerator_1, denominator_1);
        determineSign(numerator_2, denominator_2);

        // Compare the two fractions
        compareFractions(numerator_1, denominator_1, numerator_2, denominator_2);
    }
    
    return 0;
}
