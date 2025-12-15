#include "../include/operations.h"
#include "../include/struct.h"
#include "../include/user_management.h"
#include "../include/unit_management.h"
#include "../include/enrollment_management.h"
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
    
    unsigned long hashPass=encrypt_djb2(input_password);
    User* find_user=find_user_by_username(input_username);
    if(find_user != nullptr){
        if(find_user->password==to_string(hashPass)){
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
        cout << "========================================="<<endl;
        cout << "1. List my teaching units\n";
        cout << "2. Add a new unit\n";
        cout << "3. Delete a unit\n";
        cout << "4. List students in a unit\n";
        cout << "5. Show unit statistics\n";
        cout << "6. Log out\n";
        cout << "==============================="<<endl;
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
                delete_unit();
                break;
            }

            case 4: {
                list_students_in_unit();
                break;
            }

            case 5: {
                show_unit_statistic();
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
    cout << "========================================="<<endl;
    cout << "1. List available units\n";
    cout << "2. List my enrolled units\n";
    cout << "3. Enroll in a unit\n";
    cout << "4. Drop a unit\n";
    cout << "5. Check my scores\n";
    cout << "6. Generate random score (TEST)\n";
    cout << "7. Log out\n";
    cout << "==============================="<<endl;
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
            drop_unit(student);    
                break;
            }

            case 5: {
                check_my_scores(student->id);
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

Unit* find_unit_name_by_id(int unit_id){
    for (Unit& unit : units_list){
        if (unit.unit_id == unit_id){
            return &unit;
        }
    }
    return nullptr;
}

Unit* find_unit_by_code(string code) {
    for (Unit& unit : units_list) {
        if (unit.unit_code == code) { 
            return &unit;
        }
    }
    return nullptr;
}

void list_enrolled_units(int student_id){
    cout << "==========================================\n";
    cout << "             My enrolled units            \n";
    cout << "==========================================\n";

    cout << left << setw(10) << "Unit ID" << setw(20) << "Unit Code" << setw(30) << "Unit Name" << setw(10) << "Score" << endl;
    for (const Enrollment& enrolled : enrollments_list){
        if(enrolled.student_id == student_id){
            Unit* unit_ptr = find_unit_name_by_id(enrolled.unit_id);
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

void enroll_unit(User* student){
    string unit_code;
    cout << "\n========================================" << endl;
    cout << "           ENROLL IN A UNIT             " << endl;
    cout << "========================================" << endl; 

    list_available_units_for_student();
    cin.ignore (10000,'\n');

    cout << "\nEnter unit code to enroll : ";
    getline (cin,unit_code);

    if (get_student_enrollment_count(student->id) == MAX_STUDENT_UNITS){
        cout << "You have reached the maximum enrollment limit (" << MAX_STUDENT_UNITS << " units)." << endl;
        return;
    }

    Unit* target_unit = find_unit_by_code(unit_code);
    if (target_unit == nullptr){
        cout << "Error! Unit code '" << unit_code << "' not found." << endl;
        return;
    }

    if (is_student_enrolled_in(student->id, target_unit->unit_id)){
        cout << "Error! You are already enrolled in this unit." << endl;
        return;
    }

    if (is_unit_full(*target_unit)){
        cout << "Error! Unit '" << unit_code << "' is full (Capacity: " << target_unit->capacity << ")." << endl;
        return;
    }
    
    Enrollment new_enrollment;
    new_enrollment.student_id = student->id;
    new_enrollment.unit_id = target_unit->unit_id;
    new_enrollment.score = -1; //(there no score)

    enrollments_list.push_back(new_enrollment);
    target_unit->current_enrollment++;

    cout << "\nSuccess! You have enrolled in the unit: " << target_unit->unit_name << endl;
    save_all_data();
}

void check_my_scores (int student_id){
    cout << "\n========================================" << endl;
    cout << "                 MY SCORES                 " << endl;
    cout << "==========================================" << endl;
    cout << left << setw(10) << "Unit ID" 
         << left << setw(15) << "Unit Code" 
         << left << setw(30) << "Unit Name" 
         << left << setw(10) << "Score" << endl;
    cout << "----------------------------------------------------------------" << endl;
    bool found_any = false;

    for (const Enrollment& enrollment : enrollments_list){
        if (enrollment.student_id == student_id){
            found_any = true;
            Unit* unit = find_unit_name_by_id(enrollment.unit_id);
            if (unit != nullptr){
                cout << left << setw(10) << unit->unit_id
                     << left << setw(15) << unit->unit_code
                     << left << setw(30) << unit->unit_name;
            }
            else {
                cout << left << setw(10) << enrollment.unit_id 
                     << left << setw(15) << "UNKNOWN" 
                     << left << setw(30) << "Unknown Unit";
            }
            if (enrollment.score == -1) {
                cout << left << setw(10) << "N/A" << endl; 
            } else {
                cout << left << setw(10) << enrollment.score << endl;
            }
        }
    }

    if (!found_any) {
        cout << "\nYou have not enrolled in any units yet." << endl;
    }
    cout << "\nPress Enter to return to menu...";
    cin.ignore();
    cin.get();
    }

void drop_unit(User* student){
        string unit_code;
        cout << "\n========================================" << endl;
        cout << "           DROP A UNIT                  " << endl;
        cout << "========================================" << endl;
        list_enrolled_units(student->id);
        cin.ignore (10000,'\n'); 
        cout << "\nEnter Unit Code to drop: ";
        getline (cin, unit_code); 
        
        Unit* target_unit = find_unit_by_code(unit_code);
        if (target_unit == nullptr){
            cout << "Error! Unit code '" << unit_code << "' not found." << endl;
            return;
        }

        if (!is_student_enrolled_in(student->id,target_unit->unit_id)){
            cout << "Error! You are not enrolled in this unit." << endl;
            return;
        }
        for (auto it = enrollments_list.begin(); it != enrollments_list.end();it++){
            if (it->student_id == student->id && it->unit_id == target_unit->unit_id){
                it = enrollments_list.erase(it);
                cout << "\nSuccess! Dropped Unit: " << target_unit->unit_name << endl;
                target_unit->current_enrollment--;
                save_all_data(); 
                return;
            }
        }
    }

unsigned long  encrypt_djb2(string password){
    unsigned long hash = 5381;
    for(char c: password){
        hash=((hash<<5)+hash) +c;
    }
    return hash;
}

void generate_random_scores(int student_id) {
    cout << "\n========================================" << endl;
    cout << "      GENERATE RANDOM SCORES (TEST)     " << endl;
    cout << "========================================" << endl;

    bool updated = false;
    for (Enrollment& enrollment : enrollments_list) {
        if (enrollment.student_id == student_id && enrollment.score == -1) {

            int random_score = rand() % (100 - 40 + 1) + 40; 

            enrollment.score = random_score;
            updated = true;

            Unit* unit = find_unit_name_by_id(enrollment.unit_id);
            string unit_name = (unit != nullptr) ? unit->unit_name : "Unknown Unit";

            cout << "Generated score for " << unit_name << ": " << random_score << endl;
        }
    }

    if (updated) {
        cout << "\nAll pending units have been graded!" << endl;
        save_all_data(); 
    } else {
        cout << "\nYou have no units waiting for grades (or you haven't enrolled in any)." << endl;
    }
}