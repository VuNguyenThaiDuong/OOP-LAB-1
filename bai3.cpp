#include <iostream>
#include <cmath> // Library for the abs function
using namespace std;

// Function to calculate the Greatest Common Divisor (GCD)
int calculateGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to simplify a fraction
pair<int, int> simplifyFraction(int numerator, int denominator) {
    int gcd = calculateGCD(abs(numerator), abs(denominator));
    numerator /= gcd;
    denominator /= gcd;
    
    // Ensure the denominator is positive
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    
    return {numerator, denominator};
}

// Function to add two fractions
pair<int, int> addFractions(int num1, int den1, int num2, int den2) {
    int numerator = num1 * den2 + num2 * den1;
    int denominator = den1 * den2;
    return simplifyFraction(numerator, denominator);
}

// Function to subtract two fractions
pair<int, int> subtractFractions(int num1, int den1, int num2, int den2) {
    int numerator = num1 * den2 - num2 * den1;
    int denominator = den1 * den2;
    return simplifyFraction(numerator, denominator);
}

// Function to multiply two fractions
pair<int, int> multiplyFractions(int num1, int den1, int num2, int den2) {
    int numerator = num1 * num2;
    int denominator = den1 * den2;
    return simplifyFraction(numerator, denominator);
}

// Function to divide two fractions
pair<int, int> divideFractions(int num1, int den1, int num2, int den2) {
    if (num2 == 0) {
        throw runtime_error("Cannot divide by a fraction with a numerator of 0.");
    }
    int numerator = num1 * den2;
    int denominator = den1 * num2;
    return simplifyFraction(numerator, denominator);
}

int main() {
    int numerator1, denominator1, numerator2, denominator2;

    // Input for the first fraction
    cout << "Enter numerator for the first fraction: ";
    cin >> numerator1;

    cout << "Enter denominator for the first fraction: ";
    cin >> denominator1;

    // Input for the second fraction
    cout << "Enter numerator for the second fraction: ";
    cin >> numerator2;

    cout << "Enter denominator for the second fraction: ";
    cin >> denominator2;

    // Check if the denominators are zero
    if (denominator1 == 0 || denominator2 == 0) {
        cout << "Denominator must not be 0" << endl;
        return 1; // Exit the program if a denominator is zero
    }

    // Calculate and display the results
    try {
        auto sum = addFractions(numerator1, denominator1, numerator2, denominator2);
        auto difference = subtractFractions(numerator1, denominator1, numerator2, denominator2);
        auto product = multiplyFractions(numerator1, denominator1, numerator2, denominator2);
        
        // Check the numerator of the second fraction to determine whether to calculate the quotient
        if (numerator2 != 0) {
            auto quotient = divideFractions(numerator1, denominator1, numerator2, denominator2);
            cout << "Quotient: " << quotient.first << "/" << quotient.second << endl;
        } else {
            cout << "Cannot calculate quotient since the numerator of the second fraction is 0." << endl;
        }

        // Print results for sum, difference, and product
        if (sum.second == 1) {
            cout << "Sum: " << sum.first << endl;
        } else {
            cout << "Sum: " << sum.first << "/" << sum.second << endl;
        }

        if (difference.second == 1) {
            cout << "Difference: " << difference.first << endl;
        } else {
            cout << "Difference: " << difference.first << "/" << difference.second << endl;
        }

        if (product.second == 1) {
            cout << "Product: " << product.first << endl;
        } else {
            cout << "Product: " << product.first << "/" << product.second << endl;
        }
    } catch (const runtime_error& e) {
        cout << e.what() << endl; // Handle the case of division by zero
    }

    return 0;
}
