 
Institution: DEDAN KIMATHI UNIVERSITY OF TECHNOLOGY
School: SCHOOL OF COMPUTER SCIENCE AND IT
Department: DEPARTMENT OF COMPUTER SCIENCE
Unit Code: CCS 2105
Unit Name: PROGRAMMING LANGUAGES
Case Study: Managing Farmer Produce Records in a Kenyan Cooperative

MEMBERS:
NAME						REGISTRATION NUMBER
Daniel Kinyanjui Njenga				C026-01-0911/2025
Prince Lemayian Riamet				C026-01-0972/2025
Carren Cherotich Ngeno				C026-01-2560/2025



 Table of Contents
1.	Introduction	4
1.1 Background	4
1.2 General Objective	4
1.3 Scope of the Project	5
1.4 Significance of the Project	5
2.	DEVELOPMENT ENVIRONMENT	6
2.1 Development Tools	6
2.2 Programming Language	6
2.3 Database	6
2.4 Project Structure	6
3.	DATABASE DESIGN	7
3.1 Database Overview	7
3.2 Database Table	7
3.3 Table Creation	7
3.4 Database Operations	8
4.	PROGRAM IMPLEMENTATION	8
4.1 Question 1: Display Farmer Records	8
4.2 Question 2: Calculate Farmer Payments	8
4.3 Question 3: Calculate Total Cooperative Payment	9
4.4 Question 4: Display Pending Payments	9
4.5 Question 5: Update Payment Status	9
4.6 Question 6: Search Farmer Records	9
4.7 Question 7: Count Farmers by Produce Category	10
4.8 Question 8: Calculate Payments by Produce Type	10
4.9 Question 9: Identify Large Deliveries	10
4.10 Question 10: Calculate Cooperative Levy	10
4.11 Question 11: Calculate Net Payment	11
4.12 Question 12: Database Integration	11
4.13 Question 13: Delete Invalid Records	11
4.14 Question 14: Generate Daily Summary	11
4.15 Question 15: Menu-Driven System	12
5.	EXTENDED PROGRAMMING TASK	13
5.1 Overview	13
5.2 Features Implemented	14
5.3 Database Integration	14
5.4 Benefits of the Menu System	14
6.	CHALLENGES, LESSONS LEARNT AND CONCLUSION	15
6.1 Challenges Encountered	15
6.2 Lessons Learned	15
6.3 Conclusion	15

Managing Farmer Produce Records in a Kenyan Cooperative
1.	Introduction
1.1 Background
Nyeri Green Farmers Cooperative is a farmers' organization responsible for collecting, processing and marketing agricultural produce from registered farmers across Nyeri County. The cooperative handles various types of produce, including milk, coffee, maize, potatoes and vegetables. Every farmer is assigned a unique farmer number, which is used to identify their delivery records and payment information.
This project implements such a system using the C programming language and the SQLite relational database management system. The program demonstrates how arrays, loops, functions, SQL statements and database connectivity can be integrated to solve a real-world record management problem.


1.2 General Objective
To design and implement a database-driven cooperative management system that stores, processes and manages farmer produce delivery records using the C programming language and SQLite.
The project aims to:
•	Display farmer delivery records retrieved from the database. 
•	Calculate payments due to individual farmers. 
•	Compute the cooperative's total payment obligation. 
•	Identify farmers with pending payments. 
•	Update payment status using parameterized SQL statements. 
•	Search for farmer records using farmer numbers. 
•	Count farmers according to produce categories. 
•	Calculate payments by produce type. 
•	Identify large produce deliveries. 
•	Compute cooperative levies and net payments. 
•	Generate daily management reports. 
•	Demonstrate the integration of C programming with SQLite databases. 
•	Develop a menu-driven application for managing cooperative records. 

1.3 Scope of the Project
The project focuses on managing produce deliveries for registered farmers. It covers storing delivery records in an SQLite database, processing those records using C programs, updating payment information, searching for farmer records and generating management reports.
The system is implemented as a command-line application and does not include features such as user authentication, networking or graphical user interfaces.

1.4 Significance of the Project
The project demonstrates practical application of programming and database concepts learned during the course. It illustrates how database systems can be integrated with C programs to automate data processing tasks.
The project also provides experience in:
•	Database programming. 
•	SQL query execution. 
•	Prepared statements. 
•	Parameterized SQL queries. 
•	Array processing. 
•	Loop-based algorithms. 
•	File organization. 
•	Menu-driven software development. 
•	Version control using Git and GitHub.

2.	DEVELOPMENT ENVIRONMENT
2.1 Development Tools
The project was developed using the following software tools:
Tool	Purpose
Visual Studio Code	Writing and editing the source code
GCC Compiler (MinGW/MSYS2)	Compiling the C programs
SQLite3	Managing the project database
Git	Version control during development
GitHub	Online repository for source code backup and collaboration

