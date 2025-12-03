#ifndef user_management_h
#define user_management_h

using namespace std;

void teacher_menu(User* teacher);
void student_menu(User* student);
User* login_user();
User* find_user_by_username(string username);

#endif