#ifndef struct_h
#define struct_h

#include <vector>
#include <string>

using namespace std;

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

vector<User> users_list;
vector<Unit> units_list;
vector<Enrollment> enrollments_list;

#endif