#include "../include/operations.h"
#include "../include/struct.h"
#include "../include/user_management.h"
#include "../include/unit_management.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

User* find_user_by_username(string username){
    for(User& user:users_list){
        if(user.username==username){
            return &user;
        }
    }
    return nullptr;
}

User* login_user(){
    string input_username,input_password;

    cout << "\n========================================" << endl;
    cout << "              LOGIN SYSTEM                " << endl;
    cout << "==========================================" << endl;
    cout << "Username: ";
    cin >> input_username;
    cout << "Password: ";
    cin >> input_password;

    User* find_user=find_user_by_username(input_username);
    if(find_user != nullptr){
        if(find_user->password==input_password){
            cout << "\nLogin successfully! Welcome "<< find_user->username<<endl;
            return find_user;
        }else{
            cout << "\nIncorrect password. Please try again!"<<endl;
            return nullptr;
        }
    }
    cout << "This user do not exist!" <<endl;
    return nullptr;

}

void teacher_menu(User* teacher){
    int choice;
    do {
        cout << "=========================================";
        cout << "\n             TEACHER MENU            \n";
        cout << "=========================================";
        cout << "1. List my teaching units\n";
        cout << "2. Add a new unit\n";
        cout << "3. Delete a unit\n";
        cout << "4. List students in a unit\n";
        cout << "5. Show unit statistics\n";
        cout << "6. Log out\n";
        cout << "===============================";
        cout << "Enter your choice (1-6) : ";
        cin >> choice;

        switch (choice) {
            case 1: {
                list_all_teaching_units_by_teacher_id(teacher->id); 
                break;
            }

            case 2: {
                add_new_unit();
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
    cout << "=========================================";
    cout << "\n             STUDENT MENU            \n";
    cout << "=========================================";
    cout << "1. List available units\n";
    cout << "2. List my enrolled units\n";
    cout << "3. Enroll in a unit\n";
    cout << "4. Drop a unit\n";
    cout << "5. Check my scores\n";
    cout << "6. Generate random score (TEST)\n";
    cout << "7. Log out\n";
    cout << "===============================";
    cout << "Enter choice : ";
    cin >> choice;
    switch (choice) {
            case 1: {
            list_available_units_for_student();
    
                break;
            }

            case 2: {
            list_enrolled_units(student->id);
                break;
            }

            case 3: {
            enroll_unit(student);    
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
                cout << "Invalid choice. Please enter a number from 1 to 7.\n";

}
    } while (choice != 7);
} 

// 1. List available units
void list_available_units_for_student(){
    cout << "==========================================\n";
    cout << "            All available unit            \n";
    cout << "==========================================\n";
    cout << "Unit ID" << setw(5) << "Unit Name" << setw(10) << "Remain capacity" << endl;

    for (const Unit& unit : units_list){
        int remain_capacity = unit.capacity - unit.current_enrollment;
        if(remain_capacity > 0){
            cout << unit.unit_id << setw(5) 
            << unit.unit_name << setw(10) 
            << remain_capacity << endl; 
        }
    }
}



//Find unit name by unit id
Unit* find_unit_name_by_id(int unit_id){
    for (Unit& unit : units_list){
        if (unit.unit_id == unit_id){
            return &unit;
        }
    }
    return nullptr;
}
//Find unit name by unit code
Unit* find_unit_by_code(string code) {
    for (Unit& unit : units_list) {
        if (unit.unit_code == code) { 
            return &unit;
        }
    }
    return nullptr;
}


// 2.List my enrolled units
void list_enrolled_units(int student_id){
    cout << "==========================================\n";
    cout << "             My enrolled units            \n";
    cout << "==========================================\n";

    cout << left << setw(10) << "Unit ID" << setw(20) << "Unit Code" << setw(30) << "Unit Name" << setw(10) << "Score" << endl;
    for (const Enrollment& enrolled : enrollments_list){
        if(enrolled.student_id == student_id){
            Unit* unit_ptr = find_unit_name_by_unit_id(enrolled.unit_id);
            if (unit_ptr != nullptr){
                cout << left << setw(10) << unit_ptr->unit_id
                     << setw(20) << unit_ptr->unit_code
                     << setw(30) << unit_ptr->unit_name
                     << setw(10) << enrolled.score << endl;
            } else {
                cout << left << setw(10) << enrolled.unit_id
                     << setw(20) << "Unknown"
                     << setw(30) << "Unknown unit"
                     << setw(10) << enrolled.score << endl;
            }


        }
    }
}


// 3.Enroll in a unit.
void enroll_unit(User* student){
    string unit_code;
    cout << "\n========================================" << endl;
    cout << "           ENROLL IN A UNIT             " << endl;
    cout << "========================================" << endl; 

    list_available_units_for_student();
    cin.ignore (10000,'\n');

    cout << "\nEnter unit code to enroll : ";
    getline (cin,unit_code);
   // check student's enrollment limit
    if (get_student_enrollment_count(student->id) == MAX_STUDENT_UNITS){
        cout << "You have reached the maximum enrollment limit (" << MAX_STUDENT_UNITS << " units)." << endl;
        return;
    }

    // find and check the existent of unit
    Unit* target_unit = find_unit_by_code(unit_code);
    if (target_unit == nullptr){
        cout << "Error! Unit code '" << unit_code << "' not found." << endl;
        return;
    }

    //check for the duplication
    if (is_student_enrolled(student->id, target_unit->unit_id)){
        cout << "Error! You are already enrolled in this unit." << endl;
        return;
    }

    //check for the capacity
    if (is_unit_full(*target_unit)){
        cout << "Error! Unit '" << unit_code << "' is full (Capacity: " << target_unit->capacity << ")." << endl;
        return;
    }
    
    Enrollment new_enrollment;
    new_enrollment.student_id = student->id;
    new_enrollment.unit_id = target_unit->unit_id;
    new_enrollment.score = NULL; //(there no score)

    //update the enrollment
    enrollments_list.push_back(new_enrollment);
    target_unit->current_enrollment++;
    // Notify and save data
    cout << "\nSuccess! You have enrolled in the unit: " << target_unit->unit_name << endl;
    save_all_data();
}