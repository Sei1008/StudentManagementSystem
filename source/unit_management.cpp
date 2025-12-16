#include "../include/operations.h"
#include "../include/struct.h"
#include "../include/user_management.h"
#include "../include/unit_management.h"
#include "../include/enrollment_management.h"
#include <iostream>
#include <iomanip>

void list_all_teaching_units_by_teacher_id(int teacher_id){
    cout << "========================================" << endl;
    cout << "   LIST OF ALL YOUR TEACHING UNITS   " << endl;
    cout << "========================================" << endl;
    cout << left << setw(5) <<"Unit ID"<< setw(10)<<"Unit Code"<<setw(10)<<"Unit Name"<<endl;
    for(const Unit& unit:units_list){
        if(unit.teacher_id==teacher_id){
            cout << left << setw(5) <<unit.unit_id<< setw(10)<<unit.unit_code<<setw(10)<<unit.unit_name<<endl;
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

    save_unit_to_csv(units_list,"../data/unit.csv");
    
}

bool is_unit_full(const Unit& unit){
    if (unit.current_enrollment >= unit.capacity) return true;
    return false;
}

int get_student_enrollment_count(int student_id) {
    int count = 0;
    for (const Enrollment& enrollment : enrollments_list) {
        if (enrollment.student_id == student_id) {
            count++;
        }
    }
    return count;
}

bool is_student_enrolled_in(int student_id, int unit_id) {
    for (const Enrollment& enrollment : enrollments_list) {
        if (enrollment.student_id == student_id && enrollment.unit_id == unit_id) {
            return true;
        }
    }
    return false;
}

vector<Unit>::iterator find_it_by_unit_id(int unit_id){
    for (auto it = units_list.begin(); it != units_list.end(); it++) {
        if (it->unit_id == unit_id) {
            return it;
        }
    }
    return units_list.end();
}

void delete_unit(){
    int unit_id_to_delete;
    cin.ignore(10000,'\n');
    cout << "\n========================================" << endl;
    cout << "            DELETE UNIT                 " << endl;
    cout << "========================================" << endl;
    cout << "Enter Unit ID to delete: ";
    cin>>unit_id_to_delete;

    Unit* unit_to_delete=find_unit_name_by_id(unit_id_to_delete);

    if(unit_to_delete==nullptr){
        cout<<"Error! The unit id does not exist."<<endl;
        return;
    }

    if(unit_to_delete->current_enrollment>0){
        cout<<"This unit still has students studying!"<<endl;
        return;
    }

    vector<Unit>::iterator it_to_delete=find_it_by_unit_id(unit_id_to_delete);
    if(it_to_delete != units_list.end()){
        units_list.erase(it_to_delete);
        cout<<"Delete successfully!"<<endl;
        save_unit_to_csv(units_list,"../data/unit.csv");
    }
}

void list_all_units(){
    cout << "=========================================";
    cout << "\n             LIST OF UNITS            \n";
    cout << "========================================="<<endl;
    cout << left<<"ID"<< setw(5) << "Unit Name"<<endl;
    for(const Unit& unit:units_list){
        cout <<left << unit.unit_id << setw(5)<<unit.unit_name<<endl;
    }
}

void list_students_in_unit(){
    int unit_id_to_list;
    cin.ignore(10000,'\n');
    cout << "=========================================";
    cout << "\n         LIST STUDENT IN UNIT        \n";
    cout << "========================================="<<endl;
    list_all_units;
    cout << "Enter Unit ID to list: ";
    cin >> unit_id_to_list;

    Unit* find_unit=find_unit_name_by_id(unit_id_to_list);
    if(find_unit==nullptr){
        cout << "Error! Can't find the Unit."<<endl;
        return;
    }

    vector<Enrollment> students_list=find_enrollments_by_unit_id(unit_id_to_list);
    cout << "Student ID" << setw(5) << "Score" <<endl;
    for(const Enrollment& list:students_list){
        cout << list.student_id << setw(5) << list.score<<endl;
    }
}

void show_unit_statistic(){
    int unit_id_to_show;
    cout << "=========================================";
    cout << "\n             STATISTICS              \n";
    cout << "=========================================";
    cout <<"Enter Unit ID to show: ";
    cin >> unit_id_to_show;

    Unit* find_unit=find_unit_name_by_id(unit_id_to_show);
    if(find_unit == nullptr){
        cout <<"Error! Cannot find the Unit."<<endl;
        return;
    }

    vector<Enrollment> students_list=find_enrollments_by_unit_id(unit_id_to_show);
    int count=students_list.size();
    int sum=0;
    int max=INT_MIN;
    int min=INT_MAX;
    int count_pass=0;
    int count_npass=0;
    cout << "========================================="<<endl;
    cout << "Student ID" << setw(10) << "Scores" << setw(5) << "Status" << endl;
    for(const Enrollment& cal: students_list){
        cout << cal.student_id << setw(10) << cal.score <<setw(5);
        if(cal.score >=50){
            cout<<"PASSED"<<endl;
            count_pass++;
        }else{
            cout<<"NOT PASSED"<<endl;
            count_npass++;
        }
        if(cal.score>max) max=cal.score;
        if(cal.score<min) min=cal.score;
        sum += cal.score;
    }
    cout << "========================================="<<endl;
    cout << "         SUMMARY STATISTICS REPORT       " <<endl;
    cout << "-----------------------------------------"<<endl;
    cout << "Number Of Students: "<< count <<endl;
    cout << "Highest Score: "<< max <<endl;
    cout << "Lowest Score: "<< min <<endl;
    cout << "Average Score: "<< fixed << setprecision(2) << (double)sum/count <<endl;
    cout << "Pass Rate: "<< fixed << setprecision(2) << (double)count_pass/count*100 << "%" <<endl;
    cout << "Failure Rate: "<< fixed << setprecision(2) << (double)count_npass/count*100 << "%" <<endl;
}