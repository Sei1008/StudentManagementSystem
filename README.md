# Student Management System

## 📝 Introduction
This Student Management System is a terminal-based application developed as part of my coursework at **Ho Chi Minh City International University (HCMIU)**. The project focuses on implementing a modular system to handle academic data efficiently using the **C++** programming language. 

Unlike complex database systems, this project utilizes **Structured Programming** and custom `struct` definitions to manage data. It demonstrates core programming concepts such as multi-file compilation, pointer/reference management for data manipulation, and persistent storage using CSV files.

---

## 📂 Project Structure

```text
MiniProject-StudentManagementSystem
├── backup_data/            # Safety backups of existing records
│   ├── bu_enrollment.csv
│   ├── bu_unit.csv
│   └── bu_user.csv
├── data/                   # Active CSV database files
│   ├── enrollment.csv
│   ├── unit.csv
│   └── user.csv
├── include/                # Header files (.h)
│   ├── enrollment_management.h
│   ├── operations.h
│   ├── struct.h            # Data structures and definitions
│   ├── unit_management.h
│   └── user_management.h
├── source/                 # Implementation files (.cpp)
│   ├── enrollment_management.cpp
│   ├── main.cpp
│   ├── operations.cpp
│   ├── unit_management.cpp
│   └── user_management.cpp
├── .gitignore              # Git exclusion rules
└── README.md               # Project documentation
