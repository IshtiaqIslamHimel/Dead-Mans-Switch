# Dead Man’s Switch (C++)

A simple C++ program that acts as a **dead man’s switch**:  
If the program is not run for a set number of days, it **deletes a target folder** automatically.

---

## Features

- Saves the last run timestamp in a file.
- Checks how many days have passed since the last run.
- If the threshold is exceeded (default 3 days), it deletes a target folder.
- Password-protected option to extend/reset the timer.
- Intended to be added to Windows startup for automatic checks.

---

## How It Works

1. On first run, saves the current date/time.
2. On each subsequent run, compares current date with last saved timestamp.
3. If more than allowed days have passed:
    - Deletes the target folder.
    - Prompts user to enter a password to extend the timer.
4. If within the allowed period:
    - Updates the timestamp.

---

## Setup & Usage

### Requirements
- C++17 compatible compiler (for `std::filesystem`)
- Windows OS (tested on Windows 10/11)

### Steps
1. Clone or download this repository.
2. Compile the program located in `src/dead_mans_switch.cpp` using a C++17 or newer compiler.  
   Example (using g++):  
   ```bash
   g++ -std=c++17 src/dead_mans_switch.cpp -o DeadMansSwitch.exe