2.2 Programming Language
The project was implemented using the C programming language. C was chosen because it provides efficient memory management, supports structured programming and allows integration with the SQLite library for database operations.

2.3 Database
The application uses SQLite, a lightweight relational database management system. SQLite stores all farmer delivery records in a single database file (ProduceDeliveries.db) and supports SQL operations such as SELECT, UPDATE and DELETE through parameterized statements.

2.4 Project Structure
The project was organized into the following main components:
•	cooperative.c – Implements Questions 1–16 of the assignment. 
•	menu.c – Implements the menu-driven cooperative management system. 
•	ProduceDeliveries.db – Stores farmer delivery records. 
•	setup.sql – Contains the SQL script used to create the database and table. 
•	sqlite3.c and sqlite3.h – SQLite library files used for database connectivity.

3.	DATABASE DESIGN
3.1 Database Overview
The system uses an SQLite database named ProduceDeliveries.db to store information about farmer produce deliveries. SQLite was selected because it is lightweight, easy to integrate with C programs and does not require a separate database server.

3.2 Database Table
The database contains one main table named ProduceDeliveries, which stores all farmer delivery records.
Field	Data Type	     Description
FarmerNumber	INTEGER	     Unique identifier for each farmer (Primary Key)
FarmerName	TEXT	     Name of the farmer
SubCounty	TEXT	     Farmer's sub-county
ProduceType	TEXT	     Type of produce delivered
QuantityDelivered	INTEGER	    Quantity of produce delivered
PricePerUnit	REAL	    Price per unit of produce
DeliveryDate	TEXT	   Date of delivery
PaymentStatus	TEXT	   Payment status (Paid or Pending)

3.3 Table Creation
The following SQL statement was used to create the ProduceDeliveries table:
CREATE TABLE ProduceDeliveries (
    FarmerNumber INTEGER PRIMARY KEY,
    FarmerName TEXT NOT NULL,
    SubCounty TEXT NOT NULL,
    ProduceType TEXT NOT NULL,
    QuantityDelivered INTEGER NOT NULL,
    PricePerUnit REAL NOT NULL,
    DeliveryDate TEXT NOT NULL,
    PaymentStatus TEXT NOT NULL
);

3.4 Database Operations
The application performs the following database operations:
•	SELECT – Retrieve farmer records and generate reports. 
•	UPDATE – Modify payment status and payment information. 
•	DELETE – Remove invalid records after user confirmation. 
•	Prepared Statements – Execute parameterized SQL queries securely. 

4.	 PROGRAM IMPLEMENTATION
4.1 Question 1: Display Farmer Records
Objective
To display all farmer delivery records stored in the system.
Implementation Summary
Farmer records were stored in arrays and displayed using a loop. Each record included the farmer number, name, sub-county, produce type, quantity delivered, price per unit, delivery date and payment status.

4.2 Question 2: Calculate Farmer Payments
Objective
To calculate the payment due to each farmer.
Implementation Summary
The payment for each farmer was calculated using the formula:
Payment = Quantity Delivered × Price Per Unit
The calculated values were displayed for all farmers.

4.3 Question 3: Calculate Total Cooperative Payment
Objective
To determine the total amount payable to all farmers.
Implementation Summary
A loop was used to calculate each farmer's payment and accumulate the total amount payable by the cooperative.

4.4 Question 4: Display Pending Payments
Objective
To identify farmers whose payments were still pending.
Implementation Summary
The program compared each farmer's payment status with the value "Pending" and displayed only the matching records.

4.5 Question 5: Update Payment Status
Objective
To update the payment status of farmers whose payments were below KES 10,000.
Implementation Summary
Prepared SQL statements were used to update payment statuses in the SQLite database, demonstrating the use of parameterized queries.

4.6 Question 6: Search Farmer Records
Objective
To search for a farmer using the farmer number.
Implementation Summary
A linear search algorithm was implemented to locate the requested farmer and display the associated details.

4.7 Question 7: Count Farmers by Produce Category
Objective
To determine the number of farmers delivering each produce type.
Implementation Summary
Nested loops were used to compare produce types and count the number of farmers in each category.

4.8 Question 8: Calculate Payments by Produce Type
Objective
To calculate the total payments made for each produce category.
Implementation Summary
The program calculated payments for each produce category by multiplying quantities by prices and summing the values.

4.9 Question 9: Identify Large Deliveries
Objective
To identify deliveries whose quantity exceeded the specified threshold.
Implementation Summary
Conditional statements were used to filter and display deliveries greater than the specified quantity.

4.10 Question 10: Calculate Cooperative Levy
Objective
To calculate the cooperative levy deducted from each farmer's payment.
Implementation Summary
The cooperative levy was calculated as a percentage of each farmer's gross payment and displayed together with the payment details.

4.11 Question 11: Calculate Net Payment
Objective
To determine the amount payable after deducting the cooperative levy.
Implementation Summary
Net payment values were calculated and displayed for every farmer after deducting the cooperative levy.

