#include <iostream>
#include <cmath> // For using pow and fabs functions
using namespace std;

// Function to calculate factorial
// Input: n (int) - the number to calculate the factorial for
// Output: The factorial of n (long long)
long long factorial(int n) {
    long long result = 1; // Initialize result to 1
    for (int i = 1; i <= n; ++i) {
        result *= i; // Multiply result by i to calculate factorial
    }
    return result; // Return the factorial value
}

// Function to calculate sin(x) using Taylor series
// Input: x (double) - the angle in radians for which to calculate sin(x)
// Output: The sine of x (double)
double calculateSin(double x) {
    double sinValue = 0.0; // To hold the cumulative result of sine
    int n = 0; // Term counter for the series
    double term; // Current term in the Taylor series

    // Continue adding terms until the absolute value of the current term is less than 0.00001
    do {
        // Calculate the current term using the Taylor series formula
        term = (pow(-1, n) * pow(x, 2 * n + 1)) / factorial(2 * n + 1);
        sinValue += term; // Add the current term to the cumulative result
        n++; // Increment the term counter
    } while (fabs(term) >= 0.00001); // Loop until the term is smaller than the desired precision

    return sinValue; // Return the calculated sine value
}

int main() {
    double x; // Variable to hold user input
    cout << "Enter the value of x (in radians): "; // Prompt user for input
    cin >> x; // Read the input value

    // Call the calculateSin function to compute sin(x)
    double result = calculateSin(x);

    // Display the result
    cout << "sin(" << x << ") = " << result << endl; // Print the sine value
    return 0; // Indicate successful completion
}
