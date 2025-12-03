#include "../include/struct.h"
#include "../include/operations.h"
#include <iostream>

int main(){
    //load data
    cout << "========================================" << endl;
    cout << "   STUDENT MANAGEMENT SYSTEM   " << endl;
    cout << "========================================" << endl;
    cout << "\nLoading data from files..." << endl;
    load_user_from_csv(users_list);
    load_unit_from_csv(units_list);
    load_enrollment_from_csv(enrollments_list);
    cout << "Data loaded succesfully!"<<endl;
    //main menu
    User* current_user=nullptr;
    while(current_user==nullptr){
        current_user=login_user();
        if(current_user==nullptr){
            cout <<"Please try again."<<endl;
        }
    }
    //save data
    save_all_data();

    return 0;
}