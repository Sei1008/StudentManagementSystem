#ifndef operations_h
#define operations_h

using namespace std;

void load_user_from_csv(vector<User>& users_list);

void load_unit_from_csv(vector<Unit>& units_list);

void load_enrollment_from_csv(vector<Enrollment>& enrollments_list);

void save_user_to_csv(const vector<User>& users_list);

void save_unit_to_csv(const vector<Unit>& units_list);

void save_enrollment_to_csv(const vector<Enrollment>& enrollments_list);

void save_all_data();

#endif