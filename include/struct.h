#ifndef struct_h
#define struct_h

#include <vector>
#include <string>

using namespace std;

#define MAX_CAPACITY 100
#define MAX_STUDENT_UNITS 3

struct User{
    int id;
    string username;
    string password;
    string role;
    string status;
};

struct Unit{
    int unit_id;
    string unit_code;
    string unit_name;
    int capacity;
    int current_enrollment;
    int teacher_id;
};

struct Enrollment{
    int student_id;
    int unit_id;
    int score;
};

extern vector<User> users_list;
extern vector<Unit> units_list;
extern vector<Enrollment> enrollments_list;

#endif