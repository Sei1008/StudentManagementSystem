#include "../include/operations.h"
#include "../include/struct.h"
#include "../include/user_management.h"
#include "../include/unit_management.h"
#include <iostream>
#include <iomanip>

void list_all_teaching_units_by_teacher_id(int teacher_id){
    cout << "========================================" << endl;
    cout << "   LIST OF ALL YOUR TEACHING UNITS   " << endl;
    cout << "========================================" << endl;
    cout << setw(5) <<"Unit ID"<< setw(10)<<"Unit Code"<<setw(10)<<"Unit Name"<<endl;
    for(const Unit& unit:units_list){
        if(unit.teacher_id==teacher_id){
            cout << setw(5) <<unit.unit_id<< setw(10)<<unit.unit_code<<setw(10)<<unit.unit_name<<endl;
        }
    }
}

int get_the_next_id(){
    int max=0;
    for(const Unit& unit:units_list){
        if(unit.unit_id > max){
            max=unit.unit_id;
        }
    }
    return max+1;
}

void add_new_unit(){
    int new_teacher_id,new_capacity;
    string new_unit_code,new_unit_name;
    
    cout << "\n========================================" << endl;
    cout << "              ADD NEW UNIT               " << endl;
    cout << "========================================" << endl;
    cin.ignore(10000,'\n');
    cout <<"Enter New Unit Code(Ex: IT001): ";
    getline(cin,new_unit_code);
    cout <<"Enter Unit Name: ";
    getline(cin,new_unit_name);
    cout <<"Enter the Unit's Capacity: ";
    cin>>new_capacity;
    cin.ignore(10000,'\n');
    cout <<"Enter Teacher Id: ";
    cin>>new_teacher_id;
    cin.ignore(10000,'\n');

    Unit new_unit;
    new_unit.unit_id=get_the_next_id();
    new_unit.unit_code=new_unit_code;
    new_unit.unit_name=new_unit_name;
    new_unit.capacity=new_capacity;
    new_unit.current_enrollment=0;
    new_unit.teacher_id=new_teacher_id;

    units_list.push_back(new_unit);

    cout << "\nUnit added successfully!" << endl;
    cout << "Unit ID: " << new_unit.unit_id << " - " << new_unit.unit_name << endl;

    save_unit_to_csv(units_list);
    
}

// Check if the unit is full
bool is_unit_full(const Unit& unit){
    if (unit.current_enrollment >= unit.capacity) return true;
    return false;
}

// Count the enrolled students
int get_student_enrollment_count(int student_id) {
    int count = 0;
    for (const Enrollment& enrollment : enrollments_list) {
        if (enrollment.student_id == student_id) {
            count++;
        }
    }
    return count;
}

// check if this student had already enrolled in the unit
bool is_student_enrolled(int student_id, int unit_id) {
    for (const Enrollment& enrollment : enrollments_list) {
        if (enrollment.student_id == student_id && enrollment.unit_id == unit_id) {
            return true;
        }
    }
    return false;
}



