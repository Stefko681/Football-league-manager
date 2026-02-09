# Football League Manager ⚽

A console-based C++ application designed to administer football leagues, track match results, and automatically generate live standings based on professional league rules.

## 📋 Overview

This project is a sports league management system that allows users to input teams and match scores. The system automatically calculates points, goal differences, and league positions in real-time using a precise sorting algorithm.

Data is persistent and stored in an external file (`data.txt`), ensuring information is saved between sessions.

## 🚀 Key Features

* **Team Management:**
    * Add new teams (using dynamic memory allocation for names).
    * Edit existing team names.
    * Delete teams from the league.
* **Match Processing:**
    * Input match results (Home vs. Away).
    * Automatic statistical updates (Wins, Draws, Losses, Goals For/Against, Points).
* **Live Standings:**
    * View the league table at any time.
    * **Three-Tier Sorting Algorithm:**
        1.  Highest Points.
        2.  If points are tied -> Better Goal Difference.
        3.  If GD is tied -> More Goals Scored.
* **Statistics:**
    * Detailed lookup for specific team stats.
* **Persistence:**
    * Automatic loading and saving of data to `data.txt`.

## 🛠️ Technical Implementation

This project was built using **Modern C++ (C++20)** to demonstrate proficiency in core computer science concepts:

* **Manual Memory Management:**
    * Usage of dynamic arrays and raw pointers (`new`, `delete[]`) instead of `std::vector` to demonstrate low-level memory control.
    * Custom array resizing logic when adding new teams.
* **Custom String Handling:**
    * Implementation of C-style string manipulation (`char*`) without relying on the `std::string` library.
    * Custom functions for `strLen`, `strCopy`, and `strCmp`.
* **Algorithms:**
    * Implementation of a modified **Selection Sort** to handle complex ranking criteria.
* **Architecture:**
    * Modular design with separation of declarations (`teams.h`) and definitions (`teams.cpp`).

## ⚙️ Build and Run

### Prerequisites
* C++ Compiler (GCC, Clang, or MSVC) supporting C++20.
* CMake (optional).

### Using CMake
1.  Clone the repository:
    ```bash
    git clone [https://github.com/stefko681/football-league-manager.git](https://github.com/stefko681/football-league-manager.git)
    cd football-league-manager
    ```
2.  Create a build directory:
    ```bash
    mkdir build && cd build
    ```
3.  Generate and build:
    ```bash
    cmake ..
    make
    ```
4.  Run the application:
    ```bash
    ./Football_league_manager
    ```

## 📂 Data Structure

The application stores data in a text file using a pipe (`|`) delimiter for names to allow spaces (e.g., "Man City").

**Format:**
```text
TeamName|GamesPlayed Wins Draws Loses GF GA GD Points
```
## 👤 Author

**Stefko Nikolaev**

* **Role:** Software Engineering Student at FMI, Sofia University
* **Focus:** C++, Algorithms, and Data Structures