#include <iostream>
#include <vector>

using namespace std;

/**
 * Function to count occurrences of array A in array B.
 * 
 * @param A Vector of integers representing the subarray.
 * @param B Vector of integers representing the main array.
 * @return A pair containing:
 *         - The count of occurrences of A in B.
 *         - A vector containing the starting indices of each occurrence.
 */
pair<int, vector<int>> countOccurrences(const vector<int>& A, const vector<int>& B) {
    int lenA = A.size(); // Length of the subarray A
    int lenB = B.size(); // Length of the main array B
    
    int count = 0; // Counter for occurrences
    vector<int> positions; // Vector to store starting positions of occurrences

    // Loop through the main array B to check for occurrences of A
    for (int i = 0; i <= lenB - lenA; i++) {
        bool match = true; // Flag to check if A matches B starting at index i
        // Check if the subarray A matches the corresponding elements in B
        for (int j = 0; j < lenA; j++) {
            if (B[i + j] != A[j]) {
                match = false; // If any element does not match, set match to false
                break;
            }
        }
        if (match) {
            count++; // Increment the count if a match is found
            positions.push_back(i); // Store the starting index of the match
        }
    }
    
    return {count, positions}; // Return the count and the positions
}

int main() {
    int nA, nB; // Variables to hold the sizes of arrays A and B
    
    // Input the sizes of arrays A and B
    cout << "Enter the number of elements in array A and B: ";
    cin >> nA >> nB;
    
    vector<int> A(nA); // Declare vector A of size nA
    vector<int> B(nB); // Declare vector B of size nB
    
    // Input elements for array A
    cout << "Enter the elements of array A: ";
    for (int i = 0; i < nA; i++) {
        cin >> A[i];
    }

    // Input elements for array B
    cout << "Enter the elements of array B: ";
    for (int i = 0; i < nB; i++) {
        cin >> B[i];
    }

    // Call the function to count occurrences and retrieve positions
    auto [count, positions] = countOccurrences(A, B);

    // Output the result
    cout << "Number of times array A appears in array B: " << count << endl;
    cout << "Starting indices of occurrences: ";
    for (int pos : positions) {
        cout << pos << " "; // Print each starting index
    }
    cout << endl;

    return 0; // Return 0 to indicate successful execution
}
