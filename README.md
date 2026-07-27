# Cooperative-Assignment
# Farmers Cooperative Management System

A complete **C and SQLite** application developed to manage farmer produce deliveries for the **Nyeri Green Farmers Cooperative**.

This project was developed as part of a Programming assignment. It demonstrates the integration of **arrays**, **loops**, **functions**, **SQLite database programming**, **parameterized SQL statements** and a **menu-driven system** for managing cooperative records.

---

# Project Overview

The cooperative collects produce from registered farmers across Nyeri County, including:

- Milk
- Coffee
- Maize
- Potatoes
- Vegetables

Each farmer is assigned a unique farmer number. The system stores delivery records in an SQLite database and processes them using C programs.

The project consists of two major parts:

1. **Core Assignment Implementation (`cooperative.c`)**
   - Implements Questions from the case study.
   - Demonstrates arrays, loops, searching, calculations, SQL queries, database updates, and report generation.

2. **Menu-Driven Cooperative System (`Menu System/menu.c`)**
   - Provides an interactive command-line interface.
   - Retrieves data directly from the SQLite database.
   - Allows users to search, process and manage farmer records.

---

# Features

## Core Assignment

- Display farmer records
- Calculate farmer payments
- Calculate total cooperative payments
- Display pending payments
- Update payment status
- Find highest delivery
- Find lowest payment
- Search for farmers
- Count produce categories
- Calculate payments by produce type
- Identify large deliveries
- Calculate cooperative levy
- Update net payments
- Remove invalid records
- Generate daily summary
- Database programming concepts

---

## Menu System

- Display all farmer deliveries
- Search for a farmer
- Calculate farmer payments
- Display pending payments
- Update payment status
- Display large deliveries
- Generate daily cooperative report
- Save updated records
- Exit the application

---

# Technologies Used

- C Programming Language
- SQLite3
- GCC (MinGW/MSYS2)
- Visual Studio Code
- Git
- GitHub

---

# Project Structure

```text
Cooperative project/
│
├── cooperative.c
├── cooperative.exe
├── ProduceDeliveries.db
├── setup.sql
├── sqlite3.c
├── sqlite3.h
├── README.md
├── .gitignore
│
├── Menu System/
│   ├── menu.c
│   ├── menu.exe
│   └── build/
│
└── build/
```

---

# Database Structure

Database Name:

```
ProduceDeliveries.db
```

Table:

```
ProduceDeliveries
```

Fields:

| Field | Description |
|--------|-------------|
| FarmerNumber | Unique farmer identifier |
| FarmerName | Farmer's full name |
| SubCounty | Farmer's sub-county |
| ProduceType | Type of produce delivered |
| QuantityDelivered | Quantity supplied |
| PricePerUnit | Price per unit (KES) |
| DeliveryDate | Date of delivery |
| PaymentStatus | Paid or Pending |

---

# Programming Concepts Demonstrated

## C Programming

- Arrays
- Loops
- Functions
- Conditional statements
- Searching
- Data processing
- Input validation

## Database Programming

- SQLite integration
- SQL SELECT
- SQL UPDATE
- SQL DELETE
- Prepared statements
- Parameterized queries
- Database connections
- Error handling

---

# Sample Menu

```text
================================
 FARMERS COOPERATIVE SYSTEM
================================

1. Display All Farmer Deliveries
2. Search for a Farmer
3. Calculate Farmer Payments
4. Display Pending Payments
5. Update Payment Status
6. Display Large Deliveries
7. Generate Daily Report
8. Save Updated Records
9. Exit
```

---

# How to Compile

## Main Assignment

```bash
gcc cooperative.c sqlite3.c -o cooperative.exe
```

Run:

```bash
./cooperative.exe
```

---

## Menu System

Navigate into the Menu System folder:

```bash
cd "Menu System"
```

Compile:

```bash
gcc menu.c sqlite3.c -o menu.exe
```

Run:

```bash
./menu.exe
```

---

# Learning Outcomes

This project demonstrates practical application of:

- C programming
- Database programming
- SQLite integration
- SQL operations
- Arrays and loops
- File organization
- Menu-driven application development
- CRUD operations
- Parameterized SQL statements
- Report generation

---

# Future Improvements

Potential enhancements include:

- Add new farmers
- Edit farmer information
- Delete farmer records
- Authentication and user roles
- Export reports to PDF or Excel
- Graphical User Interface (GUI)
- Backup and restore database
- Statistics dashboard

---

# Author

**Daniel Njenga**

BSc Computer Science  
Dedan Kimathi University of Technology (DeKUT)

---

# License

This project was developed for educational purposes as part of a university programming assignment.