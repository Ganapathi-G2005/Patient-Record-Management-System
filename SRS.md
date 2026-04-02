# Software Requirements Specification (SRS)

**Project:** Patient Record Management System  
**Version:** 1.0  
**Author:** GMS Ganapathi  
**Date:** April 2026  
**Language:** C++ (Standard Library Only)  
**Type:** CLI Application

---

## 1. Introduction

### 1.1 Purpose
This document specifies the software requirements for the **Patient Record Management System (PRMS)** — a command-line application designed to help small healthcare clinics manage patient records through their complete lifecycle (Create, Read, Update, Delete) with persistent file-based storage.

### 1.2 Scope
The PRMS is a standalone CLI tool written in C++ that:
- Stores patient records in a flat CSV file (`patients.csv`)
- Provides CRUD operations via an interactive menu
- Persists data across application sessions
- Handles invalid user inputs gracefully

### 1.3 Definitions & Acronyms
| Term | Definition |
|------|-----------|
| PRMS | Patient Record Management System |
| CRUD | Create, Read, Update, Delete |
| CLI | Command-Line Interface |
| CSV | Comma-Separated Values |
| FR | Functional Requirement |
| NFR | Non-Functional Requirement |

---

## 2. Overall Description

### 2.1 Product Perspective
PRMS is a self-contained application with no external library dependencies. It reads from and writes to a single CSV file to maintain persistent state between sessions.

### 2.2 User Classes and Characteristics
- **Primary User:** Healthcare staff (receptionists, administrators) with basic computer literacy
- No programming knowledge required

### 2.3 Operating Environment
- **Platform:** Windows / Linux CLI
- **Language:** C++17 (compiles with `g++` or `cl`)
- **Storage:** Local filesystem

### 2.4 Assumptions and Dependencies
- The `patients.csv` file resides in the same directory as the executable
- The system assumes valid UTF-8 text input from the user
- No concurrent access (single-user, single-process model)

---

## 3. Functional Requirements

| ID | Requirement |
|----|-------------|
| FR-01 | System shall allow adding a new patient record with ID, Name, Age, and Diagnosis |
| FR-02 | System shall display all existing patient records in a formatted table |
| FR-03 | System shall search for a patient by unique numeric ID |
| FR-04 | System shall update the diagnosis of an existing patient identified by ID |
| FR-05 | System shall delete a patient record by ID with a confirmation prompt |
| FR-06 | System shall persist all records to a CSV file after every mutating operation |
| FR-07 | System shall load existing records from file on application startup |

---

## 4. Non-Functional Requirements

| ID | Requirement |
|----|-------------|
| NFR-01 | Search operation shall complete in O(n) time (linear scan over records vector) |
| NFR-02 | Data shall not be lost between sessions (file written on every mutation) |
| NFR-03 | System shall handle invalid inputs gracefully without crashing (cin validation + error messages) |
| NFR-04 | Code shall be modular — one function per operation with clear responsibilities |
| NFR-05 | All error messages shall be prefixed with `[ERROR]` or `[NOT FOUND]` for clarity |
| NFR-06 | Success messages shall be prefixed with `[SUCCESS]` |

---

## 5. Data Model

```cpp
struct Patient {
    int    id;          // Unique positive integer identifier
    string name;        // Full patient name (non-empty)
    int    age;         // Age in years (1–150)
    string diagnosis;   // Medical condition description (non-empty)
};
```

**CSV File Format (`patients.csv`):**

```
id,name,age,diagnosis
101,Ravi Kumar,34,Hypertension
102,Anita Shah,28,Migraine
```

---

## 6. Module Breakdown

```
main()
├── loadFromFile()       → FR-07: reads CSV into vector on startup
├── saveToFile()         → FR-06: writes entire vector to CSV
├── addPatient()         → FR-01: appends new record after ID-uniqueness check
├── displayAll()         → FR-02: prints all records in table format
├── searchPatient()      → FR-03: finds record by ID (O(n) scan)
├── updateDiagnosis()    → FR-04: modifies diagnosis field by ID
├── deletePatient()      → FR-05: removes record by ID with confirmation
├── findIndexById()      → Utility: linear search, returns index or -1
├── idExists()           → Utility: boolean wrapper around findIndexById()
├── printHeader()        → Utility: prints formatted table header
├── printPatient()       → Utility: prints a single patient row
└── clearInputBuffer()   → Utility: resets cin after invalid input
```

---

## 7. CLI Menu Flow

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

---

## 8. Input Validation Rules

| Field | Validation Rule |
|-------|----------------|
| Patient ID | Must be a positive integer; duplicate IDs rejected |
| Name | Non-empty string |
| Age | Integer in range [1, 150] |
| Diagnosis | Non-empty string |
| Menu Choice | Integer in range [0, 5]; non-integers handled without crash |
| Delete confirm | Must enter `y` or `Y` to proceed |

---

## 9. Constraints

- **Language:** C++ (no external libraries)
- **Storage:** Flat CSV file (`patients.csv`)
- **Platform:** Windows / Linux CLI
- **Concurrency:** Single-user; no locking mechanism

---

## 10. Revision History

| Version | Date | Author | Changes |
|---------|------|--------|---------|
| 1.0 | April 2026 | GMS Ganapathi | Initial release |