4.12 Question 12: Database Integration
Objective
To store and retrieve farmer records using SQLite.
Implementation Summary
The SQLite library was integrated with the C program to enable persistent storage and retrieval of farmer records using SQL statements.

4.13 Question 13: Delete Invalid Records
Objective
To identify and remove invalid records from the database.
Implementation Summary
Prepared DELETE statements were used to safely remove invalid records after obtaining user confirmation.

4.14 Question 14: Generate Daily Summary
Objective
To produce a summary of the day's cooperative activities.
Implementation Summary
The report included total deliveries, total payments, paid and pending farmers, highest delivery and highest payment.

4.15 Question 15: Menu-Driven System
Objective
To provide an interactive interface for managing cooperative records.
Implementation Summary
A menu-driven application was developed using a do...while loop and switch statement. The menu interacted directly with the SQLite database to perform various operations.

4.16 Question 16: Version Control
Objective
To manage the project using Git and GitHub.
Implementation Summary
Git was used for version control throughout development, while GitHub served as the remote repository for backup and collaboration.


Question 16: Database and Programming Concepts
Answer the following questions:
a.	Why might the cooperative retrieve database records into arrays before processing them?
The cooperative retrieves database records into arrays so that the data can be processed efficiently in memory. Arrays allow the program to use loops to perform calculations, searching, counting and reporting without repeatedly accessing the database. This reduces database queries, improves performance and simplifies data manipulation.
b.	What is the role of a loop when processing farmer records?
A loop processes each farmer’s record one at a time. It enables the program to perform the same operation on every record without writing repetitive code.
c.	What is the difference between updating an array and updating the database?
Updating an array changes only the data stored temporarily in the program’s memory. These changes are lost when the program ends while updating the database changes the permanent records on disk, allowing updated information to remain available even after the program is closed and restarted.
d.	Why should parameterized SQL statements be used instead of constructing SQL statements through string concatenation?
Parameterized SQL statements separate the SQL command form the user provided data. This improves security by preventing SQL injection attacks, handles special characters correctly and makes the SQL statements easier to reuse and maintain.
e.	What problems could occur where the arrays have different lengths?
The records would become misaligned and the program may attempt to access elements beyond the end of an array, leading to incorrect results or runtime errors such as array index out-of-bound errors.
f.	Suggest one way of replacing the parallel arrays with records, objects, structures, or dictionaries.
A structure. Instead of storing farmer information in several parallel arrays, the program can define a struct that groups all related information into a single record
For example:

struct Farmer {
int  number;
char name[50];
char produceType[20];
int  quantity;
double pricePerUnit;
char paymentStatus[10];
};

5.	EXTENDED PROGRAMMING TASK
5.1 Overview
To enhance the original assignment, a menu-driven application was developed to provide an interactive interface for managing farmer delivery records. The system retrieves and updates data directly from the SQLite database, allowing users to perform different operations through a simple command-line menu.

5.2 Features Implemented
The menu-driven system supports the following operations:
•	Display all farmer deliveries. 
•	Search for a farmer by farmer number. 
•	Calculate farmer payments. 
•	Display pending payments. 
•	Update payment status. 
•	Display large deliveries. 
•	Generate a daily cooperative report. 
•	Save updated records. 
•	Exit the application. 

5.3 Database Integration
The application connects to the ProduceDeliveries.db database using the SQLite library. SQL queries and prepared statements are used to retrieve, update and manage farmer records. This ensures that changes made through the menu are reflected directly in the database.

5.4 Benefits of the Menu System
The menu-driven approach improves the usability of the application by:
•	Providing an organized interface for users. 
•	Reducing the need to modify the source code for different operations. 
•	Allowing multiple database operations from a single program. 
•	Improving maintainability and user interaction.

6.	CHALLENGES, LESSONS LEARNT AND CONCLUSION
6.1 Challenges Encountered
During the development of the project, several challenges were encountered:
•	Configuring the GCC compiler and SQLite library. 
•	Connecting the C program to the SQLite database. 
•	Debugging SQL statements and prepared statements. 
•	Resolving database path issues between cooperative.c and the menu system. 
•	Managing source code using Git and resolving GitHub merge conflicts. 
These challenges were resolved through testing, debugging and proper project organization.

6.2 Lessons Learned
The project provided practical experience in:
•	Developing applications using the C programming language. 
•	Integrating SQLite databases with C programs. 
•	Writing SQL queries and prepared statements. 
•	Implementing menu-driven applications. 
•	Applying version control using Git and GitHub. 
•	Improving debugging and problem-solving skills. 

6.3 Conclusion
The project successfully achieved its objective of developing a cooperative management system using C and SQLite. The application supports storing, retrieving, updating and managing farmer delivery records while providing useful reports through a menu-driven interface. The project strengthened practical knowledge of database programming, structured programming and software development tools.

