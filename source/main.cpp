#include "../include/struct.h"
#include "../include/operations.h"
#include "../include/user_management.h"
#include <iostream>

vector<User> users_list;
vector<Unit> units_list;
vector<Enrollment> enrollments_list;

int main(){
    //load data
    cout << "========================================" << endl;
    cout << "   STUDENT MANAGEMENT SYSTEM   " << endl;
    cout << "========================================" << endl;
    cout << "\nLoading data from files..." << endl;
    load_user_from_csv(users_list,"../data/user.csv");
    load_unit_from_csv(units_list,"../data/unit.csv");
    load_enrollment_from_csv(enrollments_list,"../data/enrollment.csv");
    cout << "Data loaded succesfully!"<<endl;
    //main menu
    User* current_user=nullptr;
    while(current_user==nullptr){
        current_user=login_user();
        if(current_user==nullptr){
            cout <<"Please try again!"<<endl;
        }
    }
    if(current_user->role == "Teacher"){
        teacher_menu(current_user);
    }else if(current_user->role == "Student"){
        student_menu(current_user);
    }else{
        cerr <<"Error! Invalid user role: "<<current_user->role<<endl;
        return 1;
    }
    //save data
    save_all_data();

    return 0;
}