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

