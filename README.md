# CS3790-Lab5 Chad 

# **Banker's Algorithm Program**

## **Overview**
This program implements the **Banker's Algorithm**, which is a resource allocation and deadlock avoidance algorithm. The program ensures that the system remains in a safe state by evaluating requests for resources and preventing unsafe allocations. 

The program reads the initial system state from a file (`banker.txt`) and interacts with the user to process resource requests for different processes.

---

## **Features**
- Reads system configurations (MAX matrix and AVAILABLE vector) from `banker.txt`.
- Allows interactive simulation of resource requests.
- Validates requests and determines if they can be safely granted.
- Displays the state of the system after every request, including:
  - MAX matrix
  - ALLOCATION matrix
  - NEED matrix
  - AVAILABLE vector
- Ensures the system remains in a safe state by denying unsafe requests.

---

## **Input Files**

### 1. **`Bankers.cpp`**
This is the source code for the program. It contains:
- Functions for printing matrices and vectors.
- Safety algorithm implementation (`isSafeState`).
- Logic for handling user interactions and processing resource requests.

### 2. **`banker.txt`**
This file contains the initial configuration for the system, including:
- Number of processes (`n`) and resource types (`m`).
- **MAX Matrix**: Maximum resource demands for each process.
- **AVAILABLE Vector**: Initially available resources for each type.

### **Example `banker.txt` Format**:
```
5 3
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
10 5 7
```

#### Breakdown:
- **Line 1**: `5 3` (5 processes, 3 resource types)
- **Lines 2–6**: MAX matrix (maximum resource requirements for each process)
- **Line 7**: AVAILABLE vector (available resources for the system)

---

## **Usage Instructions**

### **Compile and Run**
1. Compile the program using a C++ compiler:
   ```
   g++ Bankers.cpp -o Bankers
   ```
2. Run the program:
   ```
   ./Bankers
   ```

### **Interactive Inputs**
- The program will prompt for:
  1. **Process Number**: Enter a number between `0` and `n-1` or `-1` to exit.
  2. **Request Vector**: Enter `m` space-separated integers representing the resource request.

---

## **Program Flow**

1. **Initialization**:
   - Reads `MAX` matrix and `AVAILABLE` vector from `banker.txt`.
   - Initializes `ALLOCATION` matrix (all zeros) and `NEED` matrix (initially equal to MAX).

2. **Request Handling**:
   - Validates the request:
     - Checks if the requested resources exceed the process's NEED or the AVAILABLE resources.
   - Simulates allocation and checks the system's safety:
     - Uses the `isSafeState` function to determine if the system remains safe.
   - Either approves the request (updates ALLOCATION and NEED) or denies it.

3. **State Display**:
   - After processing each request, displays the current system state (MAX, ALLOCATION, NEED, AVAILABLE).

---

## **Example Run**

### **Input**:
- File `banker.txt`:
  ```
  5 3
  7 5 3
  3 2 2
  9 0 2
  2 2 2
  4 3 3
  10 5 7
  ```
- Process `2` requests resources `[3, 0, 2]`.

### **Output**:
```
Enter process number (0 to 4) or -1 to exit: 2
Enter request vector (3 values): 3 0 2

Processing request for Process 2:
Request approved: System remains in a safe state.

MAX:
    7    5    3
    3    2    2
    9    0    2
    2    2    2
    4    3    3
ALLOCATION:
    0    0    0
    0    0    0
    3    0    2
    0    0    0
    0    0    0
NEED:
    7    5    3
    3    2    2
    6    0    0
    2    2    2
    4    3    3
AVAILABLE:
    7    5    5
```

---

## **Error Handling**
- **File Errors**:
  - If `banker.txt` cannot be opened, the program will display:
    ```
    Error opening file.
    ```
- **Invalid Inputs**:
  - Invalid process numbers and resource requests exceeding limits are rejected with a message:
    ```
    Invalid process number. Try again.
    ```
    or
    ```
    Request is not valid (exceeds need or available resources).
    ```

---

## **Key Functions**
- **`printMatrix`**: Displays a matrix with formatting.
- **`printVector`**: Displays a vector with formatting.
- **`isSafeState`**: Simulates resource allocation to check system safety.
- **`displayState`**: Prints the MAX, ALLOCATION, NEED, and AVAILABLE matrices/vectors.
