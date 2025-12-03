#include "../include/struct.h"
#include "../include/operations.h"
#include <iostream>

int main(){
    //load data
    load_user_from_csv(users_list);
    load_unit_from_csv(units_list);
    load_enrollment_from_csv(enrollments_list);
    //main menu


    //save data
    save_all_data();

    return 0;
}