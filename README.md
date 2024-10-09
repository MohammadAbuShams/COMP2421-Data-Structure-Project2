# Pharmacy Management System

## Overview
This project implements a comprehensive pharmacy management system that maintains medicine information using a Binary Search Tree (BST) and a Hash Table. The system facilitates the storage, retrieval, update, and deletion of medical records in an efficient manner.

## Features
- **Binary Search Tree Operations**:
  - Load medicine data from `Meds.txt` into a BST.
  - Insert, find, update, and delete medicine entries.
  - List medicines alphabetically or by category.
  - Filter medicines by treatment indication and availability.

- **Hash Table Operations**:
  - Load and save medicine data to and from `Pharmacy.txt`.
  - Implement open addressing for collision resolution using the first three characters of the medicine name as the key.
  - Display hash table contents, size, and the hash function used.
  - Handle insertions, deletions, and search operations, including collision tracking.

## Submission Details
- **Deadline**: January 24, 2023
- **Submission File**: `P2_YourStudentID_FirstNameLastName_SectionNo.c`
- **File Naming**: Ensure the file naming follows the convention `[P2_StudentID_FirstNameLastName_SectionNo].c`
- **Include**: Your full name, student ID, and section number at the beginning of the file.

## Project Structure

### Phase 1: Binary Search Tree
1. **Initialization**: Read data from `Meds.txt` and populate the BST.
2. **Medicine Management**: Implement functionalities to add, update, list, and delete medicines based on user interactions.
3. **Saving**: Write the updated medicine data back to `Pharmacy.txt`.

### Phase 2: Hash Table
1. **Setup**: Initialize the hash table from `Pharmacy.txt`.
2. **Operations**: Perform CRUD operations using hashing.
3. **Output**: Provide detailed information about hashing operations and collisions.

## Input/Output Specifications
- **Input File**: `Meds.txt`
- **Output File**: `Pharmacy.txt`

## Usage
- Compile the source file using a C compiler.
- Run the executable and follow on-screen prompts to manage the pharmacy data.

