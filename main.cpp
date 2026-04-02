// ================================================================
//  Patient Record Management System v1.0
//  Author  : GMS Ganapathi
//  Language: C++ (Standard Library Only)
//  Storage : patients.csv (flat-file persistence)
// ================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// ─── Data Model ───────────────────────────────────────────────────────────────
struct Patient {
    int    id;
    string name;
    int    age;
    string diagnosis;
};

// ─── Globals ──────────────────────────────────────────────────────────────────
const string FILE_NAME = "patients.csv";
vector<Patient> records;

// ─── Forward Declarations ─────────────────────────────────────────────────────
void loadFromFile();
void saveToFile();
int  findIndexById(int id);
bool idExists(int id);
void printHeader();
void printPatient(const Patient& p);
void addPatient();
void displayAll();
void searchPatient();
void updateDiagnosis();
void deletePatient();

// ─── File I/O ─────────────────────────────────────────────────────────────────

/**
 * loadFromFile()
 * Reads the CSV file into the global records vector on startup.
 * Skips the header line. Silently returns if file does not exist yet.
 */
void loadFromFile() {
    ifstream file(FILE_NAME);
    if (!file.is_open()) return;   // First run — no file yet

    string line;
    getline(file, line);           // Skip CSV header row

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string token;
        Patient p;

        getline(ss, token, ',');   p.id  = stoi(token);
        getline(ss, p.name, ',');
        getline(ss, token, ',');   p.age = stoi(token);
        getline(ss, p.diagnosis);  // rest of line (allows commas in diagnosis)

        records.push_back(p);
    }
    file.close();
}

/**
 * saveToFile()
 * Overwrites the CSV file with the current state of the records vector.
 * Called after every mutating operation (add / update / delete).
 */
void saveToFile() {
    ofstream file(FILE_NAME);
    file << "id,name,age,diagnosis\n";
    for (const auto& p : records) {
        file << p.id << ","
             << p.name << ","
             << p.age  << ","
             << p.diagnosis << "\n";
    }
    file.close();
}

// ─── Utility Helpers ──────────────────────────────────────────────────────────

/** Returns the index of the patient with the given ID, or -1 if not found. */
int findIndexById(int id) {
    for (int i = 0; i < static_cast<int>(records.size()); ++i)
        if (records[i].id == id) return i;
    return -1;
}

/** Returns true if a patient with the given ID already exists. */
bool idExists(int id) {
    return findIndexById(id) != -1;
}

/** Prints the formatted table header. */
void printHeader() {
    cout << "\n"
         << left
         << setw(8)  << "ID"
         << setw(22) << "Name"
         << setw(6)  << "Age"
         << setw(25) << "Diagnosis"
         << "\n"
         << string(61, '-') << "\n";
}

/** Prints a single patient row in the formatted table. */
void printPatient(const Patient& p) {
    cout << left
         << setw(8)  << p.id
         << setw(22) << p.name
         << setw(6)  << p.age
         << setw(25) << p.diagnosis
         << "\n";
}

/** Clears the input buffer after a failed cin extraction. */
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ─── CRUD Operations ──────────────────────────────────────────────────────────

/**
 * addPatient()  [FR-01]
 * Prompts the user for a new patient record and appends it after
 * validating that the chosen ID is unique.
 */
void addPatient() {
    Patient p;
    cout << "\n--- Add Patient ---\n";

    // Validate integer input for ID
    cout << "Enter ID   : ";
    if (!(cin >> p.id)) {
        cout << "[ERROR] Invalid ID. Must be a positive integer.\n";
        clearInputBuffer();
        return;
    }

    if (idExists(p.id)) {
        cout << "[ERROR] Patient with ID " << p.id << " already exists.\n";
        return;
    }

    clearInputBuffer();   // flush newline before getline

    cout << "Enter Name : ";
    getline(cin, p.name);
    if (p.name.empty()) {
        cout << "[ERROR] Name cannot be empty.\n";
        return;
    }

    cout << "Enter Age  : ";
    if (!(cin >> p.age) || p.age <= 0 || p.age > 150) {
        cout << "[ERROR] Invalid age. Must be between 1 and 150.\n";
        clearInputBuffer();
        return;
    }

    clearInputBuffer();
    cout << "Enter Diagnosis: ";
    getline(cin, p.diagnosis);
    if (p.diagnosis.empty()) {
        cout << "[ERROR] Diagnosis cannot be empty.\n";
        return;
    }

    records.push_back(p);
    saveToFile();
    cout << "[SUCCESS] Patient record added successfully.\n";
}

