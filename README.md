# E-commerce Customer Portal

Overview
This project implements an E-commerce Customer Portal developed in C++, simulating a mid-to-late 1990s environment. It focuses on core customer interaction functionalities, including secure login, password management, and order processing, with data persistence handled through flat files.

Features
Secure Customer Authentication: Users can log in using their customer ID and a default password. Passwords are encrypted using a Caesar cipher (3-position shift) and validated to ensure they are alphanumeric.

Password Management: Authenticated customers can easily reset their passwords, with changes persisted across program terminations.

Order History Review: Customers can view their complete order history, providing transparency on past purchases.

New Order Placement: Allows customers to place new orders by entering quantity, confirming the purchase, and recording it with a default salesperson ID.

Customer Management (Admin-facing):

Search customers by ID or name.

Add new customers with automatically generated unique IDs.

Rainbow Tribble List Management: A special sub-menu to display a waiting list for "Rainbow Tribbles," add customers to the list, and simulate selling a tribble to the top customer on the list.

Sales Reporting: Generates a detailed sales report, including total sales and commissions for different sales staff roles (Sales, SuperSales, Supervisor, Manager).

Data Persistence: All customer, order, and transaction data is stored and managed using text files.

Technologies Used
C++: Core programming language.

Object-Oriented Programming (OOP): Utilized for modular and scalable code design (customer.hpp, orders.hpp, transaction.hpp, absSales.hpp).

File I/O: For reading from and writing to data files (customer.txt, orders.txt, transactions.txt, salesStaff.txt, rainbowlist.txt).

Caesar Cipher: Implemented for basic password encryption.

Standard Library Containers: std::vector for data management.

Input/Output Streams: iostream, fstream, sstream for file and console interactions.

String Manipulation: string, iomanip for formatting and parsing data.

Project Structure
├── Phase 4/
│   ├── customer.hpp
│   ├── orders.hpp
│   ├── transaction.hpp
│   ├── absSales.hpp
│   ├── rainbowlist.hpp
│   ├── main.cpp
│   ├── customer.txt (updated by program)
│   ├── orders.txt (updated by program)
│   ├── transactions.txt (updated by program)
│   ├── salesStaff.txt
│   └── rainbowlist.txt (updated by program)
└── README.md
How to Compile and Run
To compile and run this project, you will need a C++ compiler (e.g., g++).

Navigate to the project directory:

Bash

cd Phase\ 4
Compile the source code:

Bash

g++ -o main main.cpp customer.cpp orders.cpp transaction.cpp absSales.cpp rainbowlist.cpp -std=c++11
Note: Ensure all .cpp files corresponding to your .hpp files (like customer.cpp, orders.cpp, etc.) are included in the compilation command. If they are in the same directory as main.cpp, just listing them is usually enough. If they are in a separate src folder, you might need to adjust the path.

Run the executable:

Bash

./main
Usage
Upon running the program, a main menu will be displayed, offering various options:

Customer Search: Search by ID or name.

Add New Customer: Input details for a new customer.

Customer Sale: Initiate a new order.

Rainbow Tribble List: Access the special menu for managing the waiting list and selling tribbles.

Display Sales Report: View the consolidated sales performance.

Customer Portal: Log in as a customer to change password, view order history, or place an order.

Exit: Terminate the program.

Author
Jennifer (Khue) Ha - Student Name
