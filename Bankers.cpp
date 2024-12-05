#include <iostream>   // Include the library for input and output operations
#include <fstream>    // Include the library for file operations
#include <vector>     // Include the library for using vectors
#include <iomanip>    // Include the library for formatted output

using namespace std;  // Use the standard namespace

// Function to print a matrix with a title
void printMatrix(const vector<vector<int>>& matrix, const string& name) {
    cout << "\n" << name << ":\n"; // Print the title of the matrix
    for (const auto& row : matrix) { // Iterate through each row of the matrix
        for (int val : row) { // Iterate through each value in the row
            cout << setw(5) << val; // Print the value with formatting
        }
        cout << "\n"; // Move to the next line after printing a row
    }
}

// Function to print a vector with a title
void printVector(const vector<int>& vec, const string& name) {
    cout << "\n" << name << ": "; // Print the title of the vector
    for (int val : vec) { // Iterate through each value in the vector
        cout << setw(5) << val; // Print the value with formatting
    }
    cout << "\n"; // Move to the next line
}

// Function to check if the system is in a safe state
bool isSafeState(const vector<vector<int>>& need, const vector<vector<int>>& allocation, 
                 const vector<int>& available, int n, int m) {
    vector<bool> finish(n, false); // Initialize the finish vector to track completed processes
    vector<int> work = available; // Initialize the work vector with available resources

    int finishedProcesses = 0; // Counter for finished processes
    while (finishedProcesses < n) { // Repeat until all processes are finished
        bool progress = false; // Flag to track if any process progresses in this iteration

        for (int i = 0; i < n; i++) { // Iterate through each process
            if (!finish[i]) { // If the process is not finished
                bool canProceed = true; // Assume the process can proceed
                for (int j = 0; j < m; j++) { // Check each resource type
                    if (need[i][j] > work[j]) { // If the process's need exceeds available resources
                        canProceed = false; // The process cannot proceed
                        break; // Exit the resource check loop
                    }
                }

                if (canProceed) { // If the process can proceed
                    for (int j = 0; j < m; j++) { // Release its allocated resources
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true; // Mark the process as finished
                    progress = true; // Indicate progress in this iteration
                    finishedProcesses++; // Increment the count of finished processes
                }
            }
        }

        if (!progress) { // If no process can proceed
            return false; // The system is not in a safe state
        }
    }
    return true; // The system is in a safe state
}

// Function to display the current state of the matrices and vectors
void displayState(const vector<vector<int>>& max, const vector<vector<int>>& allocation, 
                  const vector<vector<int>>& need, const vector<int>& available) {
    printMatrix(max, "MAX"); // Print the MAX matrix
    printMatrix(allocation, "ALLOCATION"); // Print the ALLOCATION matrix
    printMatrix(need, "NEED"); // Print the NEED matrix
    printVector(available, "AVAILABLE"); // Print the AVAILABLE vector
}

int main() {
    ifstream inFile("banker.txt"); // Open the input file containing initial data
    if (!inFile) { // Check if the file was successfully opened
        cout << "Error opening file.\n"; // Print an error message if the file cannot be opened
        return 1; // Exit the program with an error code
    }

    int n, m; // Number of processes and resource types
    inFile >> n >> m; // Read the number of processes and resource types from the file

    vector<vector<int>> max(n, vector<int>(m)); // Initialize the MAX matrix
    vector<vector<int>> allocation(n, vector<int>(m, 0)); // Initialize the ALLOCATION matrix with 0
    vector<vector<int>> need(n, vector<int>(m)); // Initialize the NEED matrix
    vector<int> available(m); // Initialize the AVAILABLE vector

    // Read the MAX matrix from the file
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            inFile >> max[i][j]; // Read the MAX value
            need[i][j] = max[i][j]; // Initialize NEED as equal to MAX
        }
    }

    // Read the AVAILABLE vector from the file
    for (int j = 0; j < m; j++) {
        inFile >> available[j];
    }

    while (true) {
        cout << "\nEnter process number (0 to " << n - 1 << ") or -1 to exit: ";
        int process;
        cin >> process; // Input the process number

        if (process == -1) { // Exit condition
            cout << "\nFinal Resource Allocation State:\n";
            displayState(max, allocation, need, available); // Display the final state
            break; // Exit the loop
        }

        if (process < 0 || process >= n) { // Check for invalid process number
            cout << "Invalid process number. Try again.\n";
            continue;
        }

        cout << "Enter request vector (" << m << " values): ";
        vector<int> request(m); // Initialize the request vector
        for (int j = 0; j < m; j++) {
            cin >> request[j]; // Input the request values
        }

        // Check if the request is valid
        bool isValid = true;
        for (int j = 0; j < m; j++) {
            if (request[j] > need[process][j] || request[j] > available[j]) {
                isValid = false; // Request exceeds need or available resources
                break;
            }
        }

        if (!isValid) {
            cout << "Request is not valid (exceeds need or available resources).\n";
            displayState(max, allocation, need, available); // Display the state
            continue; // Restart the loop
        }

        // Simulate resource allocation
        vector<vector<int>> tempAlloc = allocation;
        vector<vector<int>> tempNeed = need;
        vector<int> tempAvail = available;

        for (int j = 0; j < m; j++) {
            tempAlloc[process][j] += request[j]; // Allocate requested resources
            tempNeed[process][j] -= request[j]; // Reduce the need
            tempAvail[j] -= request[j]; // Reduce the available resources
        }

        // Check if the system is in a safe state after the allocation
        if (isSafeState(tempNeed, tempAlloc, tempAvail, n, m)) {
            cout << "Request approved: System remains in a safe state.\n";
            allocation = tempAlloc; // Commit the changes
            need = tempNeed;
            available = tempAvail;
        } else {
            cout << "Request denied: System would enter an unsafe state.\n";
        }

        // Display the current state after processing the request
        displayState(max, allocation, need, available);
    }

    return 0; // Exit the program
}


