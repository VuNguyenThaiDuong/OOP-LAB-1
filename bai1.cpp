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

// Function to simplify the fraction
// Input: int numerator - The numerator, int denominator - The denominator
// Output: Prints the simplified fraction in the form of "numerator/denominator"
void simplifyFraction(int numerator, int denominator) {
    int gcd = calculateGCD(abs(numerator), abs(denominator));
    numerator /= gcd;
    denominator /= gcd;
    cout << "Reduced answer: " << numerator << "/" << denominator << endl;
}

int main() {
    int numerator, denominator;

    // Input: Prompt user for the numerator
    cout << "Enter numerator: ";
    cin >> numerator;      // User inputs the numerator

    // Input: Prompt user for the denominator
    cout << "Enter denominator: ";
    cin >> denominator;    // User inputs the denominator

    // Check if the denominator is zero
    if (denominator == 0) {
        cout << "Denominator must be not 0" << endl;
    } else {
        // Determine the sign of the fraction
        determineSign(numerator, denominator);
        
        // Check if the fraction can be simplified to a whole number
        if (numerator % denominator == 0) {
            cout << "Reduced answer: " << numerator / denominator << endl;
        } else {
            // Simplify the fraction if it's not a whole number
            simplifyFraction(numerator, denominator);
        }
    }
    
    return 0;
}