/**
 * displayAll()  [FR-02]
 * Prints all stored patient records in a formatted table.
 */
void displayAll() {
    cout << "\n--- All Patient Records ---\n";
    if (records.empty()) {
        cout << "No records found.\n";
        return;
    }
    printHeader();
    for (const auto& p : records)
        printPatient(p);
    cout << "\nTotal records: " << records.size() << "\n";
}

/**
 * searchPatient()  [FR-03]
 * Finds and displays a single patient record by ID.
 */
void searchPatient() {
    int id;
    cout << "\n--- Search Patient ---\n";
    cout << "Enter Patient ID: ";
    if (!(cin >> id)) {
        cout << "[ERROR] Invalid input. ID must be an integer.\n";
        clearInputBuffer();
        return;
    }

    int idx = findIndexById(id);
    if (idx == -1) {
        cout << "[NOT FOUND] No patient with ID " << id << ".\n";
        return;
    }
    printHeader();
    printPatient(records[idx]);
}

/**
 * updateDiagnosis()  [FR-04]
 * Updates the diagnosis field of an existing patient record by ID.
 */
void updateDiagnosis() {
    int id;
    cout << "\n--- Update Diagnosis ---\n";
    cout << "Enter Patient ID: ";
    if (!(cin >> id)) {
        cout << "[ERROR] Invalid input. ID must be an integer.\n";
        clearInputBuffer();
        return;
    }

    int idx = findIndexById(id);
    if (idx == -1) {
        cout << "[NOT FOUND] No patient with ID " << id << ".\n";
        return;
    }

    clearInputBuffer();
    cout << "Current Diagnosis : " << records[idx].diagnosis << "\n";
    cout << "New Diagnosis     : ";
    string newDiag;
    getline(cin, newDiag);
    if (newDiag.empty()) {
        cout << "[ERROR] Diagnosis cannot be empty.\n";
        return;
    }

    records[idx].diagnosis = newDiag;
    saveToFile();
    cout << "[SUCCESS] Diagnosis updated successfully.\n";
}

/**
 * deletePatient()  [FR-05]
 * Removes a patient record permanently by ID.
 */
void deletePatient() {
    int id;
    cout << "\n--- Delete Patient ---\n";
    cout << "Enter Patient ID: ";
    if (!(cin >> id)) {
        cout << "[ERROR] Invalid input. ID must be an integer.\n";
        clearInputBuffer();
        return;
    }

    int idx = findIndexById(id);
    if (idx == -1) {
        cout << "[NOT FOUND] No patient with ID " << id << ".\n";
        return;
    }

    cout << "Are you sure you want to delete patient '"
         << records[idx].name << "' (ID " << id << ")? [y/N]: ";
    char confirm;
    cin >> confirm;
    if (confirm != 'y' && confirm != 'Y') {
        cout << "[CANCELLED] Delete operation aborted.\n";
        return;
    }

    records.erase(records.begin() + idx);
    saveToFile();
    cout << "[SUCCESS] Patient record deleted successfully.\n";
}

// ─── Main ─────────────────────────────────────────────────────────────────────
int main() {
    loadFromFile();   // FR-07: restore persisted records on startup

    int choice;
    do {
        cout << "\n=============================\n";
        cout << " Patient Record Manager v1.0\n";
        cout << "=============================\n";
        cout << "  1. Add Patient\n";
        cout << "  2. View All Patients\n";
        cout << "  3. Search by ID\n";
        cout << "  4. Update Diagnosis\n";
        cout << "  5. Delete Patient\n";
        cout << "  0. Exit\n";
        cout << "------------------------------\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "[ERROR] Invalid input. Please enter a number.\n";
            clearInputBuffer();
            choice = -1;   // trigger default case
            continue;
        }

        switch (choice) {
            case 1: addPatient();      break;
            case 2: displayAll();      break;
            case 3: searchPatient();   break;
            case 4: updateDiagnosis(); break;
            case 5: deletePatient();   break;
            case 0: cout << "\nExiting. Goodbye!\n"; break;
            default: cout << "[ERROR] Invalid choice. Enter 0-5.\n";
        }
    } while (choice != 0);

    return 0;
}
