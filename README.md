# CS3790-Lab5 Chad 

# **Banker's Algorithm Program**

## **Overview**
This program implements the **Banker's Algorithm**, a resource allocation and deadlock avoidance algorithm. It determines whether a system is in a safe state when processes request resources. The program reads resource allocation and requirements from an input file (`banker.txt`) and allows the user to simulate resource requests interactively.

---

## **Features**
- Reads initial system state (MAX matrix, AVAILABLE vector) from a file.
- Validates resource requests based on process needs and available resources.
- Simulates resource allocation and checks the system's safety after every request.
- Displays the current state of the system at every step (MAX, ALLOCATION, NEED, AVAILABLE).
- Prevents unsafe states by denying requests that would lead to deadlocks.

---

## **How It Works**
1. **Input Data**:
   - The program reads the number of processes (`n`) and resource types (`m`) from a file (`banker.txt`).
   - It initializes:
     - **MAX Matrix**: Maximum resource demand for each process.
     - **AVAILABLE Vector**: Total available resources for each type.
     - **ALLOCATION Matrix**: Resources currently allocated to each process (starts at zero).
     - **NEED Matrix**: Remaining resource needs for each process (initially equal to MAX).

2. **Interactive Requests**:
   - The user specifies a process and its resource request vector.
   - The program:
     - Validates if the request is within the process's needs and the system's available resources.
     - Simulates the allocation to check if the system remains in a safe state.
     - Approves or denies the request based on safety.

3. **System State**:
   - Displays matrices and vectors:
     - **MAX**, **ALLOCATION**, **NEED**, and **AVAILABLE**.
   - Provides feedback on approved or denied requests.

---

## **Input File Format (`banker.txt`)**
1. The first line specifies the number of processes (`n`) and resource types (`m`).
2. The next `n` lines represent the MAX matrix (one line per process).
3. The final line contains the AVAILABLE vector.

### **Example Input (`banker.txt`):**
```
3 3
7 5 3
3 2 2
9 0 2
3 3 2
```

- **Processes:** 3
- **Resource Types:** 3
- **MAX Matrix:**
  ```
  7 5 3
  3 2 2
  9 0 2
  ```
- **AVAILABLE Vector:**
  ```
  3 3 2
  ```

---

## **Usage Instructions**
1. **Compile and Run**:
   - Compile the program:
     ```
     g++ Bankers.cpp -o Bankers
     ```
   - Run the program:
     ```
     ./Bankers
     ```

2. **Interactive Inputs**:
   - Enter a process number (e.g., `0`, `1`, `2`) or `-1` to exit.
   - Provide a request vector with `m` resource values (e.g., `1 0 2`).

3. **Output**:
   - The program will validate the request and:
     - Approve and update the system state if safe.
     - Deny the request if it leads to an unsafe state.
   - Displays the current system state after every request.

---

## **Key Functions**
- **`printMatrix`**: Displays a matrix with a title.
- **`printVector`**: Displays a vector with a title.
- **`isSafeState`**: Determines if the system is in a safe state after a simulated allocation.
- **`displayState`**: Prints the MAX, ALLOCATION, NEED matrices, and the AVAILABLE vector.

---

## **Example Run**
### **Input**:
- Process `1` requests resources `[1, 0, 2]`.

### **Output**:
```
Processing request for Process 1:
Request Vector:   1   0   2
Request approved: System remains in a safe state.

MAX:
    7    5    3
    3    2    2
    9    0    2
ALLOCATION:
    0    0    0
    1    0    2
    0    0    0
NEED:
    7    5    3
    2    2    0
    9    0    2
AVAILABLE:
    2    3    0
```

---

## **Error Handling**
- **File Errors**: Displays an error message if the input file cannot be opened.
- **Invalid Input**: Rejects invalid process numbers and resource requests exceeding needs or availability.
