# Test Case Report — Patient Record Management System

**Project:** Patient Record Management System v1.0  
**Author:** GMS Ganapathi  
**Date:** April 2026  
**Test Type:** Manual Black-Box Testing  
**Compiler:** g++ (MinGW / GCC) with `-std=c++17`

---

## Test Environment Setup

```bash
# Compile
g++ -std=c++17 -Wall -Wextra -o prms main.cpp

# Run
./prms        # Linux / macOS
prms.exe      # Windows
```

> Ensure `patients.csv` does **not** exist before starting TC-01 to verify clean-state behaviour.

---

## Test Cases

| TC | Feature Under Test | Action | Input Sequence | Expected Output | Pass/Fail |
|----|--------------------|--------|----------------|-----------------|-----------|
| TC-01 | Add patient (happy path) | Select 1 → Add | ID=101, Name=Ravi Kumar, Age=34, Diagnosis=Hypertension | `[SUCCESS] Patient record added successfully.` | ✅ Pass |
| TC-02 | Duplicate ID rejection | Select 1 → Add | ID=101 (already exists) | `[ERROR] Patient with ID 101 already exists.` | ✅ Pass |
| TC-03 | Add second patient | Select 1 → Add | ID=102, Name=Anita Shah, Age=28, Diagnosis=Migraine | `[SUCCESS] Patient record added successfully.` | ✅ Pass |
| TC-04 | View all records | Select 2 | — | Table showing both Ravi Kumar & Anita Shah; "Total records: 2" | ✅ Pass |
| TC-05 | Search valid ID | Select 3 | ID=101 | Table row showing Ravi Kumar, 34, Hypertension | ✅ Pass |
| TC-06 | Search invalid ID | Select 3 | ID=999 | `[NOT FOUND] No patient with ID 999.` | ✅ Pass |
| TC-07 | Update diagnosis | Select 4 | ID=101, New=Diabetes Type 2 | `[SUCCESS] Diagnosis updated successfully.` | ✅ Pass |
| TC-08 | Verify update persisted | Select 3 | ID=101 | Diagnosis shows "Diabetes Type 2" | ✅ Pass |
| TC-09 | Delete patient (confirm yes) | Select 5 | ID=102, confirm=y | `[SUCCESS] Patient record deleted successfully.` | ✅ Pass |
| TC-10 | Delete patient (confirm no) | Select 5 | ID=101, confirm=n | `[CANCELLED] Delete operation aborted.` | ✅ Pass |
| TC-11 | Delete non-existent record | Select 5 | ID=999 | `[NOT FOUND] No patient with ID 999.` | ✅ Pass |
| TC-12 | Persistence across sessions | Exit (0) → Restart app | — | Reloaded record for ID=101 (Ravi Kumar) visible in View All | ✅ Pass |
| TC-13 | Empty state — view all | Fresh run, no CSV | Select 2 | `No records found.` | ✅ Pass |
| TC-14 | Invalid menu input (letter) | Enter `abc` at menu | — | `[ERROR] Invalid input. Please enter a number.` — no crash | ✅ Pass |
| TC-15 | Invalid age input | Select 1 → Add | ID=201, Name=Test, Age=abc | `[ERROR] Invalid age. Must be between 1 and 150.` | ✅ Pass |
| TC-16 | Age boundary (0) | Select 1 → Add | ID=202, Age=0 | `[ERROR] Invalid age. Must be between 1 and 150.` | ✅ Pass |
| TC-17 | Age boundary (150) | Select 1 → Add | ID=203, Age=150 | `[SUCCESS] Patient record added successfully.` | ✅ Pass |
| TC-18 | Empty name input | Select 1 → Add | ID=204, Name=(blank) | `[ERROR] Name cannot be empty.` | ✅ Pass |
| TC-19 | Empty diagnosis input | Select 1 → Add | ID=205, Diagnosis=(blank) | `[ERROR] Diagnosis cannot be empty.` | ✅ Pass |
| TC-20 | Out-of-range menu choice | Enter 9 at menu | — | `[ERROR] Invalid choice. Enter 0-5.` | ✅ Pass |

---

## Requirement Traceability Matrix

| Requirement ID | Description | Covered By |
|----------------|-------------|------------|
| FR-01 | Add patient | TC-01, TC-02, TC-15, TC-16, TC-17, TC-18, TC-19 |
| FR-02 | View all records | TC-04, TC-13 |
| FR-03 | Search by ID | TC-05, TC-06 |
| FR-04 | Update diagnosis | TC-07, TC-08 |
| FR-05 | Delete patient | TC-09, TC-10, TC-11 |
| FR-06 | Persist to CSV | TC-07 (file written after update) |
| FR-07 | Load on startup | TC-12 |
| NFR-03 | Graceful invalid input | TC-14, TC-15, TC-16, TC-18, TC-19, TC-20 |

---

## Test Summary

| Total TCs | Passed | Failed | Pass Rate |
|-----------|--------|--------|-----------|
| 20 | 20 | 0 | 100% |

---

## Observations & Notes

- **Commas in diagnosis:** The CSV parser uses `getline(ss, p.diagnosis)` (no delimiter) so the diagnosis field can contain commas without corrupting the record.
- **cin recovery:** After any failed integer extraction, `clearInputBuffer()` resets the stream so subsequent menu iterations work correctly.
- **Confirmation prompt on delete (TC-10):** Acts as a safety guard against accidental data loss.
- **NFR-01 (O(n) search):** `findIndexById()` performs a linear scan — acceptable for small clinic datasets. For large-scale use, a `std::unordered_map` would provide O(1) average lookup.
