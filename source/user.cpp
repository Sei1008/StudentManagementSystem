#include "operations.h"
#include "struct.h"
#include "user.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


void teacher_menu(User* teacher){
    int choice;
    do {
        cout << "===============================";
        cout << "\n        TEACHER MENU       \n";
        cout << "===============================";
        cout << "1. List my teaching units\n";
        cout << "2. Add a new unit\n";
        cout << "3. Delete a unit\n";
        cout << "4. List students in a unit\n";
        cout << "5. Show unit statistics\n";
        cout << "6. Logout\n";
        cout << "===============================";
        cout << "Enter your choice (1-6) : ";
        cin >> choice;

        switch (choice) {
            case 1: {
                
                break;
            }

            case 2: {
             
                break;
            }

            case 3: {
    
                break;
            }

            case 4: {
                
                break;
            }

            case 5: {
                
                break;
            }

            case 6:
                cout << "Logging out...\n";
                break;

            default:
                cout << "Invalid choice. Please enter a number from 1 to 6.\n";
        }
    } while (choice != 6);
}

void student_menu(User* student){
    int choice;
    do {
    cout << "===============================";
    cout << "\n       STUDENT MENU        \n";
    cout << "===============================";
    cout << "1. List available units\n";
    cout << "2. List my enrolled units\n";
    cout << "3. Enroll in a unit\n";
    cout << "4. Drop a unit\n";
    cout << "5. Check my scores\n";
    cout << "6. Generate random score (TEST)\n";
    cout << "7. Logout\n";
    cout << "===============================";
    cout << "Enter choice : ";
    cin >> choice;
    switch (choice) {
            case 1: {
                
                break;
            }

            case 2: {
             
                break;
            }

            case 3: {
    
                break;
            }

            case 4: {
                
                break;
            }

            case 5: {
                
                break;
            }

            case 6: {

                break;
            }
            case 7: 
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number from 1 to 6.\n";

}
    } while (choice != 7);
}