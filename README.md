# Patient Record Management System v1.0

A lightweight, file-persistent CLI application for managing patient records in small healthcare clinics — built entirely in **C++ with no external libraries**.

---

## Features

| Operation | Description |
|-----------|-------------|
| ➕ Add Patient | Create a new record with ID, Name, Age & Diagnosis |
| 📋 View All | Display all records in a formatted table |
| 🔍 Search | Find a patient instantly by their numeric ID |
| ✏️ Update | Modify a patient's diagnosis by ID |
| 🗑️ Delete | Remove a record by ID (with confirmation) |
| 💾 Persist | All changes survive app restarts via `patients.csv` |

---

## Quick Start

### Prerequisites
- **g++** (GCC 7+) or **MSVC** with C++17 support
- Any terminal — PowerShell, CMD, bash, zsh

### Build

```bash
# Linux / macOS
g++ -std=c++17 -Wall -Wextra -o prms main.cpp

# Windows (MinGW)
g++ -std=c++17 -Wall -Wextra -o prms.exe main.cpp

# Windows (MSVC)
cl /EHsc /std:c++17 main.cpp /Fe:prms.exe
```

### Run

```bash
./prms        # Linux / macOS
prms.exe      # Windows
```

---

## Usage

On launch, the application displays the main menu:

```
=============================
 Patient Record Manager v1.0
=============================
  1. Add Patient
  2. View All Patients
  3. Search by ID
  4. Update Diagnosis
  5. Delete Patient
  0. Exit
------------------------------
Enter choice:
```

Enter the number corresponding to your desired operation.

### Example Session

```
Enter choice: 1

--- Add Patient ---
Enter ID   : 101
Enter Name : Ravi Kumar
Enter Age  : 34
Enter Diagnosis: Hypertension
[SUCCESS] Patient record added successfully.

Enter choice: 2

--- All Patient Records ---

ID      Name                  Age   Diagnosis
-------------------------------------------------------------
101     Ravi Kumar            34    Hypertension

Total records: 1
```

---

## Data Storage

Records are stored in **`patients.csv`** (created automatically on first add):

```
id,name,age,diagnosis
101,Ravi Kumar,34,Hypertension
102,Anita Shah,28,Migraine
```

> The file is saved immediately after every Add / Update / Delete operation.

---

## Project Structure

```
patient-record-system/
├── main.cpp        ← Full source code
├── patients.csv    ← Auto-generated on first patient add
├── SRS.md          ← Software Requirements Specification
├── TESTING.md      ← Test case report (20 test cases, 100% pass)
└── README.md       ← This file
```

---

## SDLC Phases Covered

| Phase | Artifact |
|-------|----------|
| Requirements | `SRS.md` — Functional & Non-Functional Requirements |
| Design | Module breakdown, data model, CLI flow (in `SRS.md`) |
| Implementation | `main.cpp` — Modular C++ source |
| Testing | `TESTING.md` — 20 manual black-box test cases |
| Maintenance | CSV persistence + input validation |

---

## Input Validation

- **Duplicate IDs** are rejected at add-time
- **Non-integer input** at any numeric prompt is caught without crashing
- **Empty strings** for Name and Diagnosis are rejected
- **Age** must be in the range 1–150
- **Delete** requires explicit `y`/`Y` confirmation

---

## Commit History

```
git commit -m "Initial project setup and SRS documentation"
git commit -m "Add data model, file I/O: loadFromFile and saveToFile"
git commit -m "Implement CRUD: add, display, search operations"
git commit -m "Implement update and delete with input validation"
git commit -m "Add test cases and TESTING.md"
git commit -m "Final cleanup, comments, and README"
```

---

## Author

**GMS Ganapathi** — April 2026  
Language: C++ (Standard Library Only) | Type: CLI Application
