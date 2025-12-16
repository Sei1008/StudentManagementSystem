#ifndef operations_h
#define operations_h

#include "../include/struct.h"
using namespace std;
 
void load_user_from_csv(vector<User>& users_list,const string& filename);

void load_unit_from_csv(vector<Unit>& units_list,const string& filename);

void load_enrollment_from_csv(vector<Enrollment>& enrollments_list,const string& filename);

void save_user_to_csv(const vector<User>& users_list,const string& filename);

void save_unit_to_csv(const vector<Unit>& units_list,const string& filename);

void save_enrollment_to_csv(const vector<Enrollment>& enrollments_list,const string& filename);

void save_all_data();

void rollback_user(vector <User>& users_list);

void rollback_unit(vector <Unit>& units_list);

void rollback_enrollment(vector <Enrollment>& enrollments_list);

void rollback_data();

#endif